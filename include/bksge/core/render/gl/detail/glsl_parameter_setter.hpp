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
#include <bksge/core/render/sampled_texture.hpp>
#include <memory>

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

	void SetParameter(
		ResourcePool* resource_pool,
		std::shared_ptr<ShaderParameterBase> const& src,
		::GLint location) const;

	void LoadUniformBuffer(
		std::shared_ptr<ShaderParameterBase> const& src,
		::GLint offset) const;

private:
	virtual void VSetParameter(
		ResourcePool* resource_pool,
		std::shared_ptr<ShaderParameterBase> const& src,
		::GLint location) const = 0;

	virtual void VLoadUniformBuffer(
		std::shared_ptr<ShaderParameterBase> const& src,
		::GLint offset) const = 0;
};

/**
 *	@brief	GlslParameterSetter
 */
template <typename T>
class GlslParameterSetter : public GlslParameterSetterBase
{
public:
	using GlslParameterSetterBase::GlslParameterSetterBase;

private:
	void VSetParameter(
		ResourcePool* resource_pool,
		std::shared_ptr<ShaderParameterBase> const& src,
		::GLint location) const override
	{
		if (src)
		{
			auto const* v = static_cast<T const*>(src->data());
			SetParameterImpl(resource_pool, location, *v);
		}
	}

	void VLoadUniformBuffer(
		std::shared_ptr<ShaderParameterBase> const& src,
		::GLint offset) const override
	{
		if (src)
		{
			::glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(T), src->data());
		}
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, float const& v)
	{
		::glUniform1f(location, v);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, float const (&v)[2])
	{
		::glUniform2fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, float const (&v)[3])
	{
		::glUniform3fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, float const (&v)[4])
	{
		::glUniform4fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, double const& v)
	{
		::glUniform1d(location, v);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, double const (&v)[2])
	{
		::glUniform2dv(location, 1, &v[0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, double const (&v)[3])
	{
		::glUniform3dv(location, 1, &v[0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, double const (&v)[4])
	{
		::glUniform4dv(location, 1, &v[0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, float const (&v)[2][2])
	{
		::glUniformMatrix2fv(location, 1, GL_FALSE, &v[0][0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, float const (&v)[3][3])
	{
		::glUniformMatrix3fv(location, 1, GL_FALSE, &v[0][0]);
	}

	static void SetParameterImpl(ResourcePool*, ::GLint location, float const (&v)[4][4])
	{
		::glUniformMatrix4fv(location, 1, GL_FALSE, &v[0][0]);
	}

	static void SetParameterImpl(
		ResourcePool* resource_pool,
		::GLint location,
		bksge::SampledTexture const& sampled_texture)
	{
		gl::SampledTexture gl_sampled_texture(resource_pool, sampled_texture);
		gl_sampled_texture.Bind(location);
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
