﻿/**
 *	@file	glsl_parameter_setter.hpp
 *
 *	@brief	GlslParameterSetter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_GLSL_PARAMETER_SETTER_HPP
#define BKSGE_RENDER_GL_DETAIL_GLSL_PARAMETER_SETTER_HPP

#include <bksge/render/gl/detail/fwd/glsl_parameter_setter_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/detail/shader_parameter_base.hpp>
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
	explicit GlslParameterSetterBase(::GLint location);

	virtual ~GlslParameterSetterBase();

	void SetParameter(std::shared_ptr<ShaderParameterBase> const& src) const;

private:
	virtual void VSetParameter(
		::GLint location,
		std::shared_ptr<ShaderParameterBase> const& src) const = 0;

private:
	::GLint	m_location;
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
		::GLint location,
		std::shared_ptr<ShaderParameterBase> const& src) const override
	{
		if (src)
		{
			auto const* v = static_cast<T const*>(src->data());
			SetParameterImpl(location, *v);
		}
	}

	static void SetParameterImpl(::GLint location, float const& v)
	{
		::glUniform1f(location, v);
	}

	static void SetParameterImpl(::GLint location, float const (&v)[2])
	{
		::glUniform2fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(::GLint location, float const (&v)[3])
	{
		::glUniform3fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(::GLint location, float const (&v)[4])
	{
		::glUniform4fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(::GLint location, double const& v)
	{
		::glUniform1d(location, v);
	}

	static void SetParameterImpl(::GLint location, double const (&v)[2])
	{
		::glUniform2dv(location, 1, &v[0]);
	}

	static void SetParameterImpl(::GLint location, double const (&v)[3])
	{
		::glUniform3dv(location, 1, &v[0]);
	}

	static void SetParameterImpl(::GLint location, double const (&v)[4])
	{
		::glUniform4dv(location, 1, &v[0]);
	}

	static void SetParameterImpl(::GLint location, float const (&v)[2][2])
	{
		::glUniformMatrix2fv(location, 1, GL_FALSE, &v[0][0]);
	}

	static void SetParameterImpl(::GLint location, float const (&v)[3][3])
	{
		::glUniformMatrix3fv(location, 1, GL_FALSE, &v[0][0]);
	}

	static void SetParameterImpl(::GLint location, float const (&v)[4][4])
	{
		::glUniformMatrix4fv(location, 1, GL_FALSE, &v[0][0]);
	}
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/glsl_parameter_setter_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_GLSL_PARAMETER_SETTER_HPP