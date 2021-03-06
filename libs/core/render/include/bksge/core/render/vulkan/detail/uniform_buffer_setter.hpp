﻿/**
 *	@file	uniform_buffer_setter.hpp
 *
 *	@brief	UniformBufferSetter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_SETTER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_SETTER_HPP

#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_setter_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class UniformBufferSetter
{
public:
	explicit UniformBufferSetter(
		vulkan::ShaderReflectionUniform const& reflection);

	~UniformBufferSetter();

	void LoadParameters(
		bksge::ShaderParameterMap const& shader_parameter_map,
		vulkan::UniformBuffer* uniform_buffer);

	vk::WriteDescriptorSet GetWriteDescriptorSet(void) const;

private:
	// noncopyable
	UniformBufferSetter(UniformBufferSetter const&) = delete;
	UniformBufferSetter& operator=(UniformBufferSetter const&) = delete;

private:
	struct Variable
	{
		bksge::string	name;
		bksge::size_t	bytes = 0;
		bksge::uint32_t	offset = 0;
	};

	bksge::uint32_t					m_set = 0;
	bksge::uint32_t					m_binding = 0;
	bksge::string					m_name;
	::VkDescriptorType				m_descriptor_type;
	bksge::size_t					m_bytes = 0;
	bksge::vector<Variable>			m_variables;
	::VkDescriptorBufferInfo		m_buffer_info;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/uniform_buffer_setter_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_SETTER_HPP
