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

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlShaderStage(bksge::ShaderStage stage)
{
	switch (stage)
	{
	case bksge::ShaderStage::kVertex:                 return GL_VERTEX_SHADER;
	case bksge::ShaderStage::kGeometry:               return GL_GEOMETRY_SHADER;
	case bksge::ShaderStage::kFragment:               return GL_FRAGMENT_SHADER;
	case bksge::ShaderStage::kTessellationControl:    return GL_TESS_CONTROL_SHADER;
	case bksge::ShaderStage::kTessellationEvaluation: return GL_TESS_EVALUATION_SHADER;
	}
	return GL_VERTEX_SHADER;
}

}	// namespace detail

BKSGE_INLINE
ShaderStage::ShaderStage(bksge::ShaderStage stage)
	: m_stage(detail::ToGlShaderStage(stage))
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
