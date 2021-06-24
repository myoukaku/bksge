/**
 *	@file	shader_parameter_map_inl.hpp
 *
 *	@brief	ShaderParameterMap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_SHADER_PARAMETER_MAP_INL_HPP
#define BKSGE_CORE_RENDER_INL_SHADER_PARAMETER_MAP_INL_HPP

#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/fnd/utility/move.hpp>

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
	: m_parameters(bksge::move(rhs.m_parameters))
{}

BKSGE_INLINE
ShaderParameterMap& ShaderParameterMap::operator=(ShaderParameterMap&& rhs)
{
	m_parameters = bksge::move(rhs.m_parameters);
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

#endif // BKSGE_CORE_RENDER_INL_SHADER_PARAMETER_MAP_INL_HPP
