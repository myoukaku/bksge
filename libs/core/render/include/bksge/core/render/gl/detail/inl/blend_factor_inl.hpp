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

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlBlendFactor(bksge::BlendFactor blend_factor)
{
	switch (blend_factor)
	{
	case bksge::BlendFactor::kZero:             return GL_ZERO;
	case bksge::BlendFactor::kOne:              return GL_ONE;
	case bksge::BlendFactor::kSrcColor:         return GL_SRC_COLOR;
	case bksge::BlendFactor::kInvSrcColor:      return GL_ONE_MINUS_SRC_COLOR;
	case bksge::BlendFactor::kSrcAlpha:         return GL_SRC_ALPHA;
	case bksge::BlendFactor::kInvSrcAlpha:      return GL_ONE_MINUS_SRC_ALPHA;
	case bksge::BlendFactor::kDestAlpha:        return GL_DST_ALPHA;
	case bksge::BlendFactor::kInvDestAlpha:     return GL_ONE_MINUS_DST_ALPHA;
	case bksge::BlendFactor::kDestColor:        return GL_DST_COLOR;
	case bksge::BlendFactor::kInvDestColor:     return GL_ONE_MINUS_DST_COLOR;
	case bksge::BlendFactor::kSrcAlphaSaturate: return GL_SRC_ALPHA_SATURATE;
	case bksge::BlendFactor::kBlendFactor:      return GL_CONSTANT_COLOR;
	case bksge::BlendFactor::kInvBlendFactor:   return GL_ONE_MINUS_CONSTANT_COLOR;
	case bksge::BlendFactor::kSrc1Color:        return GL_SRC1_COLOR;
	case bksge::BlendFactor::kInvSrc1Color:     return GL_ONE_MINUS_SRC1_COLOR;
	case bksge::BlendFactor::kSrc1Alpha:        return GL_SRC1_ALPHA;
	case bksge::BlendFactor::kInvSrc1Alpha:     return GL_ONE_MINUS_SRC1_ALPHA;
		// GL_CONSTANT_ALPHA
		// GL_ONE_MINUS_CONSTANT_ALPHA
	}
	return GL_ZERO;
}

}	// namespace detail

BKSGE_INLINE
BlendFactor::BlendFactor(bksge::BlendFactor blend_factor)
	: m_blend_factor(detail::ToGlBlendFactor(blend_factor))
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
