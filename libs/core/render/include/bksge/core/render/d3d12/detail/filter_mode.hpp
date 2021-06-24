/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FILTER_MODE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FILTER_MODE_HPP

#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/mipmap_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief
 */
class FilterMode
{
public:
	explicit FilterMode(
		bksge::FilterMode min_filter,
		bksge::FilterMode mag_filter,
		bksge::MipmapMode mip_filter);

	operator ::D3D12_FILTER() const;

private:
	::D3D12_FILTER	m_filter;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/filter_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FILTER_MODE_HPP
