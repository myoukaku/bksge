/**
 *	@file	glsl_parameter_setter.hpp
 *
 *	@brief	GlslParameterSetter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PARAMETER_SETTER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PARAMETER_SETTER_HPP

#include <bksge/core/render/gl/detail/fwd/glsl_parameter_setter_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/gl/detail/sampled_texture.hpp>
#include <bksge/core/render/detail/shader_parameter_base.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/render/sampled_texture.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	GlslParameterSetterBase
 */
class GlslParameterSetterBase
{
public:
	explicit GlslParameterSetterBase(void);

	virtual ~GlslParameterSetterBase();

	void LoadUniform(
		ResourcePool* resource_pool,
		bksge::shared_ptr<ShaderParameterBase> const& src,
		::GLint location) const;

	virtual GLsizeiptr size(void) const = 0;

private:
	virtual void VLoadUniform(
		ResourcePool* resource_pool,
		bksge::shared_ptr<ShaderParameterBase> const& src,
		::GLint location) const = 0;
};

/**
 *	@brief	GlslParameterSetter
 */
template <typename T>
class GlslParameterSetter : public GlslParameterSetterBase
{
public:
	using GlslParameterSetterBase::GlslParameterSetterBase;

	GLsizeiptr size(void) const override
	{
		return sizeof(T);
	}

private:
	void VLoadUniform(
		ResourcePool*,
		bksge::shared_ptr<ShaderParameterBase> const& src,
		::GLint location) const override
	{
		auto const* v = static_cast<T const*>(src->data());
		LoadUniformImpl(location, *v);
	}

	static void LoadUniformImpl(::GLint location, float const& v)
	{
		::glUniform1f(location, v);
	}

	static void LoadUniformImpl(::GLint location, float const (&v)[2])
	{
		::glUniform2fv(location, 1, &v[0]);
	}

	static void LoadUniformImpl(::GLint location, float const (&v)[3])
	{
		::glUniform3fv(location, 1, &v[0]);
	}

	static void LoadUniformImpl(::GLint location, float const (&v)[4])
	{
		::glUniform4fv(location, 1, &v[0]);
	}

	static void LoadUniformImpl(::GLint location, double const& v)
	{
		::glUniform1d(location, v);
	}

	static void LoadUniformImpl(::GLint location, double const (&v)[2])
	{
		::glUniform2dv(location, 1, &v[0]);
	}

	static void LoadUniformImpl(::GLint location, double const (&v)[3])
	{
		::glUniform3dv(location, 1, &v[0]);
	}

	static void LoadUniformImpl(::GLint location, double const (&v)[4])
	{
		::glUniform4dv(location, 1, &v[0]);
	}

	static void LoadUniformImpl(::GLint location, float const (&v)[2][2])
	{
		::glUniformMatrix2fv(location, 1, GL_FALSE, &v[0][0]);
	}

	static void LoadUniformImpl(::GLint location, float const (&v)[3][3])
	{
		::glUniformMatrix3fv(location, 1, GL_FALSE, &v[0][0]);
	}

	static void LoadUniformImpl(::GLint location, float const (&v)[4][4])
	{
		::glUniformMatrix4fv(location, 1, GL_FALSE, &v[0][0]);
	}
};

template <>
class GlslParameterSetter<bksge::SampledTexture> : public GlslParameterSetterBase
{
private:
	using T = bksge::SampledTexture;

public:
	using GlslParameterSetterBase::GlslParameterSetterBase;

	GLsizeiptr size(void) const override
	{
		return sizeof(T);
	}

private:
	void VLoadUniform(
		ResourcePool* resource_pool,
		bksge::shared_ptr<ShaderParameterBase> const& src,
		::GLint location) const override
	{
		if (src->class_id() == ShaderParameter<bksge::SampledTexture>::StaticClassId())
		{
			auto sampled_texture = *static_cast<bksge::SampledTexture const*>(src->data());
			gl::SampledTexture gl_sampled_texture(resource_pool, sampled_texture);
			gl_sampled_texture.Bind(location);
			return;
		}

		if (src->class_id() == ShaderParameter<gl::SampledTexture>::StaticClassId())
		{
			auto gl_sampled_texture = *static_cast<gl::SampledTexture const*>(src->data());
			gl_sampled_texture.Bind(location);
			return;
		}
	}
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/glsl_parameter_setter_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PARAMETER_SETTER_HPP
