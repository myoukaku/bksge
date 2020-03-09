/**
 *	@file	uniform_buffer_setter_inl.hpp
 *
 *	@brief	UniformBufferSetter クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_UNIFORM_BUFFER_SETTER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_UNIFORM_BUFFER_SETTER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/uniform_buffer_setter.hpp>
#include <bksge/core/render/vulkan/detail/uniform_buffer.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/shader_reflection.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/cstring/memcpy.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
UniformBufferSetter::UniformBufferSetter(
	vulkan::ShaderReflectionUniform const& reflection)
{
	m_set             = reflection.set;
	m_binding         = reflection.binding;
	m_name            = reflection.name;
	m_descriptor_type = reflection.descriptor_type;
	m_bytes           = reflection.bytes;

	for (auto const& member : reflection.members)
	{
		Variable v;
		v.name   = member.name;
		v.offset = member.offset;
		v.bytes  = member.bytes;
		m_variables.push_back(v);
	}

	m_buffer_info.buffer = VK_NULL_HANDLE;
	m_buffer_info.offset = 0;
	m_buffer_info.range  = 0;
}

BKSGE_INLINE
UniformBufferSetter::~UniformBufferSetter()
{
}

BKSGE_INLINE void
UniformBufferSetter::LoadParameters(
	bksge::ShaderParameterMap const& shader_parameter_map,
	vulkan::UniformBuffer* uniform_buffer)
{
	bksge::uint8_t* dst = uniform_buffer->GetMappedBuffer();
	auto const offset = uniform_buffer->Allocate(m_bytes);

	dst += offset;

	// Uniform Block をまとめて更新
	{
		auto param = shader_parameter_map[m_name];
		if (param)
		{
			bksge::memcpy(dst, param->data(), m_bytes);
		}
	}

	// Uniform Block のメンバーを個別に更新
	for (auto&& variable : m_variables)
	{
		auto param = shader_parameter_map[variable.name];
		if (param)
		{
			bksge::memcpy(
				dst + variable.offset,
				param->data(),
				variable.bytes);
		}
	}

	m_buffer_info.buffer = uniform_buffer->GetBuffer();
	m_buffer_info.offset = offset;
	m_buffer_info.range  = m_bytes;
}

BKSGE_INLINE vk::WriteDescriptorSet
UniformBufferSetter::GetWriteDescriptorSet(void) const
{
	vk::WriteDescriptorSet write;
	write.dstSet           = VK_NULL_HANDLE;
	write.dstBinding       = m_binding;
	write.dstArrayElement  = 0;
	write.descriptorCount  = 1;
	write.descriptorType   = m_descriptor_type;
	write.pImageInfo       = nullptr;
	write.pBufferInfo      = &m_buffer_info;
	write.pTexelBufferView = nullptr;

	return write;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_UNIFORM_BUFFER_SETTER_INL_HPP
