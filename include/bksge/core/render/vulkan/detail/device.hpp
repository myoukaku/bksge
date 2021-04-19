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
#include <bksge/fnd/cstdint/uint32_t.hpp>

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

	void WaitIdle(void);

	vulkan::PhysicalDeviceSharedPtr const& physical_device(void) const;

	::VkDeviceMemory AllocateMemory(vk::MemoryAllocateInfo const& info);

	void FreeMemory(::VkDeviceMemory device_memory);

	void* MapMemory(::VkDeviceMemory device_memory, ::VkDeviceSize size);

	void UnmapMemory(::VkDeviceMemory device_memory);

	::VkCommandPool	CreateCommandPool(
		::VkCommandPoolCreateFlags flags,
		bksge::uint32_t queue_family_index);

	void DestroyCommandPool(::VkCommandPool command_pool);

	::VkFence CreateFence(vk::FenceCreateInfo const& info);

	void DestroyFence(::VkFence fence);

	::VkResult ResetFences(bksge::uint32_t fence_count, ::VkFence const* fences);

	::VkResult WaitForFences(
		bksge::uint32_t  fence_count,
		::VkFence const* fences,
		::VkBool32       wait_all,
		bksge::uint64_t  timeout);

	::VkBuffer CreateBuffer(::VkDeviceSize size, ::VkBufferUsageFlags usage);

	void DestroyBuffer(::VkBuffer buffer);

	::VkMemoryRequirements GetBufferMemoryRequirements(::VkBuffer buffer) const;

	void BindBufferMemory(
		::VkBuffer       buffer,
		::VkDeviceMemory memory,
		::VkDeviceSize   memoryOffset);

	operator ::VkDevice() const;

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
