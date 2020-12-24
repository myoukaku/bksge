/**
 *	@file	vulkan_renderer_inl.hpp
 *
 *	@brief	VulkanRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/vulkan_renderer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/vulkan/detail/instance.hpp>
#include <bksge/core/render/vulkan/detail/debug_report_callback.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/surface.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/swapchain.hpp>
#include <bksge/core/render/vulkan/detail/depth_stencil_buffer.hpp>
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/framebuffer.hpp>
#include <bksge/core/render/vulkan/detail/shader.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/fence.hpp>
#include <bksge/core/render/vulkan/detail/semaphore.hpp>
#include <bksge/core/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/core/render/vulkan/detail/geometry.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/resource_pool.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_PLATFORM_WIN32)
#include <bksge/core/detail/win32.hpp>
#endif

namespace bksge
{

namespace render
{

/* Number of samples needs to be the same at image creation,      */
/* renderpass creation and pipeline creation.                     */
#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT

/* Amount of time, in nanoseconds, to wait for a command buffer to complete */
#define FENCE_TIMEOUT 100000000

inline ::VkFormat GetSurfaceFormat(
	vulkan::PhysicalDevice const& physical_device,
	vulkan::Surface const& surface)
{
	auto surface_formats =
		vk::GetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface);
	// If the format list includes just one entry of VK_FORMAT_UNDEFINED,
	// the surface has no preferred format.  Otherwise, at least one
	// supported format will be returned.
	if (surface_formats.size() == 1 &&
		surface_formats[0].format == VK_FORMAT_UNDEFINED)
	{
		return VK_FORMAT_B8G8R8A8_UNORM;
	}
	else
	{
		BKSGE_ASSERT(surface_formats.size() >= 1u);
		return surface_formats[0].format;
	}
}

VKAPI_ATTR::VkBool32 VKAPI_CALL
DebugCallback(
	::VkDebugReportFlagsEXT flags,
	::VkDebugReportObjectTypeEXT,
	bksge::uint64_t /*object*/,
	bksge::size_t /*location*/,
	bksge::int32_t /*messageCode*/,
	const char* /*pLayerPrefix*/,
	const char* pMessage,
	void* /*pUserData*/)
{
#if defined(BKSGE_PLATFORM_WIN32)
	win32::OutputDebugString("Vulkan DebugCall: ");
	if ((flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0)
	{
		win32::OutputDebugString("[Info]: ");
	}
	if ((flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
	{
		win32::OutputDebugString("[Warning]: ");
	}
	if ((flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
	{
		win32::OutputDebugString("[PerformanceWarning]: ");
	}
	if ((flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
	{
		win32::OutputDebugString("[Error]: ");
	}
	if ((flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
	{
		win32::OutputDebugString("[Debug]: ");
	}

	win32::OutputDebugString(pMessage);
	win32::OutputDebugString("\n");

	if ((flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
	{
		win32::MessageBox(nullptr, pMessage, "Vulkan DebugReportCallback", MB_OK);
	}
#else
	(void)flags;
	(void)pMessage;
#endif

	return VK_FALSE;
}

BKSGE_INLINE
VulkanRenderer::VulkanRenderer(Window const& window)
{
	char sample_title[] = "Draw Cube";
	const bool depthPresent = true;

	m_instance = bksge::make_shared<vulkan::Instance>(sample_title);

	m_callback = bksge::make_unique<vulkan::DebugReportCallback>(
		m_instance,
		VK_DEBUG_REPORT_ERROR_BIT_EXT               |
		VK_DEBUG_REPORT_WARNING_BIT_EXT             |
		VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
		VK_DEBUG_REPORT_INFORMATION_BIT_EXT         |
		0,//VK_DEBUG_REPORT_DEBUG_BIT_EXT,
		&DebugCallback);

	auto gpus = m_instance->EnumeratePhysicalDevices();

	m_physical_device = bksge::make_unique<vulkan::PhysicalDevice>(gpus[0]);

	m_surface = bksge::make_unique<vulkan::Surface>(m_instance, window);

	auto const graphics_queue_family_index =
		m_physical_device->GetGraphicsQueueFamilyIndex();
	auto const present_queue_family_index =
		m_physical_device->GetPresentQueueFamilyIndex(*m_surface);

	::VkFormat const surface_format =
		GetSurfaceFormat(*m_physical_device, *m_surface);

	m_device = bksge::make_shared<vulkan::Device>(m_physical_device);

	m_command_pool = bksge::make_shared<vulkan::CommandPool>(
		m_device, graphics_queue_family_index);

	m_command_buffer = bksge::make_unique<vulkan::CommandBuffer>(
		m_command_pool);

	vk::GetDeviceQueue(*m_device, graphics_queue_family_index, 0, &m_graphics_queue);

	m_swapchain = bksge::make_unique<vulkan::Swapchain>(
		m_device,
		m_command_pool,
		*m_surface,
		surface_format,
		graphics_queue_family_index,
		present_queue_family_index);

	m_depth_stencil_buffer = bksge::make_unique<vulkan::DepthStencilBuffer>(
		m_device,
		m_command_pool,
		m_swapchain->extent(),
		NUM_SAMPLES);

	m_render_pass = bksge::make_unique<vulkan::RenderPass>(
		m_device,
		NUM_SAMPLES,
		surface_format,
		m_depth_stencil_buffer->GetFormat(),
		depthPresent);

	// init_framebuffers
	{
		auto const& swap_chain_views = m_swapchain->GetImageViews();
		for (auto const& swap_chain_view : swap_chain_views)
		{
			bksge::vector<::VkImageView> attachments;
			attachments.push_back(swap_chain_view);
			if (depthPresent)
			{
				attachments.push_back(m_depth_stencil_buffer->GetImageView());
			}

			m_framebuffers.push_back(
				bksge::make_unique<vulkan::Framebuffer>(
					m_device, *m_render_pass, attachments, m_swapchain->extent()));
		}
	}

	m_draw_fence = bksge::make_unique<vulkan::Fence>(m_device);
	m_image_acquired_semaphore = bksge::make_unique<vulkan::Semaphore>(m_device);
	m_resource_pool = bksge::make_unique<vulkan::ResourcePool>();
	m_uniform_buffer = bksge::make_unique<vulkan::UniformBuffer>(
		m_device,
		65536 * 1024);	// TODO
}

BKSGE_INLINE
VulkanRenderer::~VulkanRenderer()
{
}

BKSGE_INLINE void
VulkanRenderer::VBegin(void)
{
	m_frame_index = m_swapchain->AcquireNextImage(
		UINT64_MAX,
		*m_image_acquired_semaphore,
		VK_NULL_HANDLE);

	m_uniform_buffer->BeginFrame();

	m_command_buffer->Begin(0);
}

BKSGE_INLINE void
VulkanRenderer::VEnd(void)
{
	m_command_buffer->End();

	::VkPipelineStageFlags pipe_stage_flags =
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	vk::SubmitInfo submit_info;
	submit_info.SetWaitSemaphores(m_image_acquired_semaphore->GetAddressOf());
	submit_info.pWaitDstStageMask = &pipe_stage_flags;
	submit_info.SetCommandBuffers(m_command_buffer->GetAddressOf());
	submit_info.SetSignalSemaphores(nullptr);

	vk::QueueSubmit(m_graphics_queue, 1, &submit_info, *m_draw_fence);

	::VkResult res;
	do {
		res = m_draw_fence->Wait(VK_TRUE, FENCE_TIMEOUT);
	} while (res == VK_TIMEOUT);
	BKSGE_ASSERT(res == VK_SUCCESS);

	m_draw_fence->Reset();

	m_swapchain->Present(m_frame_index);
}

BKSGE_INLINE void
VulkanRenderer::VBeginRenderPass(RenderPassInfo const& render_pass_info)
{
	m_depth_stencil_buffer->Clear(
		m_command_pool,
		render_pass_info.clear_state());

	m_swapchain->ClearColor(
		m_command_pool,
		m_frame_index,
		render_pass_info.clear_state());

	{
		vk::RenderPassBeginInfo rp_begin;
		rp_begin.renderPass          = *m_render_pass;
		rp_begin.framebuffer         = *m_framebuffers[m_frame_index];
		rp_begin.renderArea.offset.x = 0;
		rp_begin.renderArea.offset.y = 0;
		rp_begin.renderArea.extent   = m_swapchain->extent();

		m_command_buffer->BeginRenderPass(rp_begin);
	}
	{
		auto const& viewport = render_pass_info.viewport();

		::VkViewport vp;
		vp.x        = viewport.rect().left();
		vp.y        = viewport.rect().top() + viewport.rect().height();
		vp.width    = viewport.rect().width();
		vp.height   = -viewport.rect().height();
		vp.minDepth = viewport.min_depth();
		vp.maxDepth = viewport.max_depth();
		m_command_buffer->SetViewport(vp);
	}
	{

		auto const& scissor_state = render_pass_info.scissor_state();
		auto const rect =
			scissor_state.enable() ?
			scissor_state.rect() :
			render_pass_info.viewport().rect();

		vk::Rect2D scissor_rect;
		scissor_rect.offset.x = static_cast<bksge::int32_t>(bksge::max(0.0f, rect.left()));
		scissor_rect.offset.y = static_cast<bksge::int32_t>(bksge::max(0.0f, rect.top()));
		scissor_rect.extent.width  = static_cast<bksge::uint32_t>(rect.width());
		scissor_rect.extent.height = static_cast<bksge::uint32_t>(rect.height());

		m_command_buffer->SetScissor(scissor_rect);
	}
}

BKSGE_INLINE void
VulkanRenderer::VEndRenderPass(void)
{
	m_command_buffer->EndRenderPass();
}

BKSGE_INLINE bool
VulkanRenderer::VRender(
	Geometry const& geometry,
	Shader const& shader,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	if (shader.type() != ShaderType::kGLSL)
	{
		return false;
	}

	auto vk_shader =
		m_resource_pool->GetShader(
			m_device,
			shader);

	auto graphics_pipeline =
		m_resource_pool->GetGraphicsPipeline(
			m_device,
			NUM_SAMPLES,
			geometry,
			shader,
			render_state,
			*m_render_pass);

	vk_shader->LoadParameters(
		shader_parameter_map,
		m_device,
		m_command_pool,
		m_uniform_buffer.get(),
		m_resource_pool.get());

	m_command_buffer->BindPipeline(
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		*graphics_pipeline);

	m_command_buffer->PushDescriptorSet(
		*m_device,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		graphics_pipeline->GetLayout(),
		0,	// TODO set
		vk_shader->GetWriteDescriptorSets());

	auto vk_geometry = m_resource_pool->GetGeometry(m_device, geometry);

	vk_geometry->Draw(m_command_buffer.get());

	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP
