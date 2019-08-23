/**
 *	@file	cull_mode_inl.hpp
 *
 *	@brief	ToD3D12CullMode 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_CULL_MODE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_CULL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/cull_mode.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/cull_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE ::D3D12_CULL_MODE
ToD3D12CullMode(bksge::CullMode cull_mode)
{
	static std::unordered_map<bksge::CullMode, ::D3D12_CULL_MODE> const m =
	{
		{ bksge::CullMode::kNone,   D3D12_CULL_MODE_NONE },
		{ bksge::CullMode::kFront,  D3D12_CULL_MODE_FRONT },
		{ bksge::CullMode::kBack,   D3D12_CULL_MODE_BACK },
	};

	return m.at(cull_mode);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_CULL_MODE_INL_HPP
