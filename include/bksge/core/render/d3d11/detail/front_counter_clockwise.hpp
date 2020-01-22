/**
 *	@file	front_counter_clockwise.hpp
 *
 *	@brief	FrontCounterClockwise クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_FRONT_COUNTER_CLOCKWISE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_FRONT_COUNTER_CLOCKWISE_HPP

#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/fwd/front_face_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class FrontCounterClockwise
{
public:
	explicit FrontCounterClockwise(bksge::FrontFace front_face);

	operator ::BOOL() const;

private:
	::BOOL	m_front_counter_clockwise;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/front_counter_clockwise_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_FRONT_COUNTER_CLOCKWISE_HPP
