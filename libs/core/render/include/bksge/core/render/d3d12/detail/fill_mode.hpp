﻿/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FILL_MODE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FILL_MODE_HPP

#include <bksge/core/render/fwd/fill_mode_fwd.hpp>
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
class FillMode
{
public:
	explicit FillMode(bksge::FillMode fill_mode);

	operator ::D3D12_FILL_MODE() const;

private:
	::D3D12_FILL_MODE	m_fill_mode;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/fill_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FILL_MODE_HPP
