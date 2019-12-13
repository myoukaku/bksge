/**
 *	@file	shader_stage_inl.hpp
 *
 *	@brief	ShaderStage クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_SHADER_STAGE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_SHADER_STAGE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/shader_stage.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/shader_stage.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
GlShaderStage(bksge::ShaderStage stage)
{
	static std::unordered_map<bksge::ShaderStage, ::GLenum> const m =
	{
		{ bksge::ShaderStage::kVertex,					GL_VERTEX_SHADER },
		{ bksge::ShaderStage::kGeometry,				GL_GEOMETRY_SHADER },
		{ bksge::ShaderStage::kFragment,				GL_FRAGMENT_SHADER },
		{ bksge::ShaderStage::kTessellationControl,		GL_TESS_CONTROL_SHADER },
		{ bksge::ShaderStage::kTessellationEvaluation,	GL_TESS_EVALUATION_SHADER },
	};

	return m.at(stage);
}

}	// namespace detail

BKSGE_INLINE
ShaderStage::ShaderStage(bksge::ShaderStage stage)
	: m_stage(detail::GlShaderStage(stage))
{}

BKSGE_INLINE
ShaderStage::operator ::GLenum() const
{
	return m_stage;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_SHADER_STAGE_INL_HPP
