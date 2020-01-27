/**
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
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

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
		vulkan::ShaderReflectionUniformBuffer const& reflection);

	~UniformBufferSetter();

	std::size_t LoadParameters(
		bksge::ShaderParameterMap const& shader_parameter_map,
		vulkan::UniformBuffer* uniform_buffer);

private:
	struct Variable
	{
		std::string		name;
		std::size_t		bytes;
		std::uint32_t	offset;
	};

	std::string						m_name;
	std::size_t						m_bytes = 0;
	std::vector<Variable>			m_variables;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/uniform_buffer_setter_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_SETTER_HPP
