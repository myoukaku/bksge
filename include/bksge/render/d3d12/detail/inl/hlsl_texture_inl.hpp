/**
 *	@file	hlsl_texture_inl.hpp
 *
 *	@brief	HlslTexture クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_TEXTURE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_TEXTURE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/hlsl_texture.hpp>
#include <bksge/render/d3d12/detail/resource_cache.hpp>
#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/render/detail/shader_parameter.hpp>
#include <bksge/render/texture.hpp>
#include <string>

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
HlslTexture::SetDescriptorHandle(::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	m_dest = dest;
}

BKSGE_INLINE void
HlslTexture::UpdateParameters(
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

	if (param->class_id() != ShaderParameter<bksge::Texture>::StaticClassId())
	{
		return;
	}

	auto texture = *static_cast<bksge::Texture const*>(param->data());

	auto d3d12_texture = resource_cache->GetD3D12Texture(texture, m_dest);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_TEXTURE_INL_HPP
