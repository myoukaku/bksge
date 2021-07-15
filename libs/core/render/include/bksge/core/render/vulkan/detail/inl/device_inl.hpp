/**
 *	@file	device_inl.hpp
 *
 *	@brief	Device クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/algorithm/ranges/find.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline bksge::vector<bksge::string>
EnumerateDeviceLayerNames(vulkan::PhysicalDevice const& physical_device)
{
	bksge::vector<bksge::string> result;

	auto layer_properties = physical_device.EnumerateDeviceLayerProperties();
	for (auto&& layer_property : layer_properties)
	{
		result.push_back(layer_property.layerName);
	}

	return result;
}

inline bksge::vector<bksge::string>
EnumerateDeviceExtensionNames(vulkan::PhysicalDevice const& physical_device)
{
	bksge::vector<bksge::string> result;

	auto extension_properties =
		physical_device.EnumerateDeviceExtensionProperties(nullptr);
	for (auto&& extension_property : extension_properties)
	{
		result.push_back(extension_property.extensionName);
	}

	auto layer_properties = physical_device.EnumerateDeviceLayerProperties();
	for (auto&& layer_property : layer_properties)
	{
		auto layer_extension_properties =
			physical_device.EnumerateDeviceExtensionProperties(layer_property.layerName);
		for (auto&& layer_extension_property : layer_extension_properties)
		{
			result.push_back(layer_extension_property.extensionName);
		}
	}

	return result;
}

}	// namespace detail

BKSGE_INLINE
Device::Device(vulkan::PhysicalDeviceSharedPtr const& physical_device)
	: m_device(VK_NULL_HANDLE)
	, m_physical_device(physical_device)
{
	bksge::vector<char const*> layer_names;
	{
		// 追加可能なレイヤーを全てリストアップ
		auto const available_layer_names =
			detail::EnumerateDeviceLayerNames(*physical_device);

		// 追加したいレイヤー
		bksge::vector<char const*> desired_layer_names =
		{
#if defined(_DEBUG)
			"VK_LAYER_KHRONOS_validation",
			"VK_LAYER_LUNARG_standard_validation",
#endif
		};

		// 可能であればレイヤーを追加
		for (auto desired_layer_name: desired_layer_names)
		{
			if (bksge::ranges::find(available_layer_names, desired_layer_name) != available_layer_names.end())
			{
				layer_names.push_back(desired_layer_name);
			}
		}
	}

	bksge::vector<char const*> extension_names;
	{
		// 追加可能な拡張を全てリストアップ
		auto const available_extension_names =
			detail::EnumerateDeviceExtensionNames(*physical_device);

		// 追加したい拡張
		bksge::vector<char const*> desired_extension_names =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
			VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME,
			VK_KHR_MAINTENANCE1_EXTENSION_NAME,
		};

		// 可能であれば拡張を追加
		for (auto desired_extension_name: desired_extension_names)
		{
			if (bksge::ranges::find(available_extension_names, desired_extension_name) != available_extension_names.end())
			{
				extension_names.push_back(desired_extension_name);
			}
		}
	}

	float const queue_priorities = 0.0;

	vk::DeviceQueueCreateInfo queue_info;
	queue_info.flags            = 0;
	queue_info.queueFamilyIndex = physical_device->GetGraphicsQueueFamilyIndex();
	queue_info.queueCount       = 1;
	queue_info.pQueuePriorities = &queue_priorities;

	auto const enabled_features = physical_device->GetFeatures();

	vk::DeviceCreateInfo info;
	info.SetQueueCreateInfos(queue_info);
	info.SetEnabledLayerNames(layer_names);
	info.SetEnabledExtensionNames(extension_names);
	info.pEnabledFeatures = &enabled_features;

	m_device = physical_device->CreateDevice(info);
}

BKSGE_INLINE
Device::~Device()
{
	this->WaitIdle();
	vk::DestroyDevice(m_device, nullptr);
}

BKSGE_INLINE ::VkQueue
Device::GetQueue(std::uint32_t queue_family_index, std::uint32_t queue_index)
{
	::VkQueue queue;
	vk::GetDeviceQueue(m_device, queue_family_index, queue_index, &queue);
	return queue;
}

BKSGE_INLINE void
Device::WaitIdle(void)
{
	vk::DeviceWaitIdle(m_device);
}

BKSGE_INLINE vulkan::PhysicalDeviceSharedPtr const&
Device::physical_device(void) const
{
	return m_physical_device;
}

BKSGE_INLINE ::VkDeviceMemory
Device::AllocateMemory(vk::MemoryAllocateInfo const& info)
{
	::VkDeviceMemory device_memory;
	vk::AllocateMemory(m_device, &info, nullptr, &device_memory);
	return device_memory;
}

BKSGE_INLINE void
Device::FreeMemory(::VkDeviceMemory device_memory)
{
	vk::FreeMemory(m_device, device_memory, nullptr);
}

BKSGE_INLINE void*
Device::MapMemory(::VkDeviceMemory device_memory, ::VkDeviceSize size)
{
	void* dst;
	vk::MapMemory(m_device, device_memory, 0, size, 0, &dst);
	return dst;
}

BKSGE_INLINE void
Device::UnmapMemory(::VkDeviceMemory device_memory)
{
	vk::UnmapMemory(m_device, device_memory);
}

BKSGE_INLINE ::VkFence
Device::CreateFence(vk::FenceCreateInfo const& info)
{
	::VkFence fence;
	vk::CreateFence(m_device, &info, nullptr, &fence);
	return fence;
}

BKSGE_INLINE void
Device::DestroyFence(::VkFence fence)
{
	vk::DestroyFence(m_device, fence, nullptr);
}

BKSGE_INLINE ::VkResult
Device::ResetFences(std::uint32_t fence_count, ::VkFence const* fences)
{
	return vk::ResetFences(m_device, fence_count, fences);
}

BKSGE_INLINE ::VkResult
Device::WaitForFences(
	std::uint32_t    fence_count,
	::VkFence const* fences,
	::VkBool32       wait_all,
	std::uint64_t    timeout)
{
	return vk::WaitForFences(
		m_device, fence_count, fences, wait_all, timeout);
}

BKSGE_INLINE ::VkSemaphore
Device::CreateSemaphore(vk::SemaphoreCreateInfo const& create_info)
{
	::VkSemaphore semaphore;
	vk::CreateSemaphore(m_device, &create_info, nullptr, &semaphore);
	return semaphore;
}

BKSGE_INLINE void
Device::DestroySemaphore(::VkSemaphore semaphore)
{
	vk::DestroySemaphore(m_device, semaphore, nullptr);
}

BKSGE_INLINE ::VkBuffer
Device::CreateBuffer(::VkDeviceSize size, ::VkBufferUsageFlags usage)
{
	vk::BufferCreateInfo info;
    info.size        = size;
    info.usage       = usage;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.SetQueueFamilyIndices(nullptr);

	::VkBuffer buffer;
	vk::CreateBuffer(m_device, &info, nullptr, &buffer);
	return buffer;
}

BKSGE_INLINE void
Device::DestroyBuffer(::VkBuffer buffer)
{
	vk::DestroyBuffer(m_device, buffer, nullptr);
}

BKSGE_INLINE void
Device::BindBufferMemory(
	::VkBuffer       buffer,
	::VkDeviceMemory memory,
	::VkDeviceSize   memory_offset)
{
	vk::BindBufferMemory(m_device, buffer, memory, memory_offset);
}

BKSGE_INLINE ::VkMemoryRequirements
Device::GetBufferMemoryRequirements(::VkBuffer buffer) const
{
	::VkMemoryRequirements mem_reqs;
	vk::GetBufferMemoryRequirements(m_device, buffer, &mem_reqs);
	return mem_reqs;
}

BKSGE_INLINE ::VkImage
Device::CreateImage(vk::ImageCreateInfo const& create_info)
{
	::VkImage image;
	vk::CreateImage(m_device, &create_info, nullptr, &image);
	return image;
}

BKSGE_INLINE void
Device::DestroyImage(::VkImage image)
{
	vk::DestroyImage(m_device, image, nullptr);
}

BKSGE_INLINE void
Device::BindImageMemory(::VkImage image, ::VkDeviceMemory memory, ::VkDeviceSize memory_offset)
{
	vk::BindImageMemory(m_device, image, memory, memory_offset);
}

BKSGE_INLINE ::VkMemoryRequirements
Device::GetImageMemoryRequirements(::VkImage image)
{
	::VkMemoryRequirements mem_reqs;
	vk::GetImageMemoryRequirements(m_device, image, &mem_reqs);
	return mem_reqs;
}

BKSGE_INLINE ::VkImageView
Device::CreateImageView(vk::ImageViewCreateInfo const& create_info)
{
	::VkImageView image_view;
	vk::CreateImageView(m_device, &create_info, nullptr, &image_view);
	return image_view;
}

BKSGE_INLINE void
Device::DestroyImageView(::VkImageView image_view)
{
	vk::DestroyImageView(m_device, image_view, nullptr);
}

BKSGE_INLINE ::VkShaderModule
Device::CreateShaderModule(vk::ShaderModuleCreateInfo const& create_info)
{
	::VkShaderModule shader_module;
	vk::CreateShaderModule(
		m_device,
		&create_info,
		nullptr,
		&shader_module);
	return shader_module;
}

BKSGE_INLINE void
Device::DestroyShaderModule(::VkShaderModule shader_module)
{
	vk::DestroyShaderModule(m_device, shader_module, nullptr);
}

BKSGE_INLINE ::VkPipelineCache
Device::CreatePipelineCache(vk::PipelineCacheCreateInfo const& create_info)
{
	::VkPipelineCache pipeline_cache;
	vk::CreatePipelineCache(m_device, &create_info, nullptr, &pipeline_cache);
	return pipeline_cache;
}

BKSGE_INLINE void
Device::DestroyPipelineCache(::VkPipelineCache pipeline_cache)
{
	vk::DestroyPipelineCache(m_device, pipeline_cache, nullptr);
}

BKSGE_INLINE ::VkPipeline
Device::CreateGraphicsPipeline(
	::VkPipelineCache                     pipeline_cache,
	vk::GraphicsPipelineCreateInfo const& create_info)
{
	::VkPipeline pipeline;
	vk::CreateGraphicsPipelines(
		m_device,
		pipeline_cache,
		1,
		&create_info,
		nullptr,
		&pipeline);
	return pipeline;
}

BKSGE_INLINE void
Device::DestroyPipeline(::VkPipeline pipeline)
{
	vk::DestroyPipeline(m_device, pipeline, nullptr);
}

BKSGE_INLINE ::VkPipelineLayout
Device::CreatePipelineLayout(vk::PipelineLayoutCreateInfo const& create_info)
{
	::VkPipelineLayout pipeline_layout;
	vk::CreatePipelineLayout(m_device, &create_info, nullptr, &pipeline_layout);
	return pipeline_layout;
}

BKSGE_INLINE void
Device::DestroyPipelineLayout(::VkPipelineLayout pipeline_layout)
{
	vk::DestroyPipelineLayout(m_device, pipeline_layout, nullptr);
}

BKSGE_INLINE ::VkSampler
Device::CreateSampler(vk::SamplerCreateInfo const& create_info)
{
	::VkSampler sampler;
	vk::CreateSampler(m_device, &create_info, nullptr, &sampler);
	return sampler;
}

BKSGE_INLINE void
Device::DestroySampler(::VkSampler sampler)
{
	vk::DestroySampler(m_device, sampler, nullptr);
}

BKSGE_INLINE ::VkDescriptorSetLayout
Device::CreateDescriptorSetLayout(vk::DescriptorSetLayoutCreateInfo const& create_info)
{
	::VkDescriptorSetLayout descriptor_set_layout;
	vk::CreateDescriptorSetLayout(
		m_device, &create_info, nullptr, &descriptor_set_layout);
	return descriptor_set_layout;
}

BKSGE_INLINE void
Device::DestroyDescriptorSetLayout(::VkDescriptorSetLayout descriptor_set_layout)
{
	vk::DestroyDescriptorSetLayout(m_device, descriptor_set_layout, nullptr);
}

BKSGE_INLINE ::VkDescriptorPool
Device::CreateDescriptorPool(vk::DescriptorPoolCreateInfo const& create_info)
{
	::VkDescriptorPool descriptor_pool;
	vk::CreateDescriptorPool(m_device, &create_info, nullptr, &descriptor_pool);
	return descriptor_pool;
}

BKSGE_INLINE void
Device::DestroyDescriptorPool(::VkDescriptorPool descriptor_pool)
{
	vk::DestroyDescriptorPool(m_device, descriptor_pool, nullptr);
}

BKSGE_INLINE bksge::vector<::VkDescriptorSet>
Device::AllocateDescriptorSets(
	vk::DescriptorSetAllocateInfo const& allocate_info)
{
	bksge::vector<::VkDescriptorSet> descriptor_sets(allocate_info.descriptorSetCount);
	vk::AllocateDescriptorSets(m_device, &allocate_info, descriptor_sets.data());
	return descriptor_sets;
}

BKSGE_INLINE void
Device::FreeDescriptorSets(
	::VkDescriptorPool                      descriptor_pool,
	bksge::vector<::VkDescriptorSet> const& descriptor_sets)
{
	vk::FreeDescriptorSets(
		m_device,
		descriptor_pool,
		static_cast<std::uint32_t>(descriptor_sets.size()),
		descriptor_sets.data());
}

BKSGE_INLINE void
Device::PushDescriptorSet(
	::VkCommandBuffer                            command_buffer,
	::VkPipelineBindPoint                        pipeline_bind_point,
	::VkPipelineLayout                           layout,
	std::uint32_t                                set,
	bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes)
{
	if (!descriptor_writes.empty())
	{
		vk::CmdPushDescriptorSetKHR(
			m_device,
			command_buffer,
			pipeline_bind_point,
			layout,
			set,
			static_cast<std::uint32_t>(descriptor_writes.size()),
			descriptor_writes.data());
	}
}

BKSGE_INLINE ::VkFramebuffer
Device::CreateFramebuffer(vk::FramebufferCreateInfo const& create_info)
{
	::VkFramebuffer framebuffer;
	vk::CreateFramebuffer(m_device, &create_info, nullptr, &framebuffer);
	return framebuffer;
}

BKSGE_INLINE void
Device::DestroyFramebuffer(::VkFramebuffer framebuffer)
{
	vk::DestroyFramebuffer(m_device, framebuffer, nullptr);
}

BKSGE_INLINE ::VkRenderPass
Device::CreateRenderPass(vk::RenderPassCreateInfo const& create_info)
{
	::VkRenderPass render_pass;
	vk::CreateRenderPass(m_device, &create_info, nullptr, &render_pass);
	return render_pass;
}

BKSGE_INLINE void
Device::DestroyRenderPass(::VkRenderPass render_pass)
{
	vk::DestroyRenderPass(m_device, render_pass, nullptr);
}

BKSGE_INLINE ::VkCommandPool
Device::CreateCommandPool(
	::VkCommandPoolCreateFlags flags,
	std::uint32_t queue_family_index)
{
	vk::CommandPoolCreateInfo info;
	info.flags            = flags;
	info.queueFamilyIndex = queue_family_index;

	::VkCommandPool command_pool;
	vk::CreateCommandPool(m_device, &info, nullptr, &command_pool);
	return command_pool;
}

BKSGE_INLINE void
Device::DestroyCommandPool(::VkCommandPool command_pool)
{
	vk::DestroyCommandPool(m_device, command_pool, nullptr);
}

BKSGE_INLINE ::VkCommandBuffer
Device::AllocateCommandBuffer(::VkCommandPool command_pool, ::VkCommandBufferLevel level)
{
	vk::CommandBufferAllocateInfo create_info;
	create_info.commandPool        = command_pool;
	create_info.level              = level;
	create_info.commandBufferCount = 1;

	::VkCommandBuffer command_buffer;
	vk::AllocateCommandBuffers(m_device, &create_info, &command_buffer);
	return command_buffer;
}

BKSGE_INLINE void
Device::FreeCommandBuffer(::VkCommandPool command_pool, ::VkCommandBuffer command_buffer)
{
	vk::FreeCommandBuffers(m_device, command_pool, 1, &command_buffer);
}

BKSGE_INLINE ::VkSwapchainKHR
Device::CreateSwapchain(vk::SwapchainCreateInfoKHR const& create_info)
{
	::VkSwapchainKHR swapchain;
	vk::CreateSwapchainKHR(m_device, &create_info, nullptr, &swapchain);
	return swapchain;
}

BKSGE_INLINE void
Device::DestroySwapchain(::VkSwapchainKHR swapchain)
{
	vk::DestroySwapchainKHR(m_device, swapchain, nullptr);
}

BKSGE_INLINE bksge::vector<::VkImage>
Device::GetSwapchainImages(::VkSwapchainKHR swapchain) const
{
	std::uint32_t count = 0;
	vk::GetSwapchainImagesKHR(m_device, swapchain, &count, nullptr);

	bksge::vector<::VkImage> images(count);
	vk::GetSwapchainImagesKHR(m_device, swapchain, &count, images.data());

	return images;
}

BKSGE_INLINE ::VkResult
Device::AcquireNextImage(
	::VkSwapchainKHR swapchain,
	std::uint64_t    timeout,
	::VkSemaphore    semaphore,
	::VkFence        fence,
	std::uint32_t*   image_index)
{
	return vk::AcquireNextImageKHR(
		m_device,
		swapchain,
		timeout,
		semaphore,
		fence,
		image_index);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP
