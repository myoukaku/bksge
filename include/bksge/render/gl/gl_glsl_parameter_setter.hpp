/**
 *	@file	gl_glsl_parameter_setter.hpp
 *
 *	@brief	GlGLSLParameterSetter の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_GLSL_PARAMETER_SETTER_HPP
#define BKSGE_RENDER_GL_GL_GLSL_PARAMETER_SETTER_HPP

#include <bksge/render/gl/fwd/gl_glsl_parameter_setter_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/detail/shader_parameter_base.hpp>
#include <memory>

namespace bksge
{

namespace render
{

/**
 *	@brief	GlGLSLParameterSetterBase
 */
class GlGLSLParameterSetterBase
{
public:
	explicit GlGLSLParameterSetterBase(GLint location);

	virtual ~GlGLSLParameterSetterBase();

	void SetParameter(std::shared_ptr<ShaderParameterBase> const& src) const;

private:
	virtual void VSetParameter(
		GLint location,
		std::shared_ptr<ShaderParameterBase> const& src) const = 0;

private:
	GLint	m_location;
};

/**
 *	@brief	GlGLSLParameterSetter
 */
template <typename T>
class GlGLSLParameterSetter : public GlGLSLParameterSetterBase
{
public:
	using GlGLSLParameterSetterBase::GlGLSLParameterSetterBase;

private:
	void VSetParameter(
		GLint location,
		std::shared_ptr<ShaderParameterBase> const& src) const override
	{
		if (src)
		{
			auto const* v = static_cast<T const*>(src->data());
			SetParameterImpl(location, *v);
		}
	}

	static void SetParameterImpl(GLint location, float const& v)
	{
		::glUniform1f(location, v);
	}

	static void SetParameterImpl(GLint location, float const (&v)[2])
	{
		::glUniform2fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(GLint location, float const (&v)[3])
	{
		::glUniform3fv(location, 1, &v[0]);
	}

	static void SetParameterImpl(GLint location, float const (&v)[4])
	{
		::glUniform4fv(location, 1, &v[0]);
	}
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_glsl_parameter_setter_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_GLSL_PARAMETER_SETTER_HPP
