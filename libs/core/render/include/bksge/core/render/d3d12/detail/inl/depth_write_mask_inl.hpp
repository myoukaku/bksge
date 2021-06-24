/**
 *	@file	depth_write_mask_inl.hpp
 *
 *	@brief	DepthWriteMask の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_WRITE_MASK_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_WRITE_MASK_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/depth_write_mask.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
DepthWriteMask::DepthWriteMask(bool write_enable)
	: m_depth_write_mask(
		write_enable ?
		D3D12_DEPTH_WRITE_MASK_ALL :
		D3D12_DEPTH_WRITE_MASK_ZERO)
{}

BKSGE_INLINE
DepthWriteMask::operator D3D12_DEPTH_WRITE_MASK() const
{
	return m_depth_write_mask;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_WRITE_MASK_INL_HPP
