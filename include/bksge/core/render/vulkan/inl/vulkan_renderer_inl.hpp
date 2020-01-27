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
#include <bksge/core/render/vulkan/detail/spirv_h.hpp>
#include <bksge/core/render/vulkan/detail/instance.hpp>
#include <bksge/core/render/vulkan/detail/debug_report_callback.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/surface.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/swapchain.hpp>
#include <bksge/core/render/vulkan/detail/depth_buffer.hpp>
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/framebuffer.hpp>
#include <bksge/core/render/vulkan/detail/shader.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/fence.hpp>
#include <bksge/core/render/vulkan/detail/semaphore.hpp>
//#include <bksge/core/render/vulkan/detail/descriptor_set_layout.hpp>
//#include <bksge/core/render/vulkan/detail/pipeline_layout.hpp>
//#include <bksge/core/render/vulkan/detail/pipeline_cache.hpp>
#include <bksge/core/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/core/render/vulkan/detail/descriptor_pool.hpp>
#include <bksge/core/render/vulkan/detail/descriptor_set.hpp>
#include <bksge/core/render/vulkan/detail/geometry.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/resource_pool.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/fnd/cmath/degrees_to_radians.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <assert.h>
#include <iostream>

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

/* Number of viewports and number of scissors have to be the same */
/* at pipeline creation and in any call to set them dynamically   */
/* They also have to be the same as each other                    */
#define NUM_VIEWPORTS 1
#define NUM_SCISSORS NUM_VIEWPORTS

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
		assert(surface_formats.size() >= 1);
		return surface_formats[0].format;
	}
}

VKAPI_ATTR::VkBool32 VKAPI_CALL
DebugCallback(
	::VkDebugReportFlagsEXT flags,
	::VkDebugReportObjectTypeEXT,
	std::uint64_t /*object*/,
	std::size_t /*location*/,
	std::int32_t /*messageCode*/,
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

	//auto width = window.client_size().width();
	//auto height = window.client_size().height();

	m_instance = std::make_shared<vulkan::Instance>(sample_title);

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

	::VkFormat surface_format =
		GetSurfaceFormat(*m_physical_device, *m_surface);

	m_device = std::make_shared<vulkan::Device>(m_physical_device);

	m_command_pool = std::make_shared<vulkan::CommandPool>(
		m_device, graphics_queue_family_index);

	m_command_buffer = bksge::make_unique<vulkan::CommandBuffer>(
		m_device, m_command_pool);

	::vkGetDeviceQueue(*m_device, graphics_queue_family_index, 0, &m_graphics_queue);
	::vkGetDeviceQueue(*m_device, present_queue_family_index, 0, &m_present_queue);

	m_swapchain = bksge::make_unique<vulkan::Swapchain>(
		m_device,
		*m_surface,
		surface_format,
		graphics_queue_family_index,
		present_queue_family_index);

	m_depth_buffer = bksge::make_unique<vulkan::DepthBuffer>(
		m_device,
		m_swapchain->extent(),
		NUM_SAMPLES);

	m_render_pass = bksge::make_unique<vulkan::RenderPass>(
		m_device,
		NUM_SAMPLES,
		surface_format,
		m_depth_buffer->GetFormat(),
		depthPresent);

	// init_framebuffers
	{
		auto const& swap_chain_views = m_swapchain->GetImageViews();
		for (auto const& swap_chain_view : swap_chain_views)
		{
			std::vector<::VkImageView> attachments;
			attachments.push_back(swap_chain_view);
			if (depthPresent)
			{
				attachments.push_back(m_depth_buffer->GetImageView());
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
		256 * 1024);	// TODO
}

BKSGE_INLINE
VulkanRenderer::~VulkanRenderer()
{
}

BKSGE_INLINE void
VulkanRenderer::VBegin(void)
{
	VkResult res;
	// Get the index of the next available swapchain image:
	res = vk::AcquireNextImageKHR(
		*m_device,
		*m_swapchain,
		UINT64_MAX,
		*m_image_acquired_semaphore,
		VK_NULL_HANDLE,
		&m_frame_index);
	// TODO: Deal with the VK_SUBOPTIMAL_KHR and VK_ERROR_OUT_OF_DATE_KHR
	// return codes
	assert(res == VK_SUCCESS);

	m_uniform_buffer->BeginFrame();

	{
		vk::CommandBufferBeginInfo cmd_buf_info;
		cmd_buf_info.flags = 0;
		cmd_buf_info.pInheritanceInfo = nullptr;

		vk::BeginCommandBuffer(*m_command_buffer, &cmd_buf_info);
	}

	::VkClearValue clear_values[2];
	clear_values[0].color.float32[0]     = m_clear_color[0];
	clear_values[0].color.float32[1]     = m_clear_color[1];
	clear_values[0].color.float32[2]     = m_clear_color[2];
	clear_values[0].color.float32[3]     = m_clear_color[3];
	clear_values[1].depthStencil.depth   = 1.0f;
	clear_values[1].depthStencil.stencil = 0;

	vk::RenderPassBeginInfo rp_begin;
	rp_begin.renderPass          = *m_render_pass;
	rp_begin.framebuffer         = *m_framebuffers[m_frame_index];
	rp_begin.renderArea.offset.x = 0;
	rp_begin.renderArea.offset.y = 0;
	rp_begin.renderArea.extent   = m_swapchain->extent();
	rp_begin.SetClearValues(clear_values);

	vk::CmdBeginRenderPass(
		*m_command_buffer,
		&rp_begin,
		VK_SUBPASS_CONTENTS_INLINE);

	// init_viewports
	{
#if defined(__ANDROID__)
		// Disable dynamic viewport on Android. Some drive has an issue with the dynamic viewport
		// feature.
#else
		auto const extent = m_swapchain->extent();
		::VkViewport viewport;
		viewport.x        = 0;
		viewport.y        = 0;
		viewport.width    = (float)extent.width;
		viewport.height   = (float)extent.height;
		viewport.minDepth = (float)0.0f;
		viewport.maxDepth = (float)1.0f;

		// TODO このままだと上下反転しているので、以下のようにして
		// さらにポリゴンの裏表も入れ替える
		viewport.y        = (float)extent.height;
		viewport.height   = (float)extent.height * -1.0f;

		vk::CmdSetViewport(*m_command_buffer, 0, NUM_VIEWPORTS, &viewport);
#endif
	}
}

BKSGE_INLINE void
VulkanRenderer::VEnd(void)
{
	vk::CmdEndRenderPass(*m_command_buffer);
	vk::EndCommandBuffer(*m_command_buffer);

	::VkPipelineStageFlags pipe_stage_flags =
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	vk::SubmitInfo submit_info;
	submit_info.SetWaitSemaphores(m_image_acquired_semaphore->GetAddressOf());
	submit_info.pWaitDstStageMask = &pipe_stage_flags;
	submit_info.SetCommandBuffers(m_command_buffer->GetAddressOf());
	submit_info.SetSignalSemaphores(nullptr);

	/* Queue the command buffer for execution */
	vk::QueueSubmit(m_graphics_queue, 1, &submit_info, *m_draw_fence);

	/* Now present the image in the window */

	vk::PresentInfoKHR present;
	present.SetSwapchains(m_swapchain->GetAddressOf());
	present.SetWaitSemaphores(nullptr);
	present.pImageIndices = &m_frame_index;
	present.pResults      = nullptr;

	/* Make sure command buffer is finished before presenting */
	::VkResult res;
	do {
		res = vk::WaitForFences(
			*m_device,
			1,
			m_draw_fence->GetAddressOf(),
			VK_TRUE,
			FENCE_TIMEOUT);
	} while (res == VK_TIMEOUT);
	assert(res == VK_SUCCESS);

	vk::QueuePresentKHR(m_present_queue, &present);
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

	{
		vk::Rect2D scissor_rect;

		auto const& scissor_state = render_state.scissor_state();
		if (scissor_state.enable())
		{
			scissor_rect.offset.x = static_cast<std::int32_t>(scissor_state.rect().left());
			scissor_rect.offset.y = static_cast<std::int32_t>(scissor_state.rect().top());
			scissor_rect.extent.width  = static_cast<std::uint32_t>(scissor_state.rect().width());
			scissor_rect.extent.height = static_cast<std::uint32_t>(scissor_state.rect().height());
		}
		else
		{
			scissor_rect.offset.x = 0;
			scissor_rect.offset.y = 0;
			scissor_rect.extent   = m_swapchain->extent();
		}

		vk::CmdSetScissor(*m_command_buffer, 0, NUM_SCISSORS, &scissor_rect);
	}

	auto vk_shader =
		m_resource_pool->GetShader(
			m_device,
			shader,
			m_uniform_buffer.get());

	auto graphics_pipeline =
		m_resource_pool->GetGraphicsPipeline(
			m_device,
			NUM_SAMPLES,
			geometry,
			shader,
			render_state,
			*m_render_pass,
			m_uniform_buffer.get());

	auto offsets = vk_shader->LoadParameters(
		shader_parameter_map,
		m_uniform_buffer.get());

	vk::CmdBindPipeline(
		*m_command_buffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		*graphics_pipeline);

	vk::CmdBindDescriptorSets(
		*m_command_buffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		graphics_pipeline->GetLayout(),
		0,
		static_cast<std::uint32_t>(vk_shader->GetDescriptorSet()->Get().size()),
		vk_shader->GetDescriptorSet()->Get().data(),
		static_cast<std::uint32_t>(offsets.size()),
		offsets.data());

	auto vk_geometry = m_resource_pool->GetGeometry(m_device, geometry);

	vk_geometry->Draw(m_command_buffer.get());

	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP
