/**
 *	@file	gl_glsl_parameter.hpp
 *
 *	@brief	GlGLSLParameter の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_GLSL_PARAMETER_HPP
#define BKSGE_RENDER_GL_GL_GLSL_PARAMETER_HPP

#include <bksge/render/gl/fwd/gl_glsl_parameter_fwd.hpp>
#include <bksge/render/gl/fwd/gl_glsl_parameter_setter_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/detail/fwd/shader_parameter_map_fwd.hpp>
#include <string>
#include <memory>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class GlGLSLParameter
{
public:
	GlGLSLParameter(GLuint program, GLint index);

	~GlGLSLParameter();

	void LoadParameter(ShaderParameterMap const& shader_parameter_map);

private:
	std::string	m_name;
	GLint		m_size;
	GLenum		m_type;
	GLint		m_location;
	std::unique_ptr<GlGLSLParameterSetterBase>	m_setter;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_glsl_parameter_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_GLSL_PARAMETER_HPP
