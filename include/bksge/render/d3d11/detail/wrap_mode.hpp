/**
 *	@file	wrap_mode.hpp
 *
 *	@brief	WrapMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_WRAP_MODE_HPP
#define BKSGE_RENDER_D3D11_DETAIL_WRAP_MODE_HPP

#include <bksge/render/wrap_mode.hpp>
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
class WrapMode
{
public:
	explicit WrapMode(bksge::WrapMode wrap_mode);

	operator ::D3D11_TEXTURE_ADDRESS_MODE() const;

private:
	::D3D11_TEXTURE_ADDRESS_MODE	m_wrap_mode;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/wrap_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_WRAP_MODE_HPP
