/**
 *	@file	gl_glsl_program.hpp
 *
 *	@brief	GlGLSLProgram の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_GLSL_PROGRAM_HPP
#define BKSGE_RENDER_GL_GL_GLSL_PROGRAM_HPP

#include <bksge/render/gl/fwd/gl_glsl_program_fwd.hpp>
#include <bksge/render/gl/fwd/gl_glsl_shader_fwd.hpp>
#include <bksge/render/gl/fwd/gl_renderer_fwd.hpp>
#include <bksge/render/gl/fwd/gl_geometry_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class GlGLSLProgram
{
public:
	GlGLSLProgram(Shader const& shader, GlRenderer* renderer);

	~GlGLSLProgram();

	void Render(GlGeometry const* geometry);

private:
	using GlGLSLShaders = std::vector<GlGLSLShaderUnique>;

	GlGLSLShaders	m_shaders;
	GLuint			m_id;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_glsl_program_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_GLSL_PROGRAM_HPP
