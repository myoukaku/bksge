/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_SAMPLER_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_SAMPLER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/sampler.hpp>
#include <bksge/core/render/d3d11/detail/filter_mode.hpp>
#include <bksge/core/render/d3d11/detail/address_mode.hpp>
#include <bksge/core/render/d3d11/detail/border_color.hpp>
#include <bksge/core/render/d3d11/detail/device.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/address_mode.hpp>
#include <bksge/core/render/sampler.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
Sampler::Sampler(Device* device, bksge::Sampler const& sampler)
{
	auto const border_color = d3d11::BorderColor(sampler.border_color());

	::D3D11_SAMPLER_DESC desc;
	desc.Filter         = d3d11::FilterMode(sampler.min_filter(), sampler.mag_filter(), sampler.mip_filter());
	desc.AddressU       = d3d11::AddressMode(sampler.address_mode_u());
	desc.AddressV       = d3d11::AddressMode(sampler.address_mode_v());
	desc.AddressW       = d3d11::AddressMode(sampler.address_mode_w());
	desc.MipLODBias     = 0;
	desc.MaxAnisotropy  = 16;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.BorderColor[0] = border_color[0];
	desc.BorderColor[1] = border_color[1];
	desc.BorderColor[2] = border_color[2];
	desc.BorderColor[3] = border_color[3];
	desc.MinLOD         = sampler.enable_mipmap() ? sampler.min_lod() : 0.0f;
	desc.MaxLOD         = sampler.enable_mipmap() ? sampler.max_lod() : 0.0f;

	m_state = device->CreateSamplerState(desc);
}

BKSGE_INLINE
Sampler::~Sampler()
{
}

BKSGE_INLINE ComPtr<::ID3D11SamplerState> const&
Sampler::state(void) const
{
	return m_state;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_SAMPLER_INL_HPP
