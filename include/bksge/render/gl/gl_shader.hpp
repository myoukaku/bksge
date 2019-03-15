/**
 *	@file	gl_shader.hpp
 *
 *	@brief	GlShader の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_SHADER_HPP
#define BKSGE_RENDER_GL_GL_SHADER_HPP

#include <bksge/render/gl/fwd/gl_shader_fwd.hpp>
#include <bksge/render/gl/fwd/gl_shader_program_fwd.hpp>
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
class GlShader
{
public:
	GlShader(Shader const& shader, GlRenderer* renderer);

	~GlShader();

	void Render(GlGeometry const* geometry);

private:
	using GlShaderPrograms = std::vector<GlShaderProgramUnique>;

	GlShaderPrograms	m_programs;
	GLuint				m_id;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_SHADER_HPP
