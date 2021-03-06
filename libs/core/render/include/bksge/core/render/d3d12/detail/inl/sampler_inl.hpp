﻿/**
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
#include <bksge/core/render/d3d12/detail/address_mode.hpp>
#include <bksge/core/render/d3d12/detail/border_color.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/address_mode.hpp>
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
	auto const border_color = d3d12::BorderColor(sampler.border_color());

	m_desc.Filter         = d3d12::FilterMode(sampler.min_filter(), sampler.mag_filter(), sampler.mip_filter());
	m_desc.AddressU       = d3d12::AddressMode(sampler.address_mode_u());
	m_desc.AddressV       = d3d12::AddressMode(sampler.address_mode_v());
	m_desc.AddressW       = d3d12::AddressMode(sampler.address_mode_w());
	m_desc.MipLODBias     = 0;
	m_desc.MaxAnisotropy  = 16;
	m_desc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	m_desc.BorderColor[0] = border_color[0];
	m_desc.BorderColor[1] = border_color[1];
	m_desc.BorderColor[2] = border_color[2];
	m_desc.BorderColor[3] = border_color[3];
	m_desc.MinLOD         = sampler.enable_mipmap() ? sampler.min_lod() : 0.0f;
	m_desc.MaxLOD         = sampler.enable_mipmap() ? sampler.max_lod() : 0.0f;
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
