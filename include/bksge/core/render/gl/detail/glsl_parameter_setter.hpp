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
#include <bksge/core/render/gl/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/detail/shader_parameter_base.hpp>
#include <bksge/fnd/cstddef.hpp>

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
	virtual ~GlslParameterSetterBase();

	void LoadUniform(
		ResourcePool* resource_pool,
		ShaderParameterBase const* param,
		::GLint location) const;

	virtual ::GLsizeiptr size(void) const = 0;

private:
	virtual void VLoadUniform(
		ResourcePool* resource_pool,
		ShaderParameterBase const* param,
		::GLint location) const = 0;
};

/**
 *	@brief	GlslParameterSetter
 */
template <::GLenum Type>
class GlslParameterSetter;

template <typename T, bksge::size_t N, bksge::size_t M = 1>
class GlslVectorParameterSetter : public GlslParameterSetterBase
{
public:
	::GLsizeiptr size(void) const override
	{
		return sizeof(T) * N * M;
	}

private:
	void VLoadUniform(
		ResourcePool*,
		ShaderParameterBase const* param,
		::GLint location) const override
	{
		auto const* v = static_cast<T const*>(param->data());
		VLoadUniformImpl(location, v);
	}

	virtual void VLoadUniformImpl(::GLint location, T const* v) const = 0;
};

template <>
class GlslParameterSetter<GL_FLOAT>
	: public GlslVectorParameterSetter<float, 1>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniform1fv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_VEC2>
	: public GlslVectorParameterSetter<float, 2>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniform2fv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_VEC3>
	: public GlslVectorParameterSetter<float, 3>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniform3fv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_VEC4>
	: public GlslVectorParameterSetter<float, 4>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniform4fv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE>
	: public GlslVectorParameterSetter<double, 1>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniform1dv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_VEC2>
	: public GlslVectorParameterSetter<double, 2>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniform2dv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_VEC3>
	: public GlslVectorParameterSetter<double, 3>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniform3dv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_VEC4>
	: public GlslVectorParameterSetter<double, 4>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniform4dv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_INT>
	: public GlslVectorParameterSetter<int, 1>
{
	void VLoadUniformImpl(::GLint location, int const* v) const override
	{
		::glUniform1iv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_INT_VEC2>
	: public GlslVectorParameterSetter<int, 2>
{
	void VLoadUniformImpl(::GLint location, int const* v) const override
	{
		::glUniform2iv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_INT_VEC3>
	: public GlslVectorParameterSetter<int, 3>
{
	void VLoadUniformImpl(::GLint location, int const* v) const override
	{
		::glUniform3iv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_INT_VEC4>
	: public GlslVectorParameterSetter<int, 4>
{
	void VLoadUniformImpl(::GLint location, int const* v) const override
	{
		::glUniform4iv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_UNSIGNED_INT>
	: public GlslVectorParameterSetter<unsigned int, 1>
{
	void VLoadUniformImpl(::GLint location, unsigned int const* v) const override
	{
		::glUniform1uiv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_UNSIGNED_INT_VEC2>
	: public GlslVectorParameterSetter<unsigned int, 2>
{
	void VLoadUniformImpl(::GLint location, unsigned int const* v) const override
	{
		::glUniform2uiv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_UNSIGNED_INT_VEC3>
	: public GlslVectorParameterSetter<unsigned int, 3>
{
	void VLoadUniformImpl(::GLint location, unsigned int const* v) const override
	{
		::glUniform3uiv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_UNSIGNED_INT_VEC4>
	: public GlslVectorParameterSetter<unsigned int, 4>
{
	void VLoadUniformImpl(::GLint location, unsigned int const* v) const override
	{
		::glUniform4uiv(location, 1, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT2>
	: public GlslVectorParameterSetter<float, 2, 2>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix2fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT2x3>
	: public GlslVectorParameterSetter<float, 2, 3>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix2x3fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT2x4>
	: public GlslVectorParameterSetter<float, 2, 4>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix2x4fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT3x2>
	: public GlslVectorParameterSetter<float, 3, 2>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix3x2fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT3>
	: public GlslVectorParameterSetter<float, 3, 3>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix3fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT3x4>
	: public GlslVectorParameterSetter<float, 3, 4>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix3x4fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT4x2>
	: public GlslVectorParameterSetter<float, 4, 2>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix4x2fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT4x3>
	: public GlslVectorParameterSetter<float, 4, 3>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix4x3fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_FLOAT_MAT4>
	: public GlslVectorParameterSetter<float, 4, 4>
{
	void VLoadUniformImpl(::GLint location, float const* v) const override
	{
		::glUniformMatrix4fv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT2>
	: public GlslVectorParameterSetter<double, 2, 2>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix2dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT2x3>
	: public GlslVectorParameterSetter<double, 2, 3>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix2x3dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT2x4>
	: public GlslVectorParameterSetter<double, 2, 4>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix2x4dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT3x2>
	: public GlslVectorParameterSetter<double, 3, 2>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix3x2dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT3>
	: public GlslVectorParameterSetter<double, 3, 3>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix3dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT3x4>
	: public GlslVectorParameterSetter<double, 3, 4>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix3x4dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT4x2>
	: public GlslVectorParameterSetter<double, 4, 2>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix4x2dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT4x3>
	: public GlslVectorParameterSetter<double, 4, 3>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix4x3dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_DOUBLE_MAT4>
	: public GlslVectorParameterSetter<double, 4, 4>
{
	void VLoadUniformImpl(::GLint location, double const* v) const override
	{
		::glUniformMatrix4dv(location, 1, GL_FALSE, v);
	}
};

template <>
class GlslParameterSetter<GL_SAMPLER_2D> : public GlslParameterSetterBase
{
public:
	::GLsizeiptr size(void) const override
	{
		return 0;
	}

private:
	void VLoadUniform(
		ResourcePool* resource_pool,
		ShaderParameterBase const* param,
		::GLint location) const override;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/glsl_parameter_setter_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GLSL_PARAMETER_SETTER_HPP
