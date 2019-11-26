/**
 *	@file	wrap_mode.hpp
 *
 *	@brief	WrapMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_WRAP_MODE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_WRAP_MODE_HPP

#include <bksge/render/fwd/wrap_mode_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief
 */
class WrapMode
{
public:
	explicit WrapMode(bksge::WrapMode wrap_mode);

	operator ::D3D12_TEXTURE_ADDRESS_MODE() const;

private:
	::D3D12_TEXTURE_ADDRESS_MODE	m_wrap_mode;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/wrap_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_WRAP_MODE_HPP
