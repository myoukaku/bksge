/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	FillMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_FILL_MODE_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_FILL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/fill_mode.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/fill_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_FILL_MODE
D3D11FillMode(bksge::FillMode fill_mode)
{
	static std::unordered_map<bksge::FillMode, ::D3D11_FILL_MODE> const m =
	{
		{ bksge::FillMode::kSolid,     D3D11_FILL_SOLID },
		{ bksge::FillMode::kWireframe, D3D11_FILL_WIREFRAME },
	};

	return m.at(fill_mode);
}

}	// namespace detail

BKSGE_INLINE
FillMode::FillMode(bksge::FillMode fill_mode)
	: m_fill_mode(detail::D3D11FillMode(fill_mode))
{}

BKSGE_INLINE
FillMode::operator ::D3D11_FILL_MODE() const
{
	return m_fill_mode;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_FILL_MODE_INL_HPP
