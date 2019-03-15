/**
 *	@file	gl_shader_stage_inl.hpp
 *
 *	@brief	ToGlShaderStage の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_SHADER_STAGE_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_SHADER_STAGE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/shader_stage.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLenum ToGlShaderStage(ShaderStage stage)
{
	static std::unordered_map<ShaderStage, GLenum> const m =
	{
		{ ShaderStage::kVertex,					GL_VERTEX_SHADER },
		{ ShaderStage::kGeometry,				GL_GEOMETRY_SHADER },
		{ ShaderStage::kFragment,				GL_FRAGMENT_SHADER },
		{ ShaderStage::kTessellationControl,	GL_TESS_CONTROL_SHADER },
		{ ShaderStage::kTessellationEvaluation,	GL_TESS_EVALUATION_SHADER },
	};

	return m.at(stage);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_SHADER_STAGE_INL_HPP
