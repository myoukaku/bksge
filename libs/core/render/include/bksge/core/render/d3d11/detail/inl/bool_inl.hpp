/**
 *	@file	bool_inl.hpp
 *
 *	@brief	Bool の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_BOOL_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_BOOL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/bool.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
Bool::Bool(bool b)
	: m_bool(b ? TRUE : FALSE)
{}

BKSGE_INLINE
Bool::operator BOOL() const
{
	return m_bool;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_BOOL_INL_HPP
