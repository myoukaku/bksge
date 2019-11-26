/**
 *	@file	hlsl_sampler_inl.hpp
 *
 *	@brief	HlslSampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_SAMPLER_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_SAMPLER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/hlsl_sampler.hpp>
#include <bksge/render/d3d12/detail/resource_cache.hpp>
#include <bksge/render/d3d12/detail/descriptor_heaps.hpp>
#include <bksge/render/d3d12/detail/sampler.hpp>
#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/render/detail/shader_parameter.hpp>
#include <bksge/render/sampler.hpp>
#include <string>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
HlslSampler::HlslSampler(::D3D12_SHADER_INPUT_BIND_DESC const& bind_desc)
	: m_name(bind_desc.Name)
{
}

BKSGE_INLINE void
HlslSampler::UpdateParameters(
	DescriptorHeaps* descriptor_heaps,
	ResourceCache* resource_cache,
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	auto param = shader_parameter_map[m_name];
	if (!param)
	{
		return;
	}

	if (!param->data())
	{
		return;
	}

	if (param->class_id() != ShaderParameter<bksge::Sampler>::StaticClassId())
	{
		return;
	}

	auto sampler = *static_cast<bksge::Sampler const*>(param->data());

	auto d3d12_sampler = resource_cache->GetD3D12Sampler(sampler);
	d3d12_sampler->CreateView(
		descriptor_heaps->AssignCpuDescriptorHandle(
			D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER));
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_SAMPLER_INL_HPP
