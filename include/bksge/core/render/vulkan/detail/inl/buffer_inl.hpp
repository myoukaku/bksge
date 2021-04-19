/**
 *	@file	buffer_inl.hpp
 *
 *	@brief	Buffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Buffer::Buffer(
	vulkan::DeviceSharedPtr const& device,
	::VkDeviceSize                 size,
	::VkBufferUsageFlags           usage,
	::VkFlags                      requirements_mask)
	: m_buffer(VK_NULL_HANDLE)
	, m_device(device)
{
	m_buffer = device->CreateBuffer(size, usage);

	auto const mem_reqs = device->GetBufferMemoryRequirements(m_buffer);

	m_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
		device, mem_reqs, requirements_mask);

	m_device->BindBufferMemory(m_buffer, *m_device_memory, 0);
}

BKSGE_INLINE
Buffer::~Buffer()
{
	m_device->DestroyBuffer(m_buffer);
}

BKSGE_INLINE void*
Buffer::MapMemory(::VkDeviceSize size)
{
	return m_device_memory->MapMemory(size);
}

BKSGE_INLINE void
Buffer::UnmapMemory(void)
{
	m_device_memory->UnmapMemory();
}

BKSGE_INLINE ::VkBuffer const*
Buffer::GetAddressOf(void) const
{
	return &m_buffer;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BUFFER_INL_HPP
