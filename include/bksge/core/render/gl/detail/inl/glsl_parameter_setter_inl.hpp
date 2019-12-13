/**
 *	@file	glsl_parameter_setter_inl.hpp
 *
 *	@brief	GlslParameterSetter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_SETTER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_SETTER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/glsl_parameter_setter.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
GlslParameterSetterBase::GlslParameterSetterBase(::GLint location)
	: m_location(location)
{
}

BKSGE_INLINE
GlslParameterSetterBase::~GlslParameterSetterBase()
{
}

BKSGE_INLINE void
GlslParameterSetterBase::SetParameter(
	ResourceCache* resource_cache,
	std::shared_ptr<ShaderParameterBase> const& src) const
{
	VSetParameter(resource_cache, m_location, src);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_SETTER_INL_HPP
