/**
 *	@file	vulkan_renderer_inl.hpp
 *
 *	@brief	VulkanRenderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP
#define BKSGE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/vulkan_renderer.hpp>
#include <bksge/render/vulkan/detail/instance.hpp>
#include <bksge/render/vulkan/detail/physical_device.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <bksge/render/vulkan/detail/command_pool.hpp>
#include <bksge/render/vulkan/detail/command_buffer.hpp>
#include <bksge/render/vulkan/detail/debug_report_callback.hpp>
#include <bksge/render/vulkan/detail/surface.hpp>
#include <bksge/render/vulkan/detail/fence.hpp>
#include <bksge/render/vulkan/detail/image_view.hpp>
#include <bksge/render/vulkan/detail/swapchain.hpp>
#include <bksge/render/vulkan/detail/descriptor_set_layout.hpp>
#include <bksge/render/vulkan/detail/pipeline_layout.hpp>
#include <bksge/render/vulkan/detail/render_pass.hpp>
#include <bksge/render/vulkan/detail/framebuffer.hpp>
#include <bksge/render/vulkan/detail/descriptor_pool.hpp>
#include <bksge/render/vulkan/detail/descriptor_set.hpp>
#include <bksge/render/vulkan/detail/pipeline_cache.hpp>
#include <bksge/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/render/vulkan/detail/shader_stage.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/memory/make_unique.hpp>
#include <bksge/window/window.hpp>
#include <bksge/config.hpp>
#include <cstdint>
#include <cstddef>
#if defined(BKSGE_PLATFORM_WIN32)
#include <bksge/detail/win32.hpp>
#endif

namespace bksge
{

namespace render
{

VKAPI_ATTR ::VkBool32 VKAPI_CALL
debugCallback(
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
	// OutputDebugString(L"Message Code: ");
	// OutputDebugString(std::to_wstring(messageCode).c_str());
	// OutputDebugString(L"\n");

	win32::OutputDebugString("Vulkan DebugCall: ");
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
VulkanRenderer::VulkanRenderer(void)
{
	// Init Instance
	{
		static char const* app_name = "bksge";

		static char const* layers[] =
		{
			"VK_LAYER_LUNARG_standard_validation"
		};

		static char const* extensions[] =
		{
			VK_KHR_SURFACE_EXTENSION_NAME,
#if defined(BKSGE_PLATFORM_WIN32)
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
			VK_EXT_DEBUG_REPORT_EXTENSION_NAME
		};

		// initialize the VkApplicationInfo structure
		vk::ApplicationInfo app_info;
		app_info.pApplicationName   = app_name;
		app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
		app_info.pEngineName        = app_name;
		app_info.engineVersion      = VK_MAKE_VERSION(0, 0, 1);
		app_info.apiVersion         = VK_API_VERSION_1_0;

		// initialize the VkInstanceCreateInfo structure
		vk::InstanceCreateInfo inst_info;
		inst_info.flags            = 0;
		inst_info.pApplicationInfo = &app_info;
		inst_info.SetEnabledLayers(layers);
		inst_info.SetEnabledExtensions(extensions);

		m_instance = std::make_shared<vk::Instance>(inst_info);
	}

	{
		vk::DebugReportCallbackCreateInfoEXT callback_info;

		callback_info.flags =
			VK_DEBUG_REPORT_ERROR_BIT_EXT |
			VK_DEBUG_REPORT_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
		callback_info.pfnCallback = &debugCallback;

		m_callback = bksge::make_unique<vk::DebugReportCallbackEXT>(m_instance, callback_info);
	}

	std::uint32_t queue_family_index = 0xffffffff;

	// Init Device
	{
		m_gpus = m_instance->EnumeratePhysicalDevices();

		auto properties = m_gpus[0].GetQueueFamilyProperties();
		for (std::size_t i = 0; i < properties.size(); ++i)
		{
			if ((properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
			{
				queue_family_index = static_cast<std::uint32_t>(i);
				break;
			}
		}

		float const queue_priorities[1] = {0.0};

		vk::DeviceQueueCreateInfo queue_info;
		queue_info.queueCount       = 1;
		queue_info.queueFamilyIndex = queue_family_index;
		queue_info.pQueuePriorities = queue_priorities;

		static const char* layers[] =
		{
			"VK_LAYER_LUNARG_standard_validation"
		};

		static const char* extensions[] =
		{
			"VK_KHR_swapchain"
		};

		vk::DeviceCreateInfo device_info;
		device_info.queueCreateInfoCount = 1;
		device_info.pQueueCreateInfos    = &queue_info;
		device_info.SetEnabledLayers(layers);
		device_info.SetEnabledExtensions(extensions);

		m_device = std::make_shared<vk::Device>(m_gpus[0], device_info);
	}

	// Init Device Queue
	{
		vk::GetDeviceQueue(*m_device, queue_family_index, 0, &m_graphics_queue);
		//if (info.graphics_queue_family_index == info.present_queue_family_index)
		//{
		//	info.present_queue = info.graphics_queue;
		//}
		//else
		//{
		//	vkGetDeviceQueue(info.device, info.present_queue_family_index, 0, &info.present_queue);
		//}
	}

	// Init Command Pool
	{
		vk::CommandPoolCreateInfo cmd_pool_info;
		cmd_pool_info.queueFamilyIndex = queue_family_index;
		cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		m_command_pool = bksge::make_unique<vk::CommandPool>(m_device, cmd_pool_info);
	}

	// Init Command Buffer
	{
		vk::CommandBufferAllocateInfo cmd_buf_info;
		cmd_buf_info.commandPool        = *m_command_pool;
		cmd_buf_info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		cmd_buf_info.commandBufferCount = 1;

		m_command_buffer = bksge::make_unique<vk::CommandBuffer>(m_device, cmd_buf_info);
	}

	// Init Fence
	{
		vk::FenceCreateInfo fence_info;
		m_fence = bksge::make_unique<vk::Fence>(m_device, fence_info);
	}
}

BKSGE_INLINE
VulkanRenderer::~VulkanRenderer()
{
}

BKSGE_INLINE void
VulkanRenderer::VSetRenderTarget(
	Window const& window)
{
/* Number of descriptor sets needs to be the same at alloc,       */
/* pipeline layout creation, and descriptor set layout creation   */
#define NUM_DESCRIPTOR_SETS 1

/* Number of samples needs to be the same at image creation,      */
/* renderpass creation and pipeline creation.                     */
#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT

/* Number of viewports and number of scissors have to be the same */
/* at pipeline creation and in any call to set them dynamically   */
/* They also have to be the same as each other                    */
#define NUM_VIEWPORTS 1
#define NUM_SCISSORS NUM_VIEWPORTS

	// Init Surface
	m_surface = bksge::make_unique<vk::Surface>(m_instance, window);

	// Init Swapchain
	{
		::VkSurfaceCapabilitiesKHR surf_caps;
		vk::GetPhysicalDeviceSurfaceCapabilitiesKHR(m_gpus[0], *m_surface, &surf_caps);

		auto surf_formats = m_gpus[0].GetSurfaceFormats(*m_surface);

		::VkFormat surf_format = VK_FORMAT_B8G8R8A8_UNORM;
		if (!surf_formats.empty() && surf_formats[0].format != VK_FORMAT_UNDEFINED)
		{
			surf_format = surf_formats[0].format;
		}

		::VkExtent2D swapchainExtent = surf_caps.currentExtent;

		::VkSurfaceTransformFlagBitsKHR preTransform;
		if (surf_caps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
		{
			preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		}
		else
		{
			preTransform = surf_caps.currentTransform;
		}

		::VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		::VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] =
		{
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
		};

		for (auto flag : compositeAlphaFlags)
		{
			if (surf_caps.supportedCompositeAlpha & flag)
			{
				compositeAlpha = flag;
				break;
			}
		}

		vk::SwapchainCreateInfoKHR swapchain_ci;
		swapchain_ci.surface               = *m_surface;
		swapchain_ci.minImageCount         = surf_caps.minImageCount;
		swapchain_ci.imageFormat           = surf_format;
		swapchain_ci.imageExtent.width     = swapchainExtent.width;
		swapchain_ci.imageExtent.height    = swapchainExtent.height;
		swapchain_ci.preTransform          = preTransform;
		swapchain_ci.compositeAlpha        = compositeAlpha;
		swapchain_ci.imageArrayLayers      = 1;
		swapchain_ci.presentMode           = VK_PRESENT_MODE_FIFO_KHR;
		swapchain_ci.oldSwapchain          = VK_NULL_HANDLE;
		swapchain_ci.clipped               = VK_TRUE;
		swapchain_ci.imageColorSpace       = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		swapchain_ci.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchain_ci.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
		swapchain_ci.queueFamilyIndexCount = 0;
		swapchain_ci.pQueueFamilyIndices   = nullptr;

		//uint32_t queueFamilyIndices[2] =
		//{
		//	(uint32_t)info.graphics_queue_family_index,
		//	(uint32_t)info.present_queue_family_index
		//};
		//if (info.graphics_queue_family_index != info.present_queue_family_index)
		//{
		//	// If the graphics and present queues are from different queue families,
		//	// we either have to explicitly transfer ownership of images between
		//	// the queues, or we have to create the swapchain with imageSharingMode
		//	// as VK_SHARING_MODE_CONCURRENT
		//	swapchain_ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		//	swapchain_ci.queueFamilyIndexCount = 2;
		//	swapchain_ci.pQueueFamilyIndices = queueFamilyIndices;
		//}

		m_swapchain = bksge::make_unique<vk::Swapchain>(m_device, swapchain_ci);
	}

	// Init Image Views
	{
		auto images = m_swapchain->GetImages();
		for (auto&& image : images)
		{
			vk::ImageViewCreateInfo color_image_view;
			color_image_view.flags                           = 0;
			color_image_view.image                           = image;
			color_image_view.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
			color_image_view.format                          = m_swapchain->format();
			color_image_view.components.r                    = VK_COMPONENT_SWIZZLE_R;
			color_image_view.components.g                    = VK_COMPONENT_SWIZZLE_G;
			color_image_view.components.b                    = VK_COMPONENT_SWIZZLE_B;
			color_image_view.components.a                    = VK_COMPONENT_SWIZZLE_A;
			color_image_view.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
			color_image_view.subresourceRange.baseMipLevel   = 0;
			color_image_view.subresourceRange.levelCount     = 1;
			color_image_view.subresourceRange.baseArrayLayer = 0;
			color_image_view.subresourceRange.layerCount     = 1;

			m_image_views.push_back(std::make_shared<vk::ImageView>(m_device, color_image_view));
		}
	}

	// Init Render Pass
	{
		::VkAttachmentDescription attachment_desc;
		attachment_desc.format         = m_swapchain->format();
		attachment_desc.samples        = NUM_SAMPLES;
		attachment_desc.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachment_desc.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
		attachment_desc.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment_desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment_desc.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
		attachment_desc.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		attachment_desc.flags          = 0;

		::VkAttachmentReference color_reference = {};
		color_reference.attachment = 0;
		color_reference.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		::VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.flags                   = 0;
		subpass.inputAttachmentCount    = 0;
		subpass.pInputAttachments       = nullptr;
		subpass.colorAttachmentCount    = 1;
		subpass.pColorAttachments       = &color_reference;
		subpass.pResolveAttachments     = nullptr;
		subpass.pDepthStencilAttachment = nullptr;
		subpass.preserveAttachmentCount = 0;
		subpass.pPreserveAttachments    = nullptr;

		vk::RenderPassCreateInfo rp_info;
		rp_info.attachmentCount = 1;
		rp_info.pAttachments    = &attachment_desc;
		rp_info.subpassCount    = 1;
		rp_info.pSubpasses      = &subpass;
		rp_info.dependencyCount = 0;
		rp_info.pDependencies   = nullptr;

		m_render_pass = bksge::make_unique<vk::RenderPass>(m_device, rp_info);
	}

	// Init Frame Buffers
	{
		::VkImageView attachments[1];

		vk::FramebufferCreateInfo fb_info;
		fb_info.renderPass      = *m_render_pass;
		fb_info.attachmentCount = 1;
		fb_info.pAttachments    = attachments;
		fb_info.width           = m_swapchain->width();
		fb_info.height          = m_swapchain->height();
		fb_info.layers          = 1;

		for (auto&& image_view : m_image_views)
		{
			attachments[0] = *image_view;

			m_framebuffers.push_back(std::make_shared<vk::Framebuffer>(m_device, fb_info));
		}

//		execute_end_command_buffer(info);
//		execute_queue_command_buffer(info);
	}

	// Init DescriptorSet Layout
	{
		vk::DescriptorSetLayoutBinding layout_binding;
		layout_binding.binding            = 0;
		layout_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layout_binding.descriptorCount    = 1;
		layout_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
		layout_binding.pImmutableSamplers = nullptr;

		vk::DescriptorSetLayoutCreateInfo descriptor_layout;
		descriptor_layout.bindingCount = 1;
		descriptor_layout.pBindings    = &layout_binding;

		m_descriptor_set_layout = bksge::make_unique<vk::DescriptorSetLayout>(m_device, descriptor_layout, NUM_DESCRIPTOR_SETS);
	}

	// Init Pipeline Layout
	{
		vk::PipelineLayoutCreateInfo pPipelineLayoutCreateInfo;
		pPipelineLayoutCreateInfo.setLayoutCount         = NUM_DESCRIPTOR_SETS;
		pPipelineLayoutCreateInfo.pSetLayouts            = m_descriptor_set_layout->get();
		pPipelineLayoutCreateInfo.pushConstantRangeCount = 0;
		pPipelineLayoutCreateInfo.pPushConstantRanges    = nullptr;

		m_pipeline_layout = bksge::make_unique<vk::PipelineLayout>(m_device, pPipelineLayoutCreateInfo);
	}

	bool use_texture = false;

	// Init Descriptor Pool
	{
		::VkDescriptorPoolSize type_count[2];
		type_count[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		type_count[0].descriptorCount = 1;
		if (use_texture)
		{
			type_count[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			type_count[1].descriptorCount = 1;
		}

		vk::DescriptorPoolCreateInfo descriptor_pool;
		descriptor_pool.maxSets = 1;
		descriptor_pool.poolSizeCount = use_texture ? 2 : 1;
		descriptor_pool.pPoolSizes = type_count;

		m_descriptor_pool = bksge::make_unique<vk::DescriptorPool>(m_device, descriptor_pool);
	}

	// Init Descriptor Set
	{
		vk::DescriptorSetAllocateInfo alloc_info;
		alloc_info.descriptorPool = *m_descriptor_pool;
		alloc_info.descriptorSetCount = NUM_DESCRIPTOR_SETS;
		alloc_info.pSetLayouts = m_descriptor_set_layout->get();

		m_descriptor_set = bksge::make_unique<vk::DescriptorSet>(m_device, alloc_info, NUM_DESCRIPTOR_SETS);
#if 0
		VkWriteDescriptorSet writes[2];

		writes[0] = {};
		writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writes[0].pNext = nullptr;
		writes[0].dstSet = info.desc_set[0];
		writes[0].descriptorCount = 1;
		writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		writes[0].pBufferInfo = &info.uniform_data.buffer_info;
		writes[0].dstArrayElement = 0;
		writes[0].dstBinding = 0;

		if (use_texture)
		{
			writes[1] = {};
			writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			writes[1].dstSet = info.desc_set[0];
			writes[1].dstBinding = 1;
			writes[1].descriptorCount = 1;
			writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			writes[1].pImageInfo = &info.texture_data.image_info;
			writes[1].dstArrayElement = 0;
		}

		vkUpdateDescriptorSets(info.device, use_texture ? 2 : 1, writes, 0, nullptr);
#endif
	}

	// Init Pipeline Cache
	{
		vk::PipelineCacheCreateInfo pipelineCache;
		m_pipeline_cache = bksge::make_unique<vk::PipelineCache>(m_device, pipelineCache);
	}
}

BKSGE_INLINE void
VulkanRenderer::VBegin(void)
{
	// BeginCommandWithFramebuffer
	{
		vk::CommandBufferInheritanceInfo inh_info{};
		inh_info.framebuffer = *m_framebuffers[m_current_frame_index];

		vk::CommandBufferBeginInfo begin_info{};
		begin_info.pInheritanceInfo = &inh_info;

		vk::BeginCommandBuffer(*m_command_buffer, &begin_info);
	}

	//Vulkan::barrierResource(cmdBuffers[0], images.first[currentFrameIndex],
	//	VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	//	VK_ACCESS_MEMORY_READ_BIT, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
	//	VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
	{
	}

	// BeginRenderPass
	{
		static ::VkClearValue clearValue
		{
			{{0.0f, 1.0f, 0.0f, 1.0f}}
		};

		vk::RenderPassBeginInfo rpinfo{};
		rpinfo.framebuffer              = *m_framebuffers[m_current_frame_index];
		rpinfo.renderPass               = *m_render_pass;
		rpinfo.renderArea.extent.width  = m_swapchain->width();
		rpinfo.renderArea.extent.height = m_swapchain->height();
		rpinfo.clearValueCount          = 1;
		rpinfo.pClearValues             = &clearValue;

		vk::CmdBeginRenderPass(*m_command_buffer, &rpinfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	if (m_pipeline)
	{
		vk::CmdBindPipeline(*m_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *m_pipeline);
	}

//	vkCmdSetViewport(*m_command_buffer, 0, 1, &vp);
//	vkCmdSetScissor(*m_command_buffer, 0, 1, &sc);
}

BKSGE_INLINE void
VulkanRenderer::VEnd(void)
{
	vk::CmdEndRenderPass(*m_command_buffer);
	/*
	Vulkan::barrierResource(cmdBuffers[0], images.first[currentFrameIndex],
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
		VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_ACCESS_MEMORY_READ_BIT,
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
	*/
	vk::EndCommandBuffer(*m_command_buffer);

	// Submit and Wait with Fences
	{
		static const ::VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

		::VkSubmitInfo sinfo{};
		sinfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		sinfo.commandBufferCount = 1;
		sinfo.pCommandBuffers = m_command_buffer->GetAddress();
		sinfo.pWaitDstStageMask = &waitStageMask;
		vk::QueueSubmit(m_graphics_queue, 1, &sinfo, *m_fence);
	}

	switch (vk::WaitForFences(*m_device, 1, m_fence->GetAddress(), VK_TRUE, UINT64_MAX))
	{
	case VK_SUCCESS:
		{
			::VkPresentInfoKHR pinfo{};

			pinfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			pinfo.swapchainCount = 1;
			pinfo.pSwapchains = m_swapchain->GetAddress();
			pinfo.pImageIndices = &m_current_frame_index;

			vk::QueuePresentKHR(m_graphics_queue, &pinfo);
		}
		break;
	default:
		break;
	}
	vk::ResetFences(*m_device, 1, m_fence->GetAddress());

	// Acquire next
	{
		vk::AcquireNextImageKHR(*m_device, *m_swapchain, UINT64_MAX, VK_NULL_HANDLE, *m_fence, &m_current_frame_index);
		vk::WaitForFences(*m_device, 1, m_fence->GetAddress(), VK_FALSE, UINT64_MAX);
		vk::ResetFences(*m_device, 1, m_fence->GetAddress());
	}
}

BKSGE_INLINE void
VulkanRenderer::VClear(
	ClearFlag /*clear_flag*/,
	Color4f const& /*clear_color*/)
{}

BKSGE_INLINE bool
VulkanRenderer::VRender(
	Geometry const& /*geometry*/,
	Shader const& shader,
	ShaderParameterMap const& /*shader_parameter_map*/,
	RenderState const& /*render_state*/)
{
	if (shader.type() != ShaderType::kGLSL)
	{
		return false;
	}

	// Init Shaders
	if (!m_shader_stages)
	{
		m_shader_stages = bksge::make_unique<vk::ShaderStages>(m_device, shader);
	}

	// Init Pipeline
	if (!m_pipeline)
	{
		std::vector<::VkDynamicState> dynamicStateEnables;

		vk::PipelineVertexInputStateCreateInfo vi;
		//if (include_vi)
		//{
		//	vi.vertexBindingDescriptionCount = 1;
		//	vi.pVertexBindingDescriptions = &info.vi_binding;
		//	vi.vertexAttributeDescriptionCount = 2;
		//	vi.pVertexAttributeDescriptions = info.vi_attribs;
		//}

		vk::PipelineInputAssemblyStateCreateInfo ia;
		ia.primitiveRestartEnable = VK_FALSE;
		ia.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		vk::PipelineRasterizationStateCreateInfo rs;
		rs.polygonMode             = VK_POLYGON_MODE_FILL;
		rs.cullMode                = VK_CULL_MODE_BACK_BIT;
		rs.frontFace               = VK_FRONT_FACE_CLOCKWISE;
		rs.depthClampEnable        = VK_FALSE;
		rs.rasterizerDiscardEnable = VK_FALSE;
		rs.depthBiasEnable         = VK_FALSE;
		rs.depthBiasConstantFactor = 0;
		rs.depthBiasClamp          = 0;
		rs.depthBiasSlopeFactor    = 0;
		rs.lineWidth               = 1.0f;

		::VkPipelineColorBlendAttachmentState att_state[1];
		att_state[0].colorWriteMask      = 0xf;
		att_state[0].blendEnable         = VK_FALSE;
		att_state[0].alphaBlendOp        = VK_BLEND_OP_ADD;
		att_state[0].colorBlendOp        = VK_BLEND_OP_ADD;
		att_state[0].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		att_state[0].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		att_state[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		att_state[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

		vk::PipelineColorBlendStateCreateInfo cb;
		cb.attachmentCount   = 1;
		cb.pAttachments      = att_state;
		cb.logicOpEnable     = VK_FALSE;
		cb.logicOp           = VK_LOGIC_OP_NO_OP;
		cb.blendConstants[0] = 1.0f;
		cb.blendConstants[1] = 1.0f;
		cb.blendConstants[2] = 1.0f;
		cb.blendConstants[3] = 1.0f;

		vk::PipelineViewportStateCreateInfo vp;
#ifndef __ANDROID__
		vp.viewportCount = NUM_VIEWPORTS;
		vp.scissorCount = NUM_SCISSORS;
		vp.pScissors = nullptr;
		vp.pViewports = nullptr;
		dynamicStateEnables.push_back(VK_DYNAMIC_STATE_VIEWPORT);
		dynamicStateEnables.push_back(VK_DYNAMIC_STATE_SCISSOR);
#else
		// Temporary disabling dynamic viewport on Android because some of drivers doesn't
		// support the feature.
		::VkViewport viewports;
		viewports.minDepth = 0.0f;
		viewports.maxDepth = 1.0f;
		viewports.x = 0;
		viewports.y = 0;
		viewports.width = static_cast<float>(m_swapchain->width());
		viewports.height = static_cast<float>(m_swapchain->height());
		::VkRect2D scissor;
		scissor.extent.width = m_swapchain->width();
		scissor.extent.height = m_swapchain->height();
		scissor.offset.x = 0;
		scissor.offset.y = 0;
		vp.viewportCount = NUM_VIEWPORTS;
		vp.scissorCount = NUM_SCISSORS;
		vp.pScissors = &scissor;
		vp.pViewports = &viewports;
#endif

		vk::PipelineDepthStencilStateCreateInfo ds;
		ds.flags                 = 0;
		ds.depthTestEnable       = VK_FALSE;//include_depth;
		ds.depthWriteEnable      = VK_FALSE;//include_depth;
		ds.depthCompareOp        = VK_COMPARE_OP_LESS_OR_EQUAL;
		ds.depthBoundsTestEnable = VK_FALSE;
		ds.stencilTestEnable     = VK_FALSE;
		ds.back.failOp           = VK_STENCIL_OP_KEEP;
		ds.back.passOp           = VK_STENCIL_OP_KEEP;
		ds.back.compareOp        = VK_COMPARE_OP_ALWAYS;
		ds.back.compareMask      = 0;
		ds.back.reference        = 0;
		ds.back.depthFailOp      = VK_STENCIL_OP_KEEP;
		ds.back.writeMask        = 0;
		ds.front                 = ds.back;
		ds.minDepthBounds        = 0;
		ds.maxDepthBounds        = 0;

		vk::PipelineMultisampleStateCreateInfo ms;
		ms.flags                 = 0;
		ms.pSampleMask           = nullptr;
		ms.rasterizationSamples  = NUM_SAMPLES;
		ms.sampleShadingEnable   = VK_FALSE;
		ms.alphaToCoverageEnable = VK_FALSE;
		ms.alphaToOneEnable      = VK_FALSE;
		ms.minSampleShading      = 0.0;

		vk::PipelineDynamicStateCreateInfo dynamicState;
		dynamicState.pDynamicStates    = dynamicStateEnables.data();
		dynamicState.dynamicStateCount = static_cast<std::uint32_t>(dynamicStateEnables.size());

		vk::GraphicsPipelineCreateInfo pipeline;
		pipeline.layout              = *m_pipeline_layout;
		pipeline.basePipelineHandle  = VK_NULL_HANDLE;
		pipeline.basePipelineIndex   = 0;
		pipeline.flags               = 0;
		pipeline.pVertexInputState   = &vi;
		pipeline.pInputAssemblyState = &ia;
		pipeline.pRasterizationState = &rs;
		pipeline.pColorBlendState    = &cb;
		pipeline.pTessellationState  = nullptr;
		pipeline.pMultisampleState   = &ms;
		pipeline.pDynamicState       = &dynamicState;
		pipeline.pViewportState      = &vp;
		pipeline.pDepthStencilState  = &ds;
		pipeline.pStages             = m_shader_stages->GetPtr();
		pipeline.stageCount          = m_shader_stages->GetCount();
		pipeline.renderPass          = *m_render_pass;
		pipeline.subpass             = 0;

		m_pipeline = bksge::make_unique<vk::GraphicsPipeline>(m_device, *m_pipeline_cache, pipeline);
	}

	return true;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_INL_VULKAN_RENDERER_INL_HPP
