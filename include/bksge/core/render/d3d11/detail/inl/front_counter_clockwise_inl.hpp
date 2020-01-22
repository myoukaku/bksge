/**
 *	@file	front_counter_clockwise_inl.hpp
 *
 *	@brief	FrontCounterClockwise の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FRONT_COUNTER_CLOCKWISE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FRONT_COUNTER_CLOCKWISE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/front_counter_clockwise.hpp>
#include <bksge/core/render/d3d11/detail/bool.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/front_face.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
FrontCounterClockwise::FrontCounterClockwise(bksge::FrontFace front_face)
	: m_front_counter_clockwise(d3d11::Bool(
		front_face == bksge::FrontFace::kCounterClockwise))
{}

BKSGE_INLINE
FrontCounterClockwise::operator BOOL() const
{
	return m_front_counter_clockwise;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FRONT_COUNTER_CLOCKWISE_INL_HPP
