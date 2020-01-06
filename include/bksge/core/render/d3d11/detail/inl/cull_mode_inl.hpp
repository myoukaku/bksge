/**
 *	@file	cull_mode_inl.hpp
 *
 *	@brief	CullMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_CULL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_CULL_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/cull_mode.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/cull_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_CULL_MODE
ToD3D11CullMode(bksge::CullMode cull_mode)
{
	switch (cull_mode)
	{
	case bksge::CullMode::kNone:   return D3D11_CULL_NONE;
	case bksge::CullMode::kFront:  return D3D11_CULL_FRONT;
	case bksge::CullMode::kBack:   return D3D11_CULL_BACK;
	}
	return D3D11_CULL_NONE;
}

}	// namespace detail

BKSGE_INLINE
CullMode::CullMode(bksge::CullMode cull_mode)
	: m_cull_mode(detail::ToD3D11CullMode(cull_mode))
{}

BKSGE_INLINE
CullMode::operator ::D3D11_CULL_MODE() const
{
	return m_cull_mode;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_CULL_MODE_INL_HPP
