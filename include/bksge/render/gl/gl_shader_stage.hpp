/**
 *	@file	gl_shader_stage.hpp
 *
 *	@brief	ToGlShaderStage の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_SHADER_STAGE_HPP
#define BKSGE_RENDER_GL_GL_SHADER_STAGE_HPP

#include <bksge/render/shader_stage.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	ShaderStageをOpenGLのenumに変換
 */
GLenum ToGlShaderStage(ShaderStage stage);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_shader_stage_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_SHADER_STAGE_HPP
