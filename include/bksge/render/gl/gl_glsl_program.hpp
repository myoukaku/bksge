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
#include <bksge/render/gl/fwd/gl_glsl_parameter_fwd.hpp>
#include <bksge/render/gl/fwd/gl_geometry_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/detail/fwd/shader_parameter_map_fwd.hpp>
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
	GlGLSLProgram(Shader const& shader);

	~GlGLSLProgram();

	void Render(
		GlGeometry const* geometry,
		ShaderParameterMap const& shader_parameter_map);

private:
	void LoadParameters(ShaderParameterMap const& shader_parameter_map);

	using GlGLSLShaders    = std::vector<GlGLSLShaderUnique>;
	using GlGLSLParameters = std::vector<GlGLSLParameterUnique>;

	GLuint				m_id;
	GlGLSLShaders		m_shaders;
	GlGLSLParameters	m_parameters;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_glsl_program_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_GLSL_PROGRAM_HPP
