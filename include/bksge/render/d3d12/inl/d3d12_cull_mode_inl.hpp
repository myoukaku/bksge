/**
 *	@file	d3d12_cull_mode_inl.hpp
 *
 *	@brief	ToD3D12CullMode 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_CULL_MODE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_CULL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_cull_mode.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/cull_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE ::D3D12_CULL_MODE
ToD3D12CullMode(CullMode cull_mode)
{
	static std::unordered_map<CullMode, ::D3D12_CULL_MODE> const m =
	{
		{ CullMode::kNone,   D3D12_CULL_MODE_NONE },
		{ CullMode::kFront,  D3D12_CULL_MODE_FRONT },
		{ CullMode::kBack,   D3D12_CULL_MODE_BACK },
	};

	return m.at(cull_mode);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_CULL_MODE_INL_HPP
