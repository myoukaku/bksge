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
#include <bksge/core/render/sampled_texture.hpp>
#include <bksge/fnd/assert.hpp>
#include <vector>

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

	std::vector<::GLchar> buf(max_length + 1);
	::glGetActiveUniform(
		program, index, max_length, nullptr, &m_size, &m_type, buf.data());
	m_name = buf.data();
	m_location = ::glGetUniformLocation(program, m_name.c_str());

	::glGetActiveUniformsiv(program, 1, &index, GL_UNIFORM_OFFSET, &m_offset);

	//std::cout
	//	<< m_name << ", "
	//	<< m_location << ", "
	//	<< m_offset << ", "
	//	<< m_size << ", "
	//	<< m_type << std::endl;

	switch (m_type)
	{
	case GL_FLOAT:      m_setter.reset(new GlslParameterSetter<float>()); break;
	case GL_FLOAT_VEC2: m_setter.reset(new GlslParameterSetter<float[2]>()); break;
	case GL_FLOAT_VEC3: m_setter.reset(new GlslParameterSetter<float[3]>()); break;
	case GL_FLOAT_VEC4: m_setter.reset(new GlslParameterSetter<float[4]>()); break;
	case GL_DOUBLE:      m_setter.reset(new GlslParameterSetter<double>()); break;
	case GL_DOUBLE_VEC2: m_setter.reset(new GlslParameterSetter<double[2]>()); break;
	case GL_DOUBLE_VEC3: m_setter.reset(new GlslParameterSetter<double[3]>()); break;
	case GL_DOUBLE_VEC4: m_setter.reset(new GlslParameterSetter<double[4]>()); break;
	//case GL_INT:      m_setter.reset(new GlslParameterSetter<int>()); break;
	//case GL_INT_VEC2: m_setter.reset(new GlslParameterSetter<int[2]>()); break;
	//case GL_INT_VEC3: m_setter.reset(new GlslParameterSetter<int[3]>()); break;
	//case GL_INT_VEC4: m_setter.reset(new GlslParameterSetter<int[4]>()); break;
	//case GL_UNSIGNED_INT:      m_setter.reset(new GlslParameterSetter<unsigned int>()); break;
	//case GL_UNSIGNED_INT_VEC2: m_setter.reset(new GlslParameterSetter<unsigned int[2]>()); break;
	//case GL_UNSIGNED_INT_VEC3: m_setter.reset(new GlslParameterSetter<unsigned int[3]>()); break;
	//case GL_UNSIGNED_INT_VEC4: m_setter.reset(new GlslParameterSetter<unsigned int[4]>()); break;
	//case GL_BOOL:      m_setter.reset(new GlslParameterSetter<bool>()); break;
	//case GL_BOOL_VEC2: m_setter.reset(new GlslParameterSetter<bool[2]>()); break;
	//case GL_BOOL_VEC3: m_setter.reset(new GlslParameterSetter<bool[3]>()); break;
	//case GL_BOOL_VEC4: m_setter.reset(new GlslParameterSetter<bool[4]>()); break;
	case GL_FLOAT_MAT2: m_setter.reset(new GlslParameterSetter<float[2][2]>()); break;
	case GL_FLOAT_MAT3: m_setter.reset(new GlslParameterSetter<float[3][3]>()); break;
	case GL_FLOAT_MAT4: m_setter.reset(new GlslParameterSetter<float[4][4]>()); break;
	case GL_SAMPLER_2D: m_setter.reset(new GlslParameterSetter<bksge::SampledTexture>()); break;
	default: BKSGE_ASSERT(false); break;
	}
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
		m_setter->SetParameter(resource_pool, shader_parameter_map[m_name], m_location);
	}
}

BKSGE_INLINE void
GlslParameter::LoadUniformBuffer(
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	if (m_setter)
	{
		m_setter->LoadUniformBuffer(shader_parameter_map[m_name], m_offset);
	}
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_PARAMETER_INL_HPP
