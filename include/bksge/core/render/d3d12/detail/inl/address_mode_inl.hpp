/**
 *	@file	address_mode_inl.hpp
 *
 *	@brief	AddressMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_ADDRESS_MODE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_ADDRESS_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/address_mode.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/address_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_TEXTURE_ADDRESS_MODE
ToD3D12AddressMode(bksge::AddressMode address_mode)
{
	switch (address_mode)
	{
	case bksge::AddressMode::kRepeat:  return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	case bksge::AddressMode::kMirror:  return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
	case bksge::AddressMode::kClamp:   return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	case bksge::AddressMode::kBorder:  return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	}
	return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
}

}	// namespace detail

BKSGE_INLINE
AddressMode::AddressMode(bksge::AddressMode address_mode)
	: m_address_mode(detail::ToD3D12AddressMode(address_mode))
{}

BKSGE_INLINE
AddressMode::operator D3D12_TEXTURE_ADDRESS_MODE() const
{
	return m_address_mode;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_ADDRESS_MODE_INL_HPP
