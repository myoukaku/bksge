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
#include <bksge/core/render/gl/detail/sampler.hpp>
#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/detail/shader_parameter_base.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/utility/pair.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
GlslParameterSetterBase::~GlslParameterSetterBase()
{
}

BKSGE_INLINE void
GlslParameterSetterBase::LoadUniform(
	ResourcePool* resource_pool,
	ShaderParameterBase const* param,
	::GLint location) const
{
	if (param == nullptr || param->data() == nullptr)
	{
		return;
	}
	VLoadUniform(resource_pool, param, location);
}

BKSGE_INLINE void
GlslParameterSetter<GL_SAMPLER_2D>::VLoadUniform(
	ResourcePool* resource_pool,
	ShaderParameterBase const* param,
	::GLint location) const
{
	using Sampler2d = bksge::pair<bksge::Sampler, bksge::Texture>;
	if (param->class_id() == ShaderParameter<Sampler2d>::StaticClassId())
	{
		auto sampler_2d = static_cast<Sampler2d const*>(param->data());
		auto gl_sampler = resource_pool->GetGlSampler(sampler_2d->first);
		auto gl_texture = resource_pool->GetGlTexture(sampler_2d->second);
		gl_sampler->Bind(location);
		gl_texture->Bind(location);
		return;
	}

	using GlSampler2d = bksge::pair<gl::SamplerShared, gl::TextureShared>;
	if (param->class_id() == ShaderParameter<GlSampler2d>::StaticClassId())
	{
		auto sampler_2d = static_cast<GlSampler2d const*>(param->data());
		sampler_2d->first->Bind(location);
		sampler_2d->second->Bind(location);
		return;
	}
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_SETTER_INL_HPP
