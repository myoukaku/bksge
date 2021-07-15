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
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/frame_buffer.hpp>
#include <bksge/core/render/vulkan/detail/shader.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/fence.hpp>
#include <bksge/core/render/vulkan/detail/semaphore.hpp>
#include <bksge/core/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/core/render/vulkan/detail/geometry.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/resource_pool.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_layout.hpp>
#include <bksge/core/render/vulkan/detail/viewport.hpp>
#include <bksge/core/render/vulkan/detail/scissor_state.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/sampler.hpp>
#include <bksge/core/render/vulkan/detail/queue.hpp>
#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/vertex.hpp>
#include <bksge/core/render/vertex_element.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <sstream>
#include <cstdio>	// printf
#include <cstddef>
#include <cstdint>

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
	auto const surface_formats = surface.GetFormats(physical_device);
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

VKAPI_ATTR ::VkBool32 VKAPI_CALL
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
	std::stringstream ss;
	ss << "Vulkan DebugCall: ";
	if ((flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0)
	{
		ss << "[Info]: ";
	}
	if ((flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
	{
		ss << "[Warning]: ";
	}
	if ((flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
	{
		ss << "[PerformanceWarning]: ";
	}
	if ((flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
	{
		ss << "[Error]: ";
	}
	if ((flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
	{
		ss << "[Debug]: ";
	}

	ss << pMessage << std::endl;

	std::printf("%s", ss.str().c_str());

#if defined(BKSGE_PLATFORM_WIN32)
	win32::OutputDebugString(ss.str().c_str());
	if ((flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
	{
		win32::MessageBox(nullptr, pMessage, "Vulkan DebugReportCallback", MB_OK);
	}
#endif

	return VK_FALSE;
}

struct VulkanRenderer::OffscreenBufferDrawer
{
public:
	OffscreenBufferDrawer(vulkan::DeviceSharedPtr const& device)
	{
		bksge::Sampler sampler;
		m_sampler = bksge::make_shared<vulkan::Sampler>(device, sampler);
	}

	void Draw(
		VulkanRenderer* renderer,
		vulkan::ImageSharedPtr const& image,
		bksge::Extent2<std::uint32_t> const& extent)
	{
		m_render_pass_info.clear_state().SetFlag(bksge::ClearFlag::kNone);
		m_render_pass_info.viewport().SetRect({{0, 0}, extent});

		m_shader_parameter_map.SetParameter(
			"uSampler2D", bksge::make_pair(m_sampler, image));

		renderer->ApplyRenderPassInfo(m_render_pass_info);
		renderer->Render(
			GetGeometry(),
			GetShader(),
			m_shader_parameter_map,
			m_render_state);
		renderer->EndRenderPass();
	}
private:
	static bksge::Geometry const& GetGeometry(void)
	{
		static bksge::Vertex<bksge::VPosition, bksge::VTexCoord> const vertices[] =
		{
			{{{-1.0,  3.0, 0.0}}, {{0, 0}}},
			{{{-1.0, -1.0, 0.0}}, {{0, 2}}},
			{{{ 3.0, -1.0, 0.0}}, {{2, 2}}},
		};
		static std::uint16_t const indices[] =
		{
			0, 1, 2,
		};

		static bksge::Geometry const s_geometry(
			bksge::PrimitiveTopology::kTriangles, vertices, indices);

		return s_geometry;
	}

	static bksge::Shader const& GetShader(void)
	{
		static char const* vs_source =
			"#version 420											\n"
			"#extension GL_ARB_separate_shader_objects : enable		\n"
			"														\n"
			"layout (location = 0) in vec3 aPosition;				\n"
			"layout (location = 1) in vec2 aTexCoord;				\n"
			"														\n"
			"layout (location = 0) out vec2 vTexCoord;				\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	gl_Position = vec4(aPosition, 1.0);					\n"
			"	vTexCoord   = aTexCoord;							\n"
			"}														\n"
		;

		static char const* fs_source =
			"#version 420											\n"
			"#extension GL_ARB_separate_shader_objects : enable		\n"
			"														\n"
			"layout (location = 0) in vec2 vTexCoord;				\n"
			"														\n"
			"layout (location = 0) out vec4 oColor;					\n"
			"														\n"
			"layout (binding = 1) uniform sampler2D uSampler2D;		\n"
			"														\n"
			"void main()											\n"
			"{														\n"
			"	oColor = texture(uSampler2D, vTexCoord);			\n"
			"}														\n"
		;

		static bksge::Shader const s_shader
		{
			{ bksge::ShaderStage::kVertex,   vs_source },
			{ bksge::ShaderStage::kFragment, fs_source },
		};

		return s_shader;
	}

private:
	bksge::RenderPassInfo		m_render_pass_info;
	bksge::RenderState			m_render_state;
	bksge::ShaderParameterMap	m_shader_parameter_map;
	vulkan::SamplerSharedPtr	m_sampler;
};

BKSGE_INLINE
VulkanRenderer::VulkanRenderer(Window const& window)
{
	char const* app_name = "Bksge VulkanRenderer";	// TODO

	m_instance = bksge::make_shared<vulkan::Instance>(app_name);

	m_callback = bksge::make_unique<vulkan::DebugReportCallback>(
		m_instance,
		VK_DEBUG_REPORT_ERROR_BIT_EXT               |
		VK_DEBUG_REPORT_WARNING_BIT_EXT             |
		VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
		VK_DEBUG_REPORT_INFORMATION_BIT_EXT         |
		0,//VK_DEBUG_REPORT_DEBUG_BIT_EXT,
		&DebugCallback);

	auto gpus = m_instance->EnumeratePhysicalDevices();
	// TODO 一番良いgpuを選ぶ
	m_physical_device = bksge::make_unique<vulkan::PhysicalDevice>(gpus[0]);

	m_surface = bksge::make_unique<vulkan::Surface>(m_instance, window);

	auto const graphics_queue_family_index =
		m_physical_device->GetGraphicsQueueFamilyIndex();

	m_device = bksge::make_shared<vulkan::Device>(m_physical_device);

	m_command_pool = bksge::make_shared<vulkan::CommandPool>(m_device);

	m_command_buffer = bksge::make_unique<vulkan::CommandBuffer>(m_command_pool);

	m_graphics_queue = bksge::make_unique<vulkan::Queue>(
		m_device, graphics_queue_family_index, 0);

	m_draw_fence = bksge::make_unique<vulkan::Fence>(m_device);
	m_image_acquired_semaphore = bksge::make_unique<vulkan::Semaphore>(m_device);
	m_resource_pool = bksge::make_unique<vulkan::ResourcePool>(m_device);
	m_uniform_buffer = bksge::make_unique<vulkan::UniformBuffer>(
		m_device,
		65536 * 1024);	// TODO

	CreateSwapchain();
	CreateFrameBuffers();

	{
		vulkan::Extent2D const extent(window.client_size());

		auto color_buffer = bksge::make_shared<vulkan::Image>(
			m_device,
			VK_FORMAT_R8G8B8A8_UNORM,
			extent,
			1,
			NUM_SAMPLES,
			VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
			VK_IMAGE_USAGE_SAMPLED_BIT |
			VK_IMAGE_USAGE_TRANSFER_DST_BIT);

		color_buffer->TransitionLayout(
			m_command_pool,
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

		auto depth_stencil_buffer = bksge::make_shared<vulkan::Image>(
			m_device,
			VK_FORMAT_D24_UNORM_S8_UINT,
			extent,
			1,
			NUM_SAMPLES,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
			VK_IMAGE_USAGE_TRANSFER_DST_BIT);

		depth_stencil_buffer->TransitionLayout(
			m_command_pool,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

		m_offscreen_frame_buffer = bksge::make_shared<vulkan::FrameBuffer>(
			m_device,
			extent,
			NUM_SAMPLES,
			color_buffer,
			depth_stencil_buffer);
	}

	m_offscreen_buffer_drawer = bksge::make_unique<OffscreenBufferDrawer>(m_device);
}

BKSGE_INLINE
VulkanRenderer::~VulkanRenderer()
{
}

BKSGE_INLINE void
VulkanRenderer::RecreateSwapchain(void)
{
	m_device->WaitIdle();

	m_default_frame_buffers.clear();
	m_swapchain.reset();

	CreateSwapchain();
	CreateFrameBuffers();
}

BKSGE_INLINE void
VulkanRenderer::CreateSwapchain(void)
{
	auto const surface_format =
		GetSurfaceFormat(*m_physical_device, *m_surface);

	m_swapchain = bksge::make_unique<vulkan::Swapchain>(
		m_device,
		m_command_pool,
		*m_surface,
		surface_format);
}

BKSGE_INLINE void
VulkanRenderer::CreateFrameBuffers(void)
{
	auto const& swap_chain_images = m_swapchain->images();
	for (auto const& image : swap_chain_images)
	{
		auto frame_buffer = bksge::make_shared<vulkan::FrameBuffer>(
			m_device,
			m_swapchain->extent(),
			NUM_SAMPLES,
			image,
			nullptr);
		m_default_frame_buffers.push_back(frame_buffer);
	}
}

BKSGE_INLINE void
VulkanRenderer::VBegin(void)
{
	auto const result = m_swapchain->AcquireNextImage(
		UINT64_MAX,
		*m_image_acquired_semaphore->GetAddressOf(),
		VK_NULL_HANDLE,
		&m_frame_index);
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapchain();
	}

	m_uniform_buffer->BeginFrame();

	m_command_buffer->Begin(0);
}

BKSGE_INLINE void
VulkanRenderer::VEnd(void)
{
	m_current_frame_buffer = m_default_frame_buffers[m_frame_index];

	{
		auto& color_buffer = m_offscreen_frame_buffer->color_buffer();

		auto current_layout = color_buffer->TransitionLayout(
			m_command_buffer.get(),
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

		m_offscreen_buffer_drawer->Draw(
			this,
			color_buffer,
			m_swapchain->extent());

		color_buffer->TransitionLayout(
			m_command_buffer.get(),
			current_layout);
	}

	m_command_buffer->End();

	::VkPipelineStageFlags const pipe_stage_flags =
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	vk::SubmitInfo submit_info = m_command_buffer->CreateSubmitInfo();
	submit_info.SetWaitSemaphores(*m_image_acquired_semaphore->GetAddressOf());
	submit_info.pWaitDstStageMask = &pipe_stage_flags;
	submit_info.SetSignalSemaphores(nullptr);

	m_graphics_queue->Submit(submit_info, *m_draw_fence->GetAddressOf());

	::VkResult res;
	do {
		res = m_draw_fence->Wait(VK_TRUE, FENCE_TIMEOUT);
	} while (res == VK_TIMEOUT);
	BKSGE_ASSERT(res == VK_SUCCESS);

	m_draw_fence->Reset();

	auto const result = m_swapchain->Present(m_frame_index);
	if (result == VK_ERROR_OUT_OF_DATE_KHR ||
		result == VK_SUBOPTIMAL_KHR)
	{
		RecreateSwapchain();
	}
}

BKSGE_INLINE void
VulkanRenderer::VBeginRenderPass(RenderPassInfo const& render_pass_info)
{
	ApplyFrameBuffer(render_pass_info);
	ApplyRenderPassInfo(render_pass_info);
}

BKSGE_INLINE void
VulkanRenderer::ApplyFrameBuffer(RenderPassInfo const& render_pass_info)
{
	if (render_pass_info.frame_buffer() != nullptr)
	{
		//m_current_frame_buffer = m_resource_pool->GetFrameBuffer(
		//	*render_pass_info.frame_buffer());
		m_current_frame_buffer = m_offscreen_frame_buffer;
	}
	else
	{
		m_current_frame_buffer = m_offscreen_frame_buffer;
	}
}

BKSGE_INLINE void
VulkanRenderer::ApplyRenderPassInfo(RenderPassInfo const& render_pass_info)
{
	m_current_frame_buffer->Clear(
		m_command_buffer.get(),
		render_pass_info.clear_state());

	m_command_buffer->BeginRenderPass(
		m_current_frame_buffer->GetRenderPassBeginInfo());

	m_command_buffer->SetViewport(
		vulkan::Viewport(render_pass_info.viewport()));

	m_command_buffer->SetScissor(
		vulkan::ScissorState(
			render_pass_info.scissor_state(),
			render_pass_info.viewport()
		).rect());
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
	auto vk_shader = m_resource_pool->GetShader(shader);

	vk_shader->LoadParameters(
		shader_parameter_map,
		m_command_pool,
		m_uniform_buffer.get(),
		m_resource_pool.get());

	auto graphics_pipeline = m_resource_pool->GetGraphicsPipeline(
		*m_current_frame_buffer->render_pass(),
		geometry,
		shader,
		render_state);

	graphics_pipeline->Bind(m_command_buffer.get());

	graphics_pipeline->PushDescriptorSet(
		m_command_buffer.get(),
		0,	// TODO set
		vk_shader->GetWriteDescriptorSets());

	auto vk_geometry = m_resource_pool->GetGeometry(geometry);

	vk_geometry->Draw(m_command_buffer.get());

	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP
