/**
 *	@file	blend_factor_inl.hpp
 *
 *	@brief	BlendFactor クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_FACTOR_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_FACTOR_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/blend_factor.hpp>
#include <bksge/core/render/blend_factor.hpp>
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
GlBlendFactor(bksge::BlendFactor mode)
{
	static std::unordered_map<bksge::BlendFactor, ::GLenum> const m =
	{
		{ bksge::BlendFactor::kZero,             GL_ZERO },
		{ bksge::BlendFactor::kOne,              GL_ONE },
		{ bksge::BlendFactor::kSrcColor,         GL_SRC_COLOR },
		{ bksge::BlendFactor::kInvSrcColor,      GL_ONE_MINUS_SRC_COLOR },
		{ bksge::BlendFactor::kSrcAlpha,         GL_SRC_ALPHA },
		{ bksge::BlendFactor::kInvSrcAlpha,      GL_ONE_MINUS_SRC_ALPHA },
		{ bksge::BlendFactor::kDestAlpha,        GL_DST_ALPHA },
		{ bksge::BlendFactor::kInvDestAlpha,     GL_ONE_MINUS_DST_ALPHA },
		{ bksge::BlendFactor::kDestColor,        GL_DST_COLOR },
		{ bksge::BlendFactor::kInvDestColor,     GL_ONE_MINUS_DST_COLOR },
		{ bksge::BlendFactor::kSrcAlphaSaturate, GL_SRC_ALPHA_SATURATE },
		{ bksge::BlendFactor::kBlendFactor,      GL_CONSTANT_COLOR },
		{ bksge::BlendFactor::kInvBlendFactor,   GL_ONE_MINUS_CONSTANT_COLOR },
		{ bksge::BlendFactor::kSrc1Color,        GL_SRC1_COLOR },
		{ bksge::BlendFactor::kInvSrc1Color,     GL_ONE_MINUS_SRC1_COLOR },
		{ bksge::BlendFactor::kSrc1Alpha,        GL_SRC1_ALPHA },
		{ bksge::BlendFactor::kInvSrc1Alpha,     GL_ONE_MINUS_SRC1_ALPHA },
		// GL_CONSTANT_ALPHA
		// GL_ONE_MINUS_CONSTANT_ALPHA
	};

	return m.at(mode);
}

}	// namespace detail

BKSGE_INLINE
BlendFactor::BlendFactor(bksge::BlendFactor blend_factor)
	: m_blend_factor(detail::GlBlendFactor(blend_factor))
{}

BKSGE_INLINE
BlendFactor::operator ::GLenum() const
{
	return m_blend_factor;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_FACTOR_INL_HPP
