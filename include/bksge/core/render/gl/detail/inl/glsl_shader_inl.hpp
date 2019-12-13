/**
 *	@file	glsl_shader_inl.hpp
 *
 *	@brief	GlslShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_SHADER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_SHADER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/glsl_shader.hpp>
#include <bksge/core/render/gl/detail/shader_stage.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/shader_stage.hpp>
#include <bksge/fnd/assert.hpp>
#include <string>
#include <iostream>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
GlslShader::GlslShader(
	bksge::ShaderStage stage,
	std::string const& source)
{
	m_id = ::glCreateShader(gl::ShaderStage(stage));
	BKSGE_ASSERT(m_id != 0u);

	const auto* src = source.c_str();
	::glShaderSource(m_id, 1, &src, nullptr);
	::glCompileShader(m_id);

	::GLint compiled;
	::glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		::GLint log_length;
		::glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length != 0)
		{
			std::string info_log;
			info_log.resize(log_length);
			::GLsizei length;
			::glGetShaderInfoLog(m_id, log_length, &length, &info_log[0]);

			std::cout << info_log << std::endl;
		}
	}
}

BKSGE_INLINE
GlslShader::~GlslShader()
{
	::glDeleteShader(m_id);
}

BKSGE_INLINE ::GLuint
GlslShader::id() const
{
	return m_id;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_GLSL_SHADER_INL_HPP
