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
#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
GlslParameterSetterBase::GlslParameterSetterBase(void)
{
}

BKSGE_INLINE
GlslParameterSetterBase::~GlslParameterSetterBase()
{
}

BKSGE_INLINE void
GlslParameterSetterBase::LoadUniform(
	ResourcePool* resource_pool,
	bksge::shared_ptr<ShaderParameterBase> const& param,
	::GLint location) const
{
	if (param == nullptr || param->data() == nullptr)
	{
		return;
	}
	VLoadUniform(resource_pool, param, location);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_SETTER_INL_HPP
