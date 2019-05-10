/**
 *	@file	gl_glsl_parameter_inl.hpp
 *
 *	@brief	GlGLSLParameter クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_GLSL_PARAMETER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_GLSL_PARAMETER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_glsl_parameter.hpp>
#include <bksge/render/gl/gl_glsl_parameter_setter.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/assert.hpp>
#include <string>
#include <vector>

//#include <iostream>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlGLSLParameter::GlGLSLParameter(GLuint program, GLint index)
{
	GLint max_length;
	::glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);

	std::vector<GLchar> buf(max_length + 1);
	::glGetActiveUniform(
		program, index, max_length, nullptr, &m_size, &m_type, buf.data());
	m_name = buf.data();
	m_location = ::glGetUniformLocation(program, m_name.c_str());

	//std::cout
	//	<< m_location << ", "
	//	<< m_size << ", "
	//	<< m_type << ", "
	//	<< m_name << std::endl;

	switch (m_type)
	{
	case GL_FLOAT:      m_setter.reset(new GlGLSLParameterSetter<float>(m_location)); break;
	case GL_FLOAT_VEC2: m_setter.reset(new GlGLSLParameterSetter<float[2]>(m_location)); break;
	case GL_FLOAT_VEC3: m_setter.reset(new GlGLSLParameterSetter<float[3]>(m_location)); break;
	case GL_FLOAT_VEC4: m_setter.reset(new GlGLSLParameterSetter<float[4]>(m_location)); break;
	case GL_DOUBLE:      m_setter.reset(new GlGLSLParameterSetter<double>(m_location)); break;
	case GL_DOUBLE_VEC2: m_setter.reset(new GlGLSLParameterSetter<double[2]>(m_location)); break;
	case GL_DOUBLE_VEC3: m_setter.reset(new GlGLSLParameterSetter<double[3]>(m_location)); break;
	case GL_DOUBLE_VEC4: m_setter.reset(new GlGLSLParameterSetter<double[4]>(m_location)); break;
	//case GL_INT:      m_setter.reset(new GlGLSLParameterSetter<int>(m_location)); break;
	//case GL_INT_VEC2: m_setter.reset(new GlGLSLParameterSetter<int[2]>(m_location)); break;
	//case GL_INT_VEC3: m_setter.reset(new GlGLSLParameterSetter<int[3]>(m_location)); break;
	//case GL_INT_VEC4: m_setter.reset(new GlGLSLParameterSetter<int[4]>(m_location)); break;
	//case GL_UNSIGNED_INT:      m_setter.reset(new GlGLSLParameterSetter<unsigned int>(m_location)); break;
	//case GL_UNSIGNED_INT_VEC2: m_setter.reset(new GlGLSLParameterSetter<unsigned int[2]>(m_location)); break;
	//case GL_UNSIGNED_INT_VEC3: m_setter.reset(new GlGLSLParameterSetter<unsigned int[3]>(m_location)); break;
	//case GL_UNSIGNED_INT_VEC4: m_setter.reset(new GlGLSLParameterSetter<unsigned int[4]>(m_location)); break;
	//case GL_BOOL:      m_setter.reset(new GlGLSLParameterSetter<bool>(m_location)); break;
	//case GL_BOOL_VEC2: m_setter.reset(new GlGLSLParameterSetter<bool[2]>(m_location)); break;
	//case GL_BOOL_VEC3: m_setter.reset(new GlGLSLParameterSetter<bool[3]>(m_location)); break;
	//case GL_BOOL_VEC4: m_setter.reset(new GlGLSLParameterSetter<bool[4]>(m_location)); break;
	case GL_FLOAT_MAT2: m_setter.reset(new GlGLSLParameterSetter<float[2][2]>(m_location)); break;
	case GL_FLOAT_MAT3: m_setter.reset(new GlGLSLParameterSetter<float[3][3]>(m_location)); break;
	case GL_FLOAT_MAT4: m_setter.reset(new GlGLSLParameterSetter<float[4][4]>(m_location)); break;
	default: BKSGE_ASSERT(false); break;
	}
}

BKSGE_INLINE
GlGLSLParameter::~GlGLSLParameter()
{
}

BKSGE_INLINE void
GlGLSLParameter::LoadParameter(
	ShaderParameterMap const& shader_parameter_map)
{
	if (m_setter)
	{
		m_setter->SetParameter(shader_parameter_map[m_name]);
	}
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_GLSL_PARAMETER_INL_HPP
