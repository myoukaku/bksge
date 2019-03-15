/**
 *	@file	gl_shader_program.hpp
 *
 *	@brief	GlShaderProgram の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_SHADER_PROGRAM_HPP
#define BKSGE_RENDER_GL_GL_SHADER_PROGRAM_HPP

#include <bksge/render/gl/fwd/gl_shader_program_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/shader_stage.hpp>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class GlShaderProgram
{
public:
	GlShaderProgram(ShaderStage stage, std::string const& source);

	~GlShaderProgram();

	GLuint id() const;

private:
	GLuint m_id;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_shader_program_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_SHADER_PROGRAM_HPP
