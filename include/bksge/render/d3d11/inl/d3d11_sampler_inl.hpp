/**
 *	@file	d3d11_sampler_inl.hpp
 *
 *	@brief	D3D11Sampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_SAMPLER_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_SAMPLER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_sampler.hpp>
#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/d3d11/d3d11_filter_mode.hpp>
#include <bksge/render/d3d11/d3d11_wrap_mode.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/filter_mode.hpp>
#include <bksge/render/wrap_mode.hpp>
#include <bksge/render/sampler.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11Sampler::D3D11Sampler(D3D11Renderer* renderer, Sampler const& sampler)
{
	m_texture = renderer->GetD3D11Texture(sampler.source());

	D3D11_SAMPLER_DESC desc;
	desc.Filter = D3D11FilterMode(sampler.min_filter(), sampler.mag_filter());
	desc.AddressU = D3D11WrapMode(sampler.wrap_s());
	desc.AddressV = D3D11WrapMode(sampler.wrap_t());
	desc.AddressW = D3D11WrapMode(sampler.wrap_r());
	desc.MipLODBias = 0;
	desc.MaxAnisotropy = 16;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.BorderColor[0] = sampler.border_color().r();
	desc.BorderColor[1] = sampler.border_color().g();
	desc.BorderColor[2] = sampler.border_color().b();
	desc.BorderColor[3] = sampler.border_color().a();
	desc.MinLOD = -D3D11_FLOAT32_MAX;
	desc.MaxLOD =  D3D11_FLOAT32_MAX;

	m_state = renderer->CreateSamplerState(desc);
}

BKSGE_INLINE
D3D11Sampler::~D3D11Sampler()
{
}

BKSGE_INLINE
std::shared_ptr<D3D11Texture> const& D3D11Sampler::texture(void) const
{
	return m_texture;
}

BKSGE_INLINE
ID3D11SamplerState* D3D11Sampler::state(void) const
{
	return m_state.Get();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_SAMPLER_INL_HPP
