﻿/**
 *	@file	hlsl_texture_inl.hpp
 *
 *	@brief	HlslTexture クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/hlsl_texture.hpp>
#include <bksge/core/render/d3d12/detail/resource_pool.hpp>
#include <bksge/core/render/d3d12/detail/descriptor_heaps.hpp>
#include <bksge/core/render/d3d12/detail/texture.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/render/texture.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
HlslTexture::HlslTexture(::D3D12_SHADER_INPUT_BIND_DESC const& bind_desc)
	: m_name(bind_desc.Name)
{
}

BKSGE_INLINE void
HlslTexture::UpdateParameters(
	Device* device,
	DescriptorHeaps* descriptor_heaps,
	ResourcePool* resource_pool,
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

	if (param->class_id() != ShaderParameter<bksge::Texture>::StaticClassId())
	{
		return;
	}

	auto texture = *static_cast<bksge::Texture const*>(param->data());

	auto d3d12_texture = resource_pool->GetD3D12Texture(device, texture);
	d3d12_texture->CreateView(
		device,
		descriptor_heaps->AssignCpuDescriptorHandle(
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_HLSL_TEXTURE_INL_HPP
