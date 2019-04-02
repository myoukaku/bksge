/**
 *	@file	gl_shader_inl.hpp
 *
 *	@brief	GlShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_SHADER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_SHADER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_shader.hpp>
#include <bksge/render/gl/gl_shader_program.hpp>
#include <bksge/render/gl/gl_geometry.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/memory/make_unique.hpp>
#include <bksge/assert.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlShader::GlShader(Shader const& shader, GlRenderer* /*renderer*/)
{
	m_id = ::glCreateProgram();
	BKSGE_ASSERT(m_id != 0u);

	for (auto&& it : shader.program_map())
	{
		auto shader_object = bksge::make_unique<GlShaderProgram>(it.first, it.second);
		::glAttachShader(m_id, shader_object->id());
		m_programs.push_back(std::move(shader_object));
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

	::glUseProgram(m_id);
}

BKSGE_INLINE
GlShader::~GlShader()
{
	::glDeleteProgram(m_id);
}

BKSGE_INLINE
void GlShader::Render(GlGeometry const* geometry)
{
	geometry->Bind();

	// TODO
	::glEnableVertexAttribArray(0);
	::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	geometry->Draw();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_SHADER_INL_HPP
