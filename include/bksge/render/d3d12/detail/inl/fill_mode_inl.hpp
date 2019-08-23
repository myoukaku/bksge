/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	ToD3D12FillMode 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_FILL_MODE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_FILL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/fill_mode.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/fill_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE ::D3D12_FILL_MODE
ToD3D12FillMode(bksge::FillMode fill_mode)
{
	static std::unordered_map<bksge::FillMode, ::D3D12_FILL_MODE> const m =
	{
		{ bksge::FillMode::kSolid,     D3D12_FILL_MODE_SOLID },
		{ bksge::FillMode::kWireframe, D3D12_FILL_MODE_WIREFRAME },
	};

	return m.at(fill_mode);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_FILL_MODE_INL_HPP
