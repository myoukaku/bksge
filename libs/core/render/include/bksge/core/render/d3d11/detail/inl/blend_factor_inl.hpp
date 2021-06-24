/**
 *	@file	blend_factor_inl.hpp
 *
 *	@brief	BlendFactor クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_BLEND_FACTOR_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_BLEND_FACTOR_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/blend_factor.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/blend_factor.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_BLEND
ToD3D11BlendFactor(bksge::BlendFactor blend_factor)
{
	switch (blend_factor)
	{
	case bksge::BlendFactor::kZero:             return D3D11_BLEND_ZERO;
	case bksge::BlendFactor::kOne:              return D3D11_BLEND_ONE;
	case bksge::BlendFactor::kSrcColor:         return D3D11_BLEND_SRC_COLOR;
	case bksge::BlendFactor::kInvSrcColor:      return D3D11_BLEND_INV_SRC_COLOR;
	case bksge::BlendFactor::kSrcAlpha:         return D3D11_BLEND_SRC_ALPHA;
	case bksge::BlendFactor::kInvSrcAlpha:      return D3D11_BLEND_INV_SRC_ALPHA;
	case bksge::BlendFactor::kDestAlpha:        return D3D11_BLEND_DEST_ALPHA;
	case bksge::BlendFactor::kInvDestAlpha:     return D3D11_BLEND_INV_DEST_ALPHA;
	case bksge::BlendFactor::kDestColor:        return D3D11_BLEND_DEST_COLOR;
	case bksge::BlendFactor::kInvDestColor:     return D3D11_BLEND_INV_DEST_COLOR;
	case bksge::BlendFactor::kSrcAlphaSaturate: return D3D11_BLEND_SRC_ALPHA_SAT;
	case bksge::BlendFactor::kBlendFactor:      return D3D11_BLEND_BLEND_FACTOR;
	case bksge::BlendFactor::kInvBlendFactor:   return D3D11_BLEND_INV_BLEND_FACTOR;
	case bksge::BlendFactor::kSrc1Color:        return D3D11_BLEND_SRC1_COLOR;
	case bksge::BlendFactor::kInvSrc1Color:     return D3D11_BLEND_INV_SRC1_COLOR;
	case bksge::BlendFactor::kSrc1Alpha:        return D3D11_BLEND_SRC1_ALPHA;
	case bksge::BlendFactor::kInvSrc1Alpha:     return D3D11_BLEND_INV_SRC1_ALPHA;
	}
	return D3D11_BLEND_ZERO;
}

}	// namespace detail

BKSGE_INLINE
BlendFactor::BlendFactor(bksge::BlendFactor blend_factor)
	: m_blend_factor(detail::ToD3D11BlendFactor(blend_factor))
{}

BKSGE_INLINE
BlendFactor::operator ::D3D11_BLEND() const
{
	return m_blend_factor;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_BLEND_FACTOR_INL_HPP
