/**
 *	@file	gl_glsl_parameter_setter_inl.hpp
 *
 *	@brief	GlGLSLParameterSetter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_GLSL_PARAMETER_SETTER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_GLSL_PARAMETER_SETTER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_glsl_parameter_setter.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlGLSLParameterSetterBase::GlGLSLParameterSetterBase(GLint location)
	: m_location(location)
{
}

BKSGE_INLINE
GlGLSLParameterSetterBase::~GlGLSLParameterSetterBase()
{
}

BKSGE_INLINE void
GlGLSLParameterSetterBase::SetParameter(
	std::shared_ptr<ShaderParameterBase> const& src) const
{
	VSetParameter(m_location, src);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_GLSL_PARAMETER_SETTER_INL_HPP
