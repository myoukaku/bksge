﻿/**
 *	@file	hlsl_texture_inl.hpp
 *
 *	@brief	HlslTexture クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/hlsl_texture.hpp>
#include <bksge/core/render/d3d11/detail/hlsl_shader.hpp>
#include <bksge/core/render/d3d11/detail/device_context.hpp>
#include <bksge/core/render/d3d11/detail/resource_pool.hpp>
#include <bksge/core/render/d3d11/detail/texture.hpp>
#include <bksge/core/render/d3d_common/d3d11shader.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/texture.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
HlslTexture::HlslTexture(::D3D11_SHADER_INPUT_BIND_DESC const& desc)
	: m_name(desc.Name)
{
}

BKSGE_INLINE
HlslTexture::~HlslTexture()
{
}

BKSGE_INLINE void
HlslTexture::Load(
	ResourcePool* resource_pool,
	Device* device,
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

	if (param->class_id() != ShaderParameter<bksge::Texture>::StaticClassId())
	{
		return;
	}

	auto texture = *static_cast<bksge::Texture const*>(param->data());

	auto d3d11_texture =
		resource_pool->GetD3D11Texture(device, texture);

	auto srv = d3d11_texture->shader_resource_view();

	hlsl_shader->VSetShaderResources(
		device_context,
		slot,
		1,
		&srv);
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_HLSL_TEXTURE_INL_HPP
