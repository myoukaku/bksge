﻿/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	FillMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FILL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FILL_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/fill_mode.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/fill_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_FILL_MODE
ToD3D11FillMode(bksge::FillMode fill_mode)
{
	switch (fill_mode)
	{
	case bksge::FillMode::kSolid:     return D3D11_FILL_SOLID;
	case bksge::FillMode::kWireframe: return D3D11_FILL_WIREFRAME;
	}
	return D3D11_FILL_SOLID;
}

}	// namespace detail

BKSGE_INLINE
FillMode::FillMode(bksge::FillMode fill_mode)
	: m_fill_mode(detail::ToD3D11FillMode(fill_mode))
{}

BKSGE_INLINE
FillMode::operator ::D3D11_FILL_MODE() const
{
	return m_fill_mode;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FILL_MODE_INL_HPP
