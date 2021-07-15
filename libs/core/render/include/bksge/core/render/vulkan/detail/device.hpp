/**
 *	@file	device.hpp
 *
 *	@brief	Device クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_HPP

#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/physical_device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Device
{
public:
	explicit Device(vulkan::PhysicalDeviceSharedPtr const& physical_device);

	~Device();

	::VkQueue GetQueue(std::uint32_t queue_family_index, std::uint32_t queue_index);

	void WaitIdle(void);

	vulkan::PhysicalDeviceSharedPtr const& physical_device(void) const;

	// DeviceMemory
	::VkDeviceMemory AllocateMemory(vk::MemoryAllocateInfo const& info);
	void FreeMemory(::VkDeviceMemory device_memory);
	void* MapMemory(::VkDeviceMemory device_memory, ::VkDeviceSize size);
	void UnmapMemory(::VkDeviceMemory device_memory);

	// Fence
	::VkFence CreateFence(vk::FenceCreateInfo const& info);
	void DestroyFence(::VkFence fence);
	::VkResult ResetFences(std::uint32_t fence_count, ::VkFence const* fences);
	::VkResult WaitForFences(
		std::uint32_t  fence_count,
		::VkFence const* fences,
		::VkBool32       wait_all,
		std::uint64_t  timeout);

	// Semaphore
	::VkSemaphore CreateSemaphore(vk::SemaphoreCreateInfo const& create_info);
	void DestroySemaphore(::VkSemaphore semaphore);

	// Buffer
	::VkBuffer CreateBuffer(::VkDeviceSize size, ::VkBufferUsageFlags usage);
	void DestroyBuffer(::VkBuffer buffer);
	void BindBufferMemory(::VkBuffer buffer, ::VkDeviceMemory memory, ::VkDeviceSize memory_offset);
	::VkMemoryRequirements GetBufferMemoryRequirements(::VkBuffer buffer) const;

	// Image
	::VkImage CreateImage(vk::ImageCreateInfo const& create_info);
	void DestroyImage(::VkImage image);
	void BindImageMemory(::VkImage image, ::VkDeviceMemory memory, ::VkDeviceSize memory_offset);
	::VkMemoryRequirements GetImageMemoryRequirements(::VkImage image);

	// ImageView
	::VkImageView CreateImageView(vk::ImageViewCreateInfo const& create_info);
	void DestroyImageView(::VkImageView image_view);

	// ShaderModule
	::VkShaderModule CreateShaderModule(vk::ShaderModuleCreateInfo const& create_info);
	void DestroyShaderModule(::VkShaderModule shader_module);

	// PipelineCache
	::VkPipelineCache CreatePipelineCache(vk::PipelineCacheCreateInfo const& create_info);
	void DestroyPipelineCache(::VkPipelineCache pipeline_cache);

	// Pipeline
	::VkPipeline CreateGraphicsPipeline(
		::VkPipelineCache                     pipeline_cache,
		vk::GraphicsPipelineCreateInfo const& create_info);
	//::VkPipeline CreateComputePipeline(
	//	::VkPipelineCache                    pipeline_cache,
	//	vk::ComputePipelineCreateInfo const& create_info);
	void DestroyPipeline(::VkPipeline pipeline);

	// PipelineLayout
	::VkPipelineLayout CreatePipelineLayout(vk::PipelineLayoutCreateInfo const& create_info);
	void DestroyPipelineLayout(::VkPipelineLayout pipeline_layout);

	// Sampler
	::VkSampler CreateSampler(vk::SamplerCreateInfo const& create_info);
	void DestroySampler(::VkSampler sampler);

	// DescriptorSetLayout
	::VkDescriptorSetLayout CreateDescriptorSetLayout(vk::DescriptorSetLayoutCreateInfo const& create_info);
	void DestroyDescriptorSetLayout(::VkDescriptorSetLayout descriptor_set_layout);

	// DescriptorPool
	::VkDescriptorPool CreateDescriptorPool(vk::DescriptorPoolCreateInfo const& create_info);
	void DestroyDescriptorPool(::VkDescriptorPool descriptor_pool);

	// DescriptorSet
	bksge::vector<::VkDescriptorSet> AllocateDescriptorSets(
		vk::DescriptorSetAllocateInfo const& allocate_info);
	void FreeDescriptorSets(
		::VkDescriptorPool                      descriptor_pool,
		bksge::vector<::VkDescriptorSet> const& descriptor_sets);
	void PushDescriptorSet(
		::VkCommandBuffer                            command_buffer,
		::VkPipelineBindPoint                        pipeline_bind_point,
		::VkPipelineLayout                           layout,
		std::uint32_t                              set,
		bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes);

	// Framebuffer
	::VkFramebuffer CreateFramebuffer(vk::FramebufferCreateInfo const& create_info);
	void DestroyFramebuffer(::VkFramebuffer framebuffer);

	// RenderPass
	::VkRenderPass CreateRenderPass(vk::RenderPassCreateInfo const& create_info);
	void DestroyRenderPass(::VkRenderPass render_pass);

	// CommandPool
	::VkCommandPool	CreateCommandPool(
		::VkCommandPoolCreateFlags flags,
		std::uint32_t queue_family_index);
	void DestroyCommandPool(::VkCommandPool command_pool);

	// CommandBuffer
	::VkCommandBuffer AllocateCommandBuffer(
		::VkCommandPool command_pool,
		::VkCommandBufferLevel level);
	void FreeCommandBuffer(
		::VkCommandPool command_pool,
		::VkCommandBuffer command_buffer);

	// Swapchain
	::VkSwapchainKHR CreateSwapchain(vk::SwapchainCreateInfoKHR const& create_info);
	void DestroySwapchain(::VkSwapchainKHR swapchain);
	bksge::vector<::VkImage> GetSwapchainImages(::VkSwapchainKHR swapchain) const;
	::VkResult AcquireNextImage(
		::VkSwapchainKHR swapchain,
		std::uint64_t  timeout,
		::VkSemaphore    semaphore,
		::VkFence        fence,
		std::uint32_t* image_index);

private:
	// noncopyable
	Device(Device const&) = delete;
	Device& operator=(Device const&) = delete;

private:
	::VkDevice						m_device;
	vulkan::PhysicalDeviceSharedPtr	m_physical_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/device_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_HPP
