/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_SAMPLER_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_SAMPLER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/sampler.hpp>
#include <bksge/core/render/d3d12/detail/filter_mode.hpp>
#include <bksge/core/render/d3d12/detail/wrap_mode.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/sampler.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
Sampler::Sampler(bksge::Sampler const& sampler)
{
	m_desc.Filter         = FilterMode(sampler.min_filter(), sampler.mag_filter());
	m_desc.AddressU       = WrapMode(sampler.wrap_s());
	m_desc.AddressV       = WrapMode(sampler.wrap_t());
	m_desc.AddressW       = WrapMode(sampler.wrap_r());
	m_desc.MipLODBias     = 0;
	m_desc.MaxAnisotropy  = 16;
	m_desc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	m_desc.BorderColor[0] = sampler.border_color().r();
	m_desc.BorderColor[1] = sampler.border_color().g();
	m_desc.BorderColor[2] = sampler.border_color().b();
	m_desc.BorderColor[3] = sampler.border_color().a();
	m_desc.MinLOD         = -D3D12_FLOAT32_MAX;
	m_desc.MaxLOD         =  D3D12_FLOAT32_MAX;
}

BKSGE_INLINE
Sampler::~Sampler()
{
}

BKSGE_INLINE void
Sampler::CreateView(Device* device, ::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	device->CreateSampler(&m_desc, dest);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_SAMPLER_INL_HPP
