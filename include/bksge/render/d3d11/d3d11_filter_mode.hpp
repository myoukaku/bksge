/**
 *	@file	d3d11_filter_mode.hpp
 *
 *	@brief	D3D11FilterMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_FILTER_MODE_HPP
#define BKSGE_RENDER_D3D11_D3D11_FILTER_MODE_HPP

#include <bksge/render/filter_mode.hpp>
#include <bksge/render/d3d11/d3d11.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11FilterMode
{
public:
	D3D11FilterMode(FilterMode min_filter, FilterMode mag_filter);

	operator D3D11_FILTER() const;

private:
	D3D11_FILTER	m_filter;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_filter_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_FILTER_MODE_HPP
