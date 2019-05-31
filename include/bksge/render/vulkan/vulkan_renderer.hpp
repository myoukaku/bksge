/**
 *	@file	vulkan_renderer.hpp
 *
 *	@brief	VulkanRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_VULKAN_RENDERER_HPP
#define BKSGE_RENDER_VULKAN_VULKAN_RENDERER_HPP

#include <bksge/render/renderer.hpp>
#include <bksge/window/fwd/window_fwd.hpp>
#include <bksge/render/vulkan/detail/instance.hpp>
#include <bksge/render/vulkan/detail/physical_device.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <bksge/render/vulkan/detail/command_pool.hpp>
#include <bksge/render/vulkan/detail/command_buffer.hpp>
#include <bksge/render/vulkan/detail/debug_report_callback.hpp>
#include <bksge/render/vulkan/detail/surface.hpp>
#include <bksge/render/vulkan/detail/fence.hpp>
#include <bksge/render/vulkan/detail/swapchain.hpp>
#include <bksge/render/vulkan/detail/image_view.hpp>
#include <bksge/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/render/vulkan/detail/pipeline_layout.hpp>
#include <bksge/render/vulkan/detail/render_pass.hpp>
#include <bksge/render/vulkan/detail/framebuffer.hpp>
#include <bksge/render/vulkan/detail/descriptor_pool.hpp>
#include <bksge/render/vulkan/detail/descriptor_set.hpp>
#include <bksge/render/vulkan/detail/pipeline_cache.hpp>
#include <bksge/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/render/vulkan/detail/shader_stage.hpp>
#include <memory>
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
	VulkanRenderer(void);

	virtual ~VulkanRenderer();

private:
	void VSetRenderTarget(Window const& window) override;
	void VBegin(void) override;
	void VEnd(void) override;
	void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

private:
	std::shared_ptr<vk::Instance>					m_instance;
	std::unique_ptr<vk::DebugReportCallbackEXT>		m_callback;
	std::vector<vk::PhysicalDevice>					m_gpus;
	std::shared_ptr<vk::Device>						m_device;
	::VkQueue										m_graphics_queue;
	std::unique_ptr<vk::Fence>						m_fence;
	std::unique_ptr<vk::CommandPool>				m_command_pool;
	std::unique_ptr<vk::CommandBuffer>				m_command_buffer;
	std::unique_ptr<vk::Surface>					m_surface;
	std::unique_ptr<vk::Swapchain>					m_swapchain;
	std::vector<std::shared_ptr<vk::ImageView>>		m_image_views;
	std::unique_ptr<vk::DescriptorSetLayout>		m_descriptor_set_layout;
	std::unique_ptr<vk::PipelineLayout>				m_pipeline_layout;
	std::unique_ptr<vk::RenderPass>					m_render_pass;
	std::vector<std::shared_ptr<vk::Framebuffer>>	m_framebuffers;
	std::unique_ptr<vk::DescriptorPool>				m_descriptor_pool;
	std::unique_ptr<vk::DescriptorSet>				m_descriptor_set;
	std::unique_ptr<vk::PipelineCache>				m_pipeline_cache;
	std::unique_ptr<vk::GraphicsPipeline>			m_pipeline;
	std::unique_ptr<vk::ShaderStages>				m_shader_stages;
	std::uint32_t									m_current_frame_index = 0;
};

}	// namespace render

using render::VulkanRenderer;

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/inl/vulkan_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_VULKAN_RENDERER_HPP
