/**
 *	@file	gl_glsl_shader.hpp
 *
 *	@brief	GlGLSLShader の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_GLSL_SHADER_HPP
#define BKSGE_RENDER_GL_GL_GLSL_SHADER_HPP

#include <bksge/render/gl/fwd/gl_glsl_shader_fwd.hpp>
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
class GlGLSLShader
{
public:
	GlGLSLShader(ShaderStage stage, std::string const& source);

	~GlGLSLShader();

	GLuint id() const;

private:
	GLuint m_id;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_glsl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_GLSL_SHADER_HPP
