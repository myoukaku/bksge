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
#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/filter_mode.hpp>
#include <bksge/render/wrap_mode.hpp>
#include <bksge/render/sampler.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

#if 0
BKSGE_INLINE
Sampler::Sampler(D3D11Renderer* renderer, bksge::Sampler const& sampler)
{
	m_texture = renderer->GetD3D11Texture(sampler.source());

	::D3D11_SAMPLER_DESC desc;
	desc.Filter         = D3D11FilterMode(sampler.min_filter(), sampler.mag_filter());
	desc.AddressU       = D3D11WrapMode(sampler.wrap_s());
	desc.AddressV       = D3D11WrapMode(sampler.wrap_t());
	desc.AddressW       = D3D11WrapMode(sampler.wrap_r());
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

BKSGE_INLINE std::shared_ptr<Texture> const&
Sampler::texture(void) const
{
	return m_texture;
}

BKSGE_INLINE ID3D11SamplerState*
Sampler::state(void) const
{
	return m_state.Get();
}
#endif

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_SAMPLER_INL_HPP
