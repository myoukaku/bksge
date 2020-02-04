/**
 *	@file	glsl_shader.hpp
 *
 *	@brief	GlslShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_GLSL_SHADER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_GLSL_SHADER_HPP

#include <bksge/core/render/gl/detail/fwd/glsl_shader_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/shader_stage.hpp>
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
	// noncopyable
	GlslShader(GlslShader const&) = delete;
	GlslShader& operator=(GlslShader const&) = delete;

private:
	::GLuint m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/glsl_shader_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GLSL_SHADER_HPP
