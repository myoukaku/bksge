﻿/**
 *	@file	device_memory_inl.hpp
 *
 *	@brief	DeviceMemory クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_MEMORY_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_MEMORY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline bksge::uint32_t
GetMemoryTypeIndex(
	::VkPhysicalDeviceMemoryProperties const& props,
	bksge::uint32_t type_bits,
	::VkFlags mask)
{
	// Search memtypes to find first index with those properties
	for (bksge::uint32_t i = 0; i < props.memoryTypeCount; i++)
	{
		if ((type_bits & 1) == 1)
		{
			// Type is available, does it match user properties?
			if ((props.memoryTypes[i].propertyFlags & mask) == mask)
			{
				return i;
			}
		}
		type_bits >>= 1;
	}

	// No memory types matched, return failure
	return bksge::uint32_t(-1);
}

}	// namespace detail

BKSGE_INLINE
DeviceMemory::DeviceMemory(
	DeviceSharedPtr const& device,
	::VkMemoryRequirements const& requirements,
	::VkFlags requirements_mask)
	: m_device_memory(VK_NULL_HANDLE)
	, m_device(device)
{
	auto physical_device = device->physical_device();

	vk::MemoryAllocateInfo info;
	info.allocationSize = requirements.size;
	info.memoryTypeIndex =
		detail::GetMemoryTypeIndex(
			physical_device->GetMemoryProperties(),
			requirements.memoryTypeBits,
			requirements_mask);

	m_device_memory = m_device->AllocateMemory(info);
}

BKSGE_INLINE
DeviceMemory::~DeviceMemory()
{
	m_device->FreeMemory(m_device_memory);
}

BKSGE_INLINE void*
DeviceMemory::MapMemory(::VkDeviceSize size)
{
	return m_device->MapMemory(m_device_memory, size);
}

BKSGE_INLINE void
DeviceMemory::UnmapMemory(void)
{
	m_device->UnmapMemory(m_device_memory);
}

BKSGE_INLINE void
DeviceMemory::BindImage(::VkImage image, ::VkDeviceSize memory_offset)
{
	m_device->BindImageMemory(image, m_device_memory, memory_offset);
}

BKSGE_INLINE void
DeviceMemory::BindBuffer(::VkBuffer buffer, ::VkDeviceSize memory_offset)
{
	m_device->BindBufferMemory(buffer, m_device_memory, memory_offset);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_MEMORY_INL_HPP
