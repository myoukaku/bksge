/**
 *	@file	constant_buffer_inl.hpp
 *
 *	@brief	ConstantBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/d3dcompiler.hpp>
#include <bksge/render/shader_parameter_map.hpp>
#include <bksge/cmath/round_up.hpp>

//#include <iostream>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
ConstantBuffer::ConstantBuffer(
	Device* device,
	::ID3D12ShaderReflectionConstantBuffer* constant_buffer)
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

	// Create resource.
	{
		::D3D12_HEAP_PROPERTIES prop;
		prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask     = 1;
		prop.VisibleNodeMask      = 1;

		::D3D12_RESOURCE_DESC desc;
		desc.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment        = 0;
		desc.Width            = m_size;
		desc.Height           = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels        = 1;
		desc.Format           = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc       = {1, 0};
		desc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags            = D3D12_RESOURCE_FLAG_NONE;

		m_resource = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr);
	}

	// Map the constant buffer. We don't unmap this until the app closes.
	// Keeping things mapped for the lifetime of the resource is okay.
	m_resource->Map(0, nullptr, reinterpret_cast<void**>(&m_buffer_data));

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
ConstantBuffer::~ConstantBuffer()
{
}

BKSGE_INLINE void
ConstantBuffer::CreateConstantBufferView(
	Device* device, ::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	::D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
	desc.BufferLocation = m_resource->GetGPUVirtualAddress();
	desc.SizeInBytes = m_size;
	device->CreateConstantBufferView(&desc, dest);
}

BKSGE_INLINE void
ConstantBuffer::UpdateParameters(
	bksge::ShaderParameterMap const& shader_parameter_map)
{
	for (auto&& variable : m_variables)
	{
		auto param = shader_parameter_map[variable.m_name];
		if (param)
		{
			auto src = param->data();
			std::memcpy(
				m_buffer_data + variable.m_start_offset,
				src,
				variable.m_size);
		}
	}
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_INL_HPP
