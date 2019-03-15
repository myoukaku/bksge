/**
 *	@file	gl_shader_program_inl.hpp
 *
 *	@brief	GlShaderProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_SHADER_PROGRAM_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_SHADER_PROGRAM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_shader_program.hpp>
#include <bksge/render/gl/gl_shader_stage.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/assert.hpp>
#include <string>
#include <iostream>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlShaderProgram::GlShaderProgram(
	ShaderStage stage,
	std::string const& source)
{
	m_id = glCreateShader(ToGlShaderStage(stage));
	BKSGE_ASSERT(m_id != 0u);

	const auto* src = source.c_str();
	glShaderSource(m_id, 1, &src, nullptr);
	glCompileShader(m_id);

	GLint compiled;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint log_length;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length != 0)
		{
			std::string info_log;
			info_log.resize(log_length);
			GLsizei length;
			glGetShaderInfoLog(m_id, log_length, &length, &info_log[0]);

			std::cout << info_log << std::endl;
		}
	}
}

BKSGE_INLINE
GlShaderProgram::~GlShaderProgram()
{
	glDeleteShader(m_id);
}

BKSGE_INLINE
GLuint GlShaderProgram::id() const
{
	return m_id;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_SHADER_PROGRAM_INL_HPP
