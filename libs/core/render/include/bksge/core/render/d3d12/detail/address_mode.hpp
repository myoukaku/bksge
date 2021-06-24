/**
 *	@file	address_mode.hpp
 *
 *	@brief	AddressMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_ADDRESS_MODE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_ADDRESS_MODE_HPP

#include <bksge/core/render/fwd/address_mode_fwd.hpp>
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
class AddressMode
{
public:
	explicit AddressMode(bksge::AddressMode address_mode);

	operator ::D3D12_TEXTURE_ADDRESS_MODE() const;

private:
	::D3D12_TEXTURE_ADDRESS_MODE	m_address_mode;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/address_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_ADDRESS_MODE_HPP
