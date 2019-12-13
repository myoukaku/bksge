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
#include <bksge/core/render/sampler.hpp>
#include <bksge/fnd/assert.hpp>
#include <string>
#include <vector>

//#include <iostream>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
GlslParameter::GlslParameter(::GLuint program, ::GLint index)
{
	::GLint max_length;
	::glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);

	std::vector<::GLchar> buf(max_length + 1);
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
	case GL_FLOAT:      m_setter.reset(new GlslParameterSetter<float>(m_location)); break;
	case GL_FLOAT_VEC2: m_setter.reset(new GlslParameterSetter<float[2]>(m_location)); break;
	case GL_FLOAT_VEC3: m_setter.reset(new GlslParameterSetter<float[3]>(m_location)); break;
	case GL_FLOAT_VEC4: m_setter.reset(new GlslParameterSetter<float[4]>(m_location)); break;
	case GL_DOUBLE:      m_setter.reset(new GlslParameterSetter<double>(m_location)); break;
	case GL_DOUBLE_VEC2: m_setter.reset(new GlslParameterSetter<double[2]>(m_location)); break;
	case GL_DOUBLE_VEC3: m_setter.reset(new GlslParameterSetter<double[3]>(m_location)); break;
	case GL_DOUBLE_VEC4: m_setter.reset(new GlslParameterSetter<double[4]>(m_location)); break;
	//case GL_INT:      m_setter.reset(new GlslParameterSetter<int>(m_location)); break;
	//case GL_INT_VEC2: m_setter.reset(new GlslParameterSetter<int[2]>(m_location)); break;
	//case GL_INT_VEC3: m_setter.reset(new GlslParameterSetter<int[3]>(m_location)); break;
	//case GL_INT_VEC4: m_setter.reset(new GlslParameterSetter<int[4]>(m_location)); break;
	//case GL_UNSIGNED_INT:      m_setter.reset(new GlslParameterSetter<unsigned int>(m_location)); break;
	//case GL_UNSIGNED_INT_VEC2: m_setter.reset(new GlslParameterSetter<unsigned int[2]>(m_location)); break;
	//case GL_UNSIGNED_INT_VEC3: m_setter.reset(new GlslParameterSetter<unsigned int[3]>(m_location)); break;
	//case GL_UNSIGNED_INT_VEC4: m_setter.reset(new GlslParameterSetter<unsigned int[4]>(m_location)); break;
	//case GL_BOOL:      m_setter.reset(new GlslParameterSetter<bool>(m_location)); break;
	//case GL_BOOL_VEC2: m_setter.reset(new GlslParameterSetter<bool[2]>(m_location)); break;
	//case GL_BOOL_VEC3: m_setter.reset(new GlslParameterSetter<bool[3]>(m_location)); break;
	//case GL_BOOL_VEC4: m_setter.reset(new GlslParameterSetter<bool[4]>(m_location)); break;
	case GL_FLOAT_MAT2: m_setter.reset(new GlslParameterSetter<float[2][2]>(m_location)); break;
	case GL_FLOAT_MAT3: m_setter.reset(new GlslParameterSetter<float[3][3]>(m_location)); break;
	case GL_FLOAT_MAT4: m_setter.reset(new GlslParameterSetter<float[4][4]>(m_location)); break;
	case GL_SAMPLER_2D: m_setter.reset(new GlslParameterSetter<bksge::Sampler>(m_location)); break;
	default: BKSGE_ASSERT(false); break;
	}
}

BKSGE_INLINE
GlslParameter::~GlslParameter()
{
}

BKSGE_INLINE void
GlslParameter::LoadParameter(
	ResourceCache* resource_cache,
	ShaderParameterMap const& shader_parameter_map)
{
	if (m_setter)
	{
		m_setter->SetParameter(resource_cache, shader_parameter_map[m_name]);
	}
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_INL_HPP
