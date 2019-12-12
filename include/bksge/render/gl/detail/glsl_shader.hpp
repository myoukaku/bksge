/**
 *	@file	glsl_shader.hpp
 *
 *	@brief	GlslShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_GLSL_SHADER_HPP
#define BKSGE_RENDER_GL_DETAIL_GLSL_SHADER_HPP

#include <bksge/render/gl/detail/fwd/glsl_shader_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/shader_stage.hpp>
#include <string>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class GlslShader
{
public:
	explicit GlslShader(bksge::ShaderStage stage, std::string const& source);

	~GlslShader();

	::GLuint id() const;

private:
	::GLuint m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/glsl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_GLSL_SHADER_HPP
