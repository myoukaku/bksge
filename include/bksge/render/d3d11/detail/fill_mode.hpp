/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_FILL_MODE_HPP
#define BKSGE_RENDER_D3D11_DETAIL_FILL_MODE_HPP

#include <bksge/render/fwd/fill_mode_fwd.hpp>
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
class FillMode
{
public:
	FillMode(bksge::FillMode fill_mode);

	operator ::D3D11_FILL_MODE() const;

private:
	::D3D11_FILL_MODE	m_fill_mode;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/fill_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_FILL_MODE_HPP
