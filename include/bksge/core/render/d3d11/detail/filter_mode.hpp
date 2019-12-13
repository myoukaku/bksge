/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_FILTER_MODE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_FILTER_MODE_HPP

#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class FilterMode
{
public:
	explicit FilterMode(bksge::FilterMode min_filter, bksge::FilterMode mag_filter);

	operator ::D3D11_FILTER() const;

private:
	::D3D11_FILTER	m_filter;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/filter_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_FILTER_MODE_HPP
