/**
 *	@file	uniform_buffer_inl.hpp
 *
 *	@brief	UniformBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_UNIFORM_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_UNIFORM_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/buffer_object.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/cmath/round_up.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
UniformBuffer::UniformBuffer(
	vulkan::DeviceSharedPtr const& device,
	::VkDeviceSize                 size)
{
	m_buffer = bksge::make_unique<vulkan::BufferObject>(
		device,
		size,
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	m_mapped_buffer =
		static_cast<std::uint8_t*>(m_buffer->MapMemory(VK_WHOLE_SIZE));

	auto physical_device = device->GetPhysicalDevice();
	::VkPhysicalDeviceProperties properties;
	vk::GetPhysicalDeviceProperties(*physical_device, &properties);
	m_offset_alignment = static_cast<bksge::size_t>(
		properties.limits.minUniformBufferOffsetAlignment);
}

BKSGE_INLINE
UniformBuffer::~UniformBuffer()
{
	m_buffer->UnmapMemory();
}

BKSGE_INLINE ::VkBuffer
UniformBuffer::GetBuffer(void) const
{
	return m_buffer->GetBuffer();
}

BKSGE_INLINE std::uint8_t*
UniformBuffer::GetMappedBuffer(void) const
{
	return m_mapped_buffer;
}

BKSGE_INLINE bksge::size_t
UniformBuffer::Allocate(bksge::size_t size)
{
	auto const offset = m_offset;

	m_offset += bksge::round_up(size, m_offset_alignment);

	return offset;
}

BKSGE_INLINE void
UniformBuffer::BeginFrame(void)
{
	m_offset = 0;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_UNIFORM_BUFFER_INL_HPP
