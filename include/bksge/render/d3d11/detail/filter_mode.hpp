/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_FILTER_MODE_HPP
#define BKSGE_RENDER_D3D11_DETAIL_FILTER_MODE_HPP

#include <bksge/render/filter_mode.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>

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
	FilterMode(bksge::FilterMode min_filter, bksge::FilterMode mag_filter);

	operator ::D3D11_FILTER() const;

private:
	::D3D11_FILTER	m_filter;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/filter_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_FILTER_MODE_HPP
