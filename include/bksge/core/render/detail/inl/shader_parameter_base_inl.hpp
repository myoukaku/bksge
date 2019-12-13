﻿/**
 *	@file	shader_parameter_base_inl.hpp
 *
 *	@brief	ShaderParameterBase の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_SHADER_PARAMETER_BASE_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_SHADER_PARAMETER_BASE_INL_HPP

#include <bksge/core/render/detail/shader_parameter_base.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
ShaderParameterBase::~ShaderParameterBase()
{}

BKSGE_INLINE bool
operator==(ShaderParameterBase const& lhs, ShaderParameterBase const& rhs)
{
	return lhs.Equals(rhs);
}

BKSGE_INLINE bool
operator!=(ShaderParameterBase const& lhs, ShaderParameterBase const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_SHADER_PARAMETER_BASE_INL_HPP
