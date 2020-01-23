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
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/cmath/round_up.hpp>

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
	: m_device(device)
{
	m_buffer = bksge::make_unique<vulkan::Buffer>(
		device,
		size,
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

	auto const mem_reqs = m_buffer->requirements();

	m_device_memory =
		bksge::make_unique<vulkan::DeviceMemory>(
			device,
			mem_reqs,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	vk::BindBufferMemory(
		*m_device,
		*m_buffer,
		*m_device_memory,
		0);

	vk::MapMemory(
		*m_device,
		*m_device_memory,
		0,
		VK_WHOLE_SIZE,
		0,
		reinterpret_cast<void**>(&m_mapped_buffer));

	auto physical_device = device->GetPhysicalDevice();
	VkPhysicalDeviceProperties properties;
	vk::GetPhysicalDeviceProperties(*physical_device, &properties);
	m_offset_alignment = properties.limits.minUniformBufferOffsetAlignment;
}

BKSGE_INLINE
UniformBuffer::~UniformBuffer()
{
	vk::UnmapMemory(*m_device, *m_device_memory);
}

BKSGE_INLINE vulkan::BufferUniquePtr const&
UniformBuffer::GetBuffer() const
{
	return m_buffer;
}

BKSGE_INLINE std::uint8_t*
UniformBuffer::GetMappedBuffer(void) const
{
	return m_mapped_buffer;
}

BKSGE_INLINE std::size_t
UniformBuffer::Allocate(std::size_t size)
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
