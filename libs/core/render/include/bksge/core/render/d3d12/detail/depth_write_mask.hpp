﻿/**
 *	@file	depth_write_mask.hpp
 *
 *	@brief	DepthWriteMask クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_WRITE_MASK_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_WRITE_MASK_HPP

#include <bksge/core/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief
 */
class DepthWriteMask
{
public:
	explicit DepthWriteMask(bool write_enable);

	operator ::D3D12_DEPTH_WRITE_MASK() const;

private:
	::D3D12_DEPTH_WRITE_MASK	m_depth_write_mask;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/depth_write_mask_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_WRITE_MASK_HPP
