/**
 *	@file	shader_parameter_map_inl.hpp
 *
 *	@brief	ShaderParameterMap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_SHADER_PARAMETER_MAP_INL_HPP
#define BKSGE_RENDER_INL_SHADER_PARAMETER_MAP_INL_HPP

#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/render/detail/shader_parameter.hpp>
#include <memory>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
ShaderParameterMap::ShaderParameterMap(void)
	: m_parameters()
{}

BKSGE_INLINE
ShaderParameterMap::ShaderParameterMap(ShaderParameterMap&& rhs)
	: m_parameters(std::move(rhs.m_parameters))
{}

BKSGE_INLINE
ShaderParameterMap& ShaderParameterMap::operator=(ShaderParameterMap&& rhs)
{
	m_parameters = std::move(rhs.m_parameters);
	return *this;
}

BKSGE_INLINE
auto ShaderParameterMap::operator[](key_type const& key) const
-> mapped_type const&
{
	auto&& it = m_parameters.find(key);

	if (it != m_parameters.end())
	{
		return it->second;
	}

	static mapped_type const dummy;
	return dummy;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SHADER_PARAMETER_MAP_INL_HPP
