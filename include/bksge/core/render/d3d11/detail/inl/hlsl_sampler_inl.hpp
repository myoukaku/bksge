/**
 *	@file	hlsl_sampler_inl.hpp
 *
 *	@brief	HlslSampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_SAMPLER_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_SAMPLER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/hlsl_sampler.hpp>
#include <bksge/core/render/d3d11/detail/hlsl_shader.hpp>
#include <bksge/core/render/d3d11/detail/device_context.hpp>
#include <bksge/core/render/d3d11/detail/resource_cache.hpp>
#include <bksge/core/render/d3d11/detail/sampler.hpp>
#include <bksge/core/render/d3d_common/d3d11shader.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/sampler.hpp>
#include <string>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
HlslSampler::HlslSampler(::D3D11_SHADER_INPUT_BIND_DESC const& desc)
	: m_name(desc.Name)
{
}

BKSGE_INLINE
HlslSampler::~HlslSampler()
{
}

BKSGE_INLINE void
HlslSampler::Load(
	ResourceCache* resource_cache,
	DeviceContext* device_context,
	bksge::ShaderParameterMap const& shader_parameter_map,
	HlslShaderBase* hlsl_shader,
	::UINT slot)
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

	auto d3d11_sampler =
		resource_cache->GetD3D11Sampler(sampler);

	hlsl_shader->VSetSamplers(
		device_context,
		slot,
		1,
		d3d11_sampler->state().GetAddressOf());
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_SAMPLER_INL_HPP
