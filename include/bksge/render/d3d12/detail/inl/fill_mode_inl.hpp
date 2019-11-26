/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	FillMode の実装
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

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_FILL_MODE
ToD3D12FillMode(bksge::FillMode fill_mode)
{
	switch (fill_mode)
	{
	case bksge::FillMode::kSolid:     return D3D12_FILL_MODE_SOLID;
	case bksge::FillMode::kWireframe: return D3D12_FILL_MODE_WIREFRAME;
	};
	return D3D12_FILL_MODE_SOLID;
}

}	// namespace detail

BKSGE_INLINE
FillMode::FillMode(bksge::FillMode fill_mode)
	: m_fill_mode(detail::ToD3D12FillMode(fill_mode))
{}

BKSGE_INLINE
FillMode::operator ::D3D12_FILL_MODE() const
{
	return m_fill_mode;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_FILL_MODE_INL_HPP
