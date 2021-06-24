/**
 *	@file	glsl_parameter_inl.hpp
 *
 *	@brief	GlslParameter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/glsl_parameter.hpp>
#include <bksge/core/render/gl/detail/glsl_parameter_setter.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/assert.hpp>

//#include <iostream>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
GlslParameter::GlslParameter(::GLuint program, ::GLuint index)
{
	::GLint max_length;
	::glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);

	bksge::vector<::GLchar> buf(max_length + 1);
	::GLint size;
	::glGetActiveUniform(
		program, index, max_length, nullptr, &size, &m_type, buf.data());
	m_name = buf.data();
	m_location = ::glGetUniformLocation(program, m_name.c_str());

	::glGetActiveUniformsiv(program, 1, &index, GL_UNIFORM_OFFSET, &m_offset);

#define BKSGE_GL_CREATE_PARAM_SETTER(Type)	\
	case Type:      m_setter.reset(new GlslParameterSetter<Type>()); break

	switch (m_type)
	{
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_VEC2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_VEC3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_VEC4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_VEC2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_VEC3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_VEC4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_INT);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_INT_VEC2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_INT_VEC3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_INT_VEC4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_UNSIGNED_INT);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_UNSIGNED_INT_VEC2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_UNSIGNED_INT_VEC3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_UNSIGNED_INT_VEC4);
	//BKSGE_GL_CREATE_PARAM_SETTER(GL_BOOL);
	//BKSGE_GL_CREATE_PARAM_SETTER(GL_BOOL_VEC2);
	//BKSGE_GL_CREATE_PARAM_SETTER(GL_BOOL_VEC3);
	//BKSGE_GL_CREATE_PARAM_SETTER(GL_BOOL_VEC4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT2x3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT2x4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT3x2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT3x4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT4x2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT4x3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_FLOAT_MAT4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT2x3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT2x4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT3x2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT3x4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT4x2);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT4x3);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_DOUBLE_MAT4);
	BKSGE_GL_CREATE_PARAM_SETTER(GL_SAMPLER_2D);
	default: BKSGE_ASSERT(false); break;
	}

#undef BKSGE_GL_CREATE_PARAM_SETTER
}

BKSGE_INLINE
GlslParameter::~GlslParameter()
{
}

BKSGE_INLINE void
GlslParameter::LoadParameter(
	ResourcePool* resource_pool,
	ShaderParameterMap const& shader_parameter_map)
{
	if (m_setter)
	{
		m_setter->LoadUniform(
			resource_pool,
			shader_parameter_map[m_name].get(),
			m_location);
	}
}

BKSGE_INLINE void
GlslParameter::LoadUniformBuffer(
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	if (m_setter == nullptr)
	{
		return;
	}

	auto param = shader_parameter_map[m_name];
	if (param == nullptr || param->data() == nullptr)
	{
		return;
	}

	::glBufferSubData(GL_UNIFORM_BUFFER, m_offset, m_setter->size(), param->data());
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_INL_HPP
