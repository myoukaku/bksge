﻿/**
 *	@file	hlsl_constant_buffer_inl.hpp
 *
 *	@brief	HlslConstantBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_CONSTANT_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_CONSTANT_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/hlsl_constant_buffer.hpp>
#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d12/detail/resource_cache.hpp>
#include <bksge/render/d3d12/detail/descriptor_heaps.hpp>
#include <bksge/render/d3d_common/d3d12shader.hpp>
#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/cmath/round_up.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
HlslConstantBuffer::HlslConstantBuffer(::ID3D12ShaderReflectionConstantBuffer* constant_buffer)
{
	::D3D12_SHADER_BUFFER_DESC shader_buffer_desc;
	constant_buffer->GetDesc(&shader_buffer_desc);

	m_name = shader_buffer_desc.Name;
	m_size = bksge::round_up(
		shader_buffer_desc.Size,
		D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);

	//std::cout
	//	<< shader_buffer_desc.Name << ", "
	//	<< shader_buffer_desc.Size << std::endl;

	for (::UINT i = 0; i < shader_buffer_desc.Variables; ++i)
	{
		auto variable = constant_buffer->GetVariableByIndex(i);
		::D3D12_SHADER_VARIABLE_DESC variable_desc;
		variable->GetDesc(&variable_desc);

		//std::cout << "    "
		//	<< variable_desc.Name << ", "
		//	<< variable_desc.StartOffset << ", "
		//	<< variable_desc.Size << std::endl;

		if (variable_desc.uFlags & D3D_SVF_USED)
		{
			Variable v;
			v.m_name         = variable_desc.Name;
			v.m_start_offset = variable_desc.StartOffset;
			v.m_size         = variable_desc.Size;
			m_variables.push_back(v);
		}
	}
}

BKSGE_INLINE
HlslConstantBuffer::~HlslConstantBuffer()
{
}

BKSGE_INLINE void
HlslConstantBuffer::UpdateParameters(
	DescriptorHeaps* descriptor_heaps,
	ResourceCache* resource_cache,
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	std::vector<std::uint8_t> buf(m_size);

	for (auto&& variable : m_variables)
	{
		auto param = shader_parameter_map[variable.m_name];
		if (param)
		{
			auto src = param->data();
			std::memcpy(
				buf.data() + variable.m_start_offset,
				src,
				variable.m_size);
		}
	}

	auto d3d12_constant_buffer = resource_cache->GetD3D12ConstantBuffer(buf);
	d3d12_constant_buffer->Update(buf);
	d3d12_constant_buffer->CreateView(
		descriptor_heaps->AssignCpuDescriptorHandle(
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_HLSL_CONSTANT_BUFFER_INL_HPP
