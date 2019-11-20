/**
 *	@file	descriptor_heap_inl.hpp
 *
 *	@brief	DescriptorHeap クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_DESCRIPTOR_HEAP_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_DESCRIPTOR_HEAP_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/descriptor_heap.hpp>
#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/hlsl_program.hpp>
#include <bksge/render/d3d12/detail/hlsl_texture.hpp>
#include <bksge/render/d3d12/detail/hlsl_sampler.hpp>
#include <bksge/render/d3d12/detail/root_parameters.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
DescriptorHeap::DescriptorHeap(
	Device* device,
	RootParameters const& root_parameters,
	ConstantBuffers const& constant_buffers,
	HlslTextures const& hlsl_textures,
	HlslSamplers const& hlsl_samplers)
{
	CreateCbvSrvUavDescriptorHeap(device, constant_buffers, hlsl_textures);
	CreateSamplerDescriptorHeap(device, hlsl_samplers);

	::D3D12_GPU_DESCRIPTOR_HANDLE cbv_srv_uav_handle = {};
	::D3D12_GPU_DESCRIPTOR_HANDLE sampler_handle = {};
	if (m_cbv_srv_uav_descriptor_heap)
	{
		cbv_srv_uav_handle = m_cbv_srv_uav_descriptor_heap->GetGPUDescriptorHandleForHeapStart();
	}
	if (m_sampler_descriptor_heap)
	{
		sampler_handle = m_sampler_descriptor_heap->GetGPUDescriptorHandleForHeapStart();
	}

	for (::UINT i = 0; i < root_parameters.GetSize(); ++i)
	{
		if (root_parameters.GetType(i) == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
		{
			switch (root_parameters.GetDescriptorRangeType(i))
			{
			case D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER:
				m_gpu_handles.push_back(sampler_handle);
				sampler_handle.ptr += m_sampler_descriptor_handle_incrementsize;
				break;
			case D3D12_DESCRIPTOR_RANGE_TYPE_SRV:
			case D3D12_DESCRIPTOR_RANGE_TYPE_UAV:
			case D3D12_DESCRIPTOR_RANGE_TYPE_CBV:
				m_gpu_handles.push_back(cbv_srv_uav_handle);
				cbv_srv_uav_handle.ptr += m_cbv_srv_uav_descriptor_handle_incrementsize;
				break;
			}
		}
		else
		{
			// TODO DescriptorTable 以外は未対応
		}
	}
}

BKSGE_INLINE void
DescriptorHeap::CreateCbvSrvUavDescriptorHeap(
	Device* device,
	ConstantBuffers const& constant_buffers,
	HlslTextures const& hlsl_textures)
{
	m_cbv_srv_uav_descriptor_handle_incrementsize =
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// Create descriptor heap.
	::D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.NumDescriptors = static_cast<::UINT>(constant_buffers.size() + hlsl_textures.size());
	desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	if (desc.NumDescriptors == 0)
	{
		return;
	}

	m_cbv_srv_uav_descriptor_heap = device->CreateDescriptorHeap(desc);

	::D3D12_CPU_DESCRIPTOR_HANDLE handle =
		m_cbv_srv_uav_descriptor_heap->GetCPUDescriptorHandleForHeapStart();

	// Create ConstantBufferView.
	for (auto&& constant_buffer : constant_buffers)
	{
		constant_buffer->CreateConstantBufferView(device, handle);
		handle.ptr += m_cbv_srv_uav_descriptor_handle_incrementsize;
	}

	// Create ShaderResourceView.
	for (auto&& hlsl_texture : hlsl_textures)
	{
		hlsl_texture->SetDescriptorHandle(handle);
		handle.ptr += m_cbv_srv_uav_descriptor_handle_incrementsize;
	}
}

BKSGE_INLINE void
DescriptorHeap::CreateSamplerDescriptorHeap(
	Device* device,
	HlslSamplers const& hlsl_samplers)
{
	m_sampler_descriptor_handle_incrementsize =
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

	// Create descriptor heap.
	::D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.NumDescriptors = static_cast<::UINT>(hlsl_samplers.size());
	desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
	desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	if (desc.NumDescriptors == 0)
	{
		return;
	}

	m_sampler_descriptor_heap = device->CreateDescriptorHeap(desc);

	::D3D12_CPU_DESCRIPTOR_HANDLE handle =
		m_sampler_descriptor_heap->GetCPUDescriptorHandleForHeapStart();

	for (auto&& hlsl_sampler : hlsl_samplers)
	{
		hlsl_sampler->SetDescriptorHandle(handle);
		handle.ptr += m_sampler_descriptor_handle_incrementsize;
	}
}

BKSGE_INLINE
DescriptorHeap::~DescriptorHeap()
{
}

BKSGE_INLINE void
DescriptorHeap::SetEnable(CommandList* command_list)
{
	std::vector<::ID3D12DescriptorHeap*> heaps;
	if (m_cbv_srv_uav_descriptor_heap)
	{
		heaps.push_back(m_cbv_srv_uav_descriptor_heap.Get());
	}
	if (m_sampler_descriptor_heap)
	{
		heaps.push_back(m_sampler_descriptor_heap.Get());
	}
	command_list->SetDescriptorHeaps(static_cast<::UINT>(heaps.size()), heaps.data());

	::UINT root_parameter_index = 0;
	for (auto gpu_handle : m_gpu_handles)
	{
		command_list->SetGraphicsRootDescriptorTable(root_parameter_index, gpu_handle);
		root_parameter_index++;
	}
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_DESCRIPTOR_HEAP_INL_HPP
