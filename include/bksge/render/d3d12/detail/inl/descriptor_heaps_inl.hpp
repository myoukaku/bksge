/**
 *	@file	descriptor_heaps_inl.hpp
 *
 *	@brief	DescriptorHeaps クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_DESCRIPTOR_HEAPS_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_DESCRIPTOR_HEAPS_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/descriptor_heaps.hpp>
#include <bksge/render/d3d12/detail/descriptor_heap.hpp>
//#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/root_parameters.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/memory/make_unique.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
DescriptorHeaps::DescriptorHeaps(
	Device* device,
	::UINT num_cbv_srv_uav,
	::UINT num_samplers,
	::UINT num_render_target_views,
	::UINT num_depth_stencil_views)
{
	m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV] =
		bksge::make_unique<DescriptorHeap>(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			num_cbv_srv_uav,
			D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER] =
		bksge::make_unique<DescriptorHeap>(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
			num_samplers,
			D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_RTV] =
		bksge::make_unique<DescriptorHeap>(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			num_render_target_views,
			D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

	m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_DSV] =
		bksge::make_unique<DescriptorHeap>(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
			num_depth_stencil_views,
			D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
}

BKSGE_INLINE
DescriptorHeaps::~DescriptorHeaps()
{
}

BKSGE_INLINE void
DescriptorHeaps::SetEnable(CommandList* command_list)
{
	std::vector<::ID3D12DescriptorHeap*> heaps;
	for (auto&& descriptor_heap : m_descriptor_heaps)
	{
		if (descriptor_heap->Get())
		{
			heaps.push_back(descriptor_heap->Get());
		}
	}

	command_list->SetDescriptorHeaps(static_cast<::UINT>(heaps.size()), heaps.data());
}

namespace detail
{

inline ::D3D12_DESCRIPTOR_HEAP_TYPE
DescriptorRangeType_To_DescriptorHeapType(::D3D12_DESCRIPTOR_RANGE_TYPE type)
{
	switch (type)
	{
	case D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER:
		return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
	case D3D12_DESCRIPTOR_RANGE_TYPE_SRV:
	case D3D12_DESCRIPTOR_RANGE_TYPE_UAV:
	case D3D12_DESCRIPTOR_RANGE_TYPE_CBV:
		return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	}

	return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
}

}	// namespace detail

BKSGE_INLINE void
DescriptorHeaps::SetDescriptorTables(
	CommandList* command_list,
	RootParameters const& root_parameters)
{
	for (::UINT i = 0; i < root_parameters.GetSize(); ++i)
	{
		if (root_parameters.GetType(i) == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
		{
			const auto heap_type = detail::DescriptorRangeType_To_DescriptorHeapType(
				root_parameters.GetDescriptorRangeType(i));
			command_list->SetGraphicsRootDescriptorTable(
				i, AssignGpuDescriptorHandle(heap_type));
		}
		else
		{
			// TODO DescriptorTable 以外は未対応
		}
	}
}

BKSGE_INLINE ::D3D12_GPU_DESCRIPTOR_HANDLE
DescriptorHeaps::AssignGpuDescriptorHandle(::D3D12_DESCRIPTOR_HEAP_TYPE type)
{
	return m_descriptor_heaps[type]->AssignGpuDescriptorHandle();
}

BKSGE_INLINE ::D3D12_CPU_DESCRIPTOR_HANDLE
DescriptorHeaps::AssignCpuDescriptorHandle(::D3D12_DESCRIPTOR_HEAP_TYPE type)
{
	return m_descriptor_heaps[type]->AssignCpuDescriptorHandle();
}

BKSGE_INLINE void
DescriptorHeaps::BeginFrame(void)
{
	for (auto&& descriptor_heap : m_descriptor_heaps)
	{
		descriptor_heap->BeginFrame();
	}
}

#if 0
BKSGE_INLINE
DescriptorHeap::DescriptorHeap(
	Device* device,
	RootParameters const& root_parameters,
	HlslConstantBuffers const& hlsl_constant_buffers,
	HlslTextures const& hlsl_textures,
	HlslSamplers const& hlsl_samplers)
{
	CreateCbvSrvUavDescriptorHeap(device, hlsl_constant_buffers, hlsl_textures);
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
	HlslConstantBuffers const& hlsl_constant_buffers,
	HlslTextures const& hlsl_textures)
{
	m_cbv_srv_uav_descriptor_handle_incrementsize =
		device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// Create descriptor heap.
	::D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.NumDescriptors = static_cast<::UINT>(hlsl_constant_buffers.size() + hlsl_textures.size());
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
	for (auto&& hlsl_constant_buffer : hlsl_constant_buffers)
	{
//		hlsl_constant_buffer->CreateConstantBufferView(device, handle);
		hlsl_constant_buffer->SetDescriptorHandle(handle);
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
#endif

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_DESCRIPTOR_HEAPS_INL_HPP
