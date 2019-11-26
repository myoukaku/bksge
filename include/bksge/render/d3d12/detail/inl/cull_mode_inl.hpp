/**
 *	@file	cull_mode_inl.hpp
 *
 *	@brief	CullMode の実装
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

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_CULL_MODE
ToD3D12CullMode(bksge::CullMode cull_mode)
{
	switch (cull_mode)
	{
	case bksge::CullMode::kNone:   return D3D12_CULL_MODE_NONE;
	case bksge::CullMode::kFront:  return D3D12_CULL_MODE_FRONT;
	case bksge::CullMode::kBack:   return D3D12_CULL_MODE_BACK;
	};
	return D3D12_CULL_MODE_NONE;
}

}	// namespace detail

BKSGE_INLINE
CullMode::CullMode(bksge::CullMode cull_mode)
	: m_cull_mode(detail::ToD3D12CullMode(cull_mode))
{}

BKSGE_INLINE
CullMode::operator D3D12_CULL_MODE() const
{
	return m_cull_mode;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_CULL_MODE_INL_HPP
