/**
 *	@file	blend_factor_inl.hpp
 *
 *	@brief	BlendFactor の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_FACTOR_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_FACTOR_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/blend_factor.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/blend_factor.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_BLEND
ToD3D12BlendFactor(bksge::BlendFactor blend_factor)
{
	static std::unordered_map<bksge::BlendFactor, ::D3D12_BLEND> const m =
	{
		{ bksge::BlendFactor::kZero,             D3D12_BLEND_ZERO },
		{ bksge::BlendFactor::kOne,				 D3D12_BLEND_ONE },
		{ bksge::BlendFactor::kSrcColor,		 D3D12_BLEND_SRC_COLOR },
		{ bksge::BlendFactor::kInvSrcColor,		 D3D12_BLEND_INV_SRC_COLOR },
		{ bksge::BlendFactor::kSrcAlpha,		 D3D12_BLEND_SRC_ALPHA },
		{ bksge::BlendFactor::kInvSrcAlpha,		 D3D12_BLEND_INV_SRC_ALPHA },
		{ bksge::BlendFactor::kDestAlpha,		 D3D12_BLEND_DEST_ALPHA },
		{ bksge::BlendFactor::kInvDestAlpha,	 D3D12_BLEND_INV_DEST_ALPHA },
		{ bksge::BlendFactor::kDestColor,		 D3D12_BLEND_DEST_COLOR },
		{ bksge::BlendFactor::kInvDestColor,	 D3D12_BLEND_INV_DEST_COLOR },
		{ bksge::BlendFactor::kSrcAlphaSaturate, D3D12_BLEND_SRC_ALPHA_SAT },
		{ bksge::BlendFactor::kBlendFactor,		 D3D12_BLEND_BLEND_FACTOR },
		{ bksge::BlendFactor::kInvBlendFactor,	 D3D12_BLEND_INV_BLEND_FACTOR },
		{ bksge::BlendFactor::kSrc1Color,		 D3D12_BLEND_SRC1_COLOR },
		{ bksge::BlendFactor::kInvSrc1Color,	 D3D12_BLEND_INV_SRC1_COLOR },
		{ bksge::BlendFactor::kSrc1Alpha,		 D3D12_BLEND_SRC1_ALPHA },
		{ bksge::BlendFactor::kInvSrc1Alpha,	 D3D12_BLEND_INV_SRC1_ALPHA },
	};

	return m.at(blend_factor);
}

}	// namespace detail

BKSGE_INLINE
BlendFactor::BlendFactor(bksge::BlendFactor blend_factor)
	: m_blend_factor(detail::ToD3D12BlendFactor(blend_factor))
{}

BKSGE_INLINE
BlendFactor::operator D3D12_BLEND() const
{
	return m_blend_factor;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_FACTOR_INL_HPP
