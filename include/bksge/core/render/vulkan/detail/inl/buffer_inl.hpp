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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

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
	::VkBufferUsageFlags           usage)
	: m_device(device)
	, m_buffer(VK_NULL_HANDLE)
{
	vk::BufferCreateInfo info;
    info.size        = size;
    info.usage       = usage;
    info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.SetQueueFamilyIndices(nullptr);

	vk::CreateBuffer(*m_device, &info, nullptr, &m_buffer);
}

BKSGE_INLINE
Buffer::~Buffer()
{
	vk::DestroyBuffer(*m_device, m_buffer, nullptr);
}

BKSGE_INLINE
Buffer::operator ::VkBuffer() const
{
	return m_buffer;
}

BKSGE_INLINE ::VkBuffer const*
Buffer::GetAddressOf(void) const
{
	return &m_buffer;
}

BKSGE_INLINE ::VkMemoryRequirements
Buffer::requirements(void) const
{
	::VkMemoryRequirements result;
	vk::GetBufferMemoryRequirements(*m_device, m_buffer, &result);
	return result;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BUFFER_INL_HPP
