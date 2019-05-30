﻿/**
 *	@file	gl_glsl_program_inl.hpp
 *
 *	@brief	GlGLSLProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_GLSL_PROGRAM_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_GLSL_PROGRAM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_glsl_program.hpp>
#include <bksge/render/gl/gl_glsl_shader.hpp>
#include <bksge/render/gl/gl_glsl_parameter.hpp>
#include <bksge/render/gl/gl_geometry.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/memory/make_unique.hpp>
#include <bksge/assert.hpp>
#include <string>
#include <utility>
#include <iostream>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlGLSLProgram::GlGLSLProgram(Shader const& shader)
{
	m_id = ::glCreateProgram();
	BKSGE_ASSERT(m_id != 0u);

	for (auto&& it : shader)
	{
		auto shader_object = bksge::make_unique<GlGLSLShader>(it.first, it.second);
		::glAttachShader(m_id, shader_object->id());
		m_shaders.push_back(std::move(shader_object));
	}

	::glLinkProgram(m_id);

	GLint linked;
	::glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint log_length;
		::glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length != 0)
		{
			std::string info_log;
			info_log.resize(log_length);
			GLsizei length;
			::glGetProgramInfoLog(m_id, log_length, &length, &info_log[0]);

			std::cout << info_log << std::endl;
		}
	}

	GLint uniform_count;
	::glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniform_count);

	for (GLint i = 0; i < uniform_count; i++)
	{
		auto parameter = bksge::make_unique<GlGLSLParameter>(m_id, i);
		m_parameters.push_back(std::move(parameter));
	}
}

BKSGE_INLINE
GlGLSLProgram::~GlGLSLProgram()
{
	::glDeleteProgram(m_id);
}

BKSGE_INLINE void
GlGLSLProgram::Render(
	GlGeometry const* geometry,
	ShaderParameterMap const& shader_parameter_map)
{
	::glUseProgram(m_id);
	{
		LoadParameters(shader_parameter_map);

		geometry->Bind();
		geometry->Draw();
		geometry->Unbind();
	}
	::glUseProgram(0u);
}

BKSGE_INLINE void
GlGLSLProgram::LoadParameters(
	ShaderParameterMap const& shader_parameter_map)
{
	for (auto&& parameter : m_parameters)
	{
		parameter->LoadParameter(shader_parameter_map);
	}
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_GLSL_PROGRAM_INL_HPP
