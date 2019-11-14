/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_SAMPLER_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_SAMPLER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/sampler.hpp>
#include <bksge/render/d3d11/detail/filter_mode.hpp>
#include <bksge/render/d3d11/detail/wrap_mode.hpp>
#include <bksge/render/d3d11/detail/device.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/filter_mode.hpp>
#include <bksge/render/wrap_mode.hpp>
#include <bksge/render/sampler.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
Sampler::Sampler(Device* device, bksge::Sampler const& sampler)
{
	::D3D11_SAMPLER_DESC desc;
	desc.Filter         = FilterMode(sampler.min_filter(), sampler.mag_filter());
	desc.AddressU       = WrapMode(sampler.wrap_s());
	desc.AddressV       = WrapMode(sampler.wrap_t());
	desc.AddressW       = WrapMode(sampler.wrap_r());
	desc.MipLODBias     = 0;
	desc.MaxAnisotropy  = 16;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.BorderColor[0] = sampler.border_color().r();
	desc.BorderColor[1] = sampler.border_color().g();
	desc.BorderColor[2] = sampler.border_color().b();
	desc.BorderColor[3] = sampler.border_color().a();
	desc.MinLOD         = -D3D11_FLOAT32_MAX;
	desc.MaxLOD         =  D3D11_FLOAT32_MAX;

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

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_SAMPLER_INL_HPP
