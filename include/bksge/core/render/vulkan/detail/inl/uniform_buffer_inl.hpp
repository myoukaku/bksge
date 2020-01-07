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

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
UniformBuffer::UniformBuffer(
	vulkan::DeviceSharedPtr const& device,
	vulkan::ShaderReflectionUniformBuffer const& reflection)
	: m_device(device)
{
	auto const size = reflection.bytes;

	m_buffer = bksge::make_unique<vulkan::Buffer>(
		device,
		size,
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

	auto const mem_reqs = m_buffer->requirements();

	m_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
		device,
		mem_reqs,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	vk::BindBufferMemory(*m_device, *m_buffer, *m_device_memory, 0);

	m_descriptor_buffer_info.buffer = *m_buffer;
	m_descriptor_buffer_info.offset = 0;
	m_descriptor_buffer_info.range  = size;

	m_name  = reflection.name;
	m_bytes = reflection.bytes;

	for (auto const& member : reflection.members)
	{
		Variable v;
		v.name   = member.name;
		v.offset = member.offset;
		v.bytes  = member.bytes;
		m_variables.push_back(v);
	}
}

BKSGE_INLINE
UniformBuffer::~UniformBuffer()
{
}

BKSGE_INLINE void
UniformBuffer::LoadParameters(bksge::ShaderParameterMap const& shader_parameter_map)
{
	auto const mem_reqs = m_buffer->requirements();

	std::uint8_t* dst;
	vk::MapMemory(*m_device, *m_device_memory, 0, mem_reqs.size, 0, reinterpret_cast<void**>(&dst));

	// Uniform Block をまとめて更新
	{
		auto param = shader_parameter_map[m_name];
		if (param)
		{
			std::memcpy(dst, param->data(), m_bytes);
		}
	}

	// Uniform Block のメンバーを個別に更新
	for (auto&& variable : m_variables)
	{
		auto param = shader_parameter_map[variable.name];
		if (param)
		{
			std::memcpy(
				dst + variable.offset,
				param->data(),
				variable.bytes);
		}
	}

	vk::UnmapMemory(*m_device, *m_device_memory);
}

BKSGE_INLINE ::VkDescriptorBufferInfo const*
UniformBuffer::GetDescriptorBufferInfo(void) const
{
	return &m_descriptor_buffer_info;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_UNIFORM_BUFFER_INL_HPP
