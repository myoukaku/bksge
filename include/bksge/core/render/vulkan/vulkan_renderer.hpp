/**
 *	@file	vulkan_renderer.hpp
 *
 *	@brief	VulkanRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_VULKAN_RENDERER_HPP
#define BKSGE_CORE_RENDER_VULKAN_VULKAN_RENDERER_HPP

#include <bksge/core/render/renderer.hpp>
#include <bksge/core/render/vulkan/detail/fwd/instance_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/debug_report_callback_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/physical_device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/surface_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/swapchain_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/depth_stencil_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/framebuffer_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/shader_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/fence_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/semaphore_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/pipeline_cache_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_layout_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/image_view_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/pipeline_layout_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/graphics_pipeline_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/geometry_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/descriptor_pool_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/descriptor_set_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/fwd/graphics_pipeline_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/resource_pool_fwd.hpp>
//#include <bksge/core/render/vulkan/detail/shader_stage.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class VulkanRenderer : public Renderer
{
public:
	VulkanRenderer(Window const& window);

	virtual ~VulkanRenderer();

private:
	void VBegin(void) override;
	void VEnd(void) override;
	void VBeginRenderPass(RenderPassInfo const& render_pass_info) override;
	void VEndRenderPass(void) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

private:
	std::shared_ptr<vulkan::Instance>					m_instance;
	bksge::unique_ptr<vulkan::DebugReportCallback>		m_callback;
	std::shared_ptr<vulkan::PhysicalDevice>				m_physical_device;
	std::shared_ptr<vulkan::Device>						m_device;
	bksge::unique_ptr<vulkan::Surface>					m_surface;
	std::shared_ptr<vulkan::CommandPool>				m_command_pool;
	bksge::unique_ptr<vulkan::CommandBuffer>			m_command_buffer;
	::VkQueue											m_graphics_queue;
	bksge::unique_ptr<vulkan::Swapchain>				m_swapchain;
	bksge::unique_ptr<vulkan::DepthStencilBuffer>		m_depth_stencil_buffer;
	bksge::unique_ptr<vulkan::RenderPass>				m_render_pass;
	std::vector<bksge::unique_ptr<vulkan::Framebuffer>>	m_framebuffers;
	bksge::unique_ptr<vulkan::Fence>					m_draw_fence;
	bksge::unique_ptr<vulkan::Semaphore>				m_image_acquired_semaphore;
	bksge::unique_ptr<vulkan::ResourcePool>				m_resource_pool;
	bksge::unique_ptr<vulkan::UniformBuffer>			m_uniform_buffer;
	bksge::uint32_t										m_frame_index = 0;
};

}	// namespace render

using render::VulkanRenderer;

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/inl/vulkan_renderer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_VULKAN_RENDERER_HPP
