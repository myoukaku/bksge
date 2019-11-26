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
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
DescriptorHeap::DescriptorHeap(
	Device*							device,
	::D3D12_DESCRIPTOR_HEAP_TYPE	type,
	::UINT							num_descriptors,
	::D3D12_DESCRIPTOR_HEAP_FLAGS	flags)
	: m_descriptor_heap()
	, m_descriptor_handle_increment_size(0)
	, m_gpu_descriptor_handle_index(0)
	, m_cpu_descriptor_handle_index(0)
{
	if (num_descriptors == 0)
	{
		return;
	}

	::D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type           = type;
	desc.NumDescriptors = num_descriptors;
	desc.Flags          = flags;

	m_descriptor_heap = device->CreateDescriptorHeap(desc);
	m_descriptor_handle_increment_size = device->GetDescriptorHandleIncrementSize(type);
}

BKSGE_INLINE
DescriptorHeap::~DescriptorHeap()
{
}

BKSGE_INLINE ::ID3D12DescriptorHeap*
DescriptorHeap::Get(void) const
{
	if (!m_descriptor_heap)
	{
		return nullptr;
	}

	return m_descriptor_heap.Get();
}

BKSGE_INLINE ::D3D12_GPU_DESCRIPTOR_HANDLE
DescriptorHeap::AssignGpuDescriptorHandle(void)
{
	if (!m_descriptor_heap)
	{
		return {};
	}

	auto handle = m_descriptor_heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += m_gpu_descriptor_handle_index * m_descriptor_handle_increment_size;

	++m_gpu_descriptor_handle_index;
	if (m_gpu_descriptor_handle_index >= GetNumDescriptors())
	{
		m_gpu_descriptor_handle_index = 0;
	}

	return handle;
}

BKSGE_INLINE ::D3D12_CPU_DESCRIPTOR_HANDLE
DescriptorHeap::AssignCpuDescriptorHandle(void)
{
	if (!m_descriptor_heap)
	{
		return {};
	}

	auto handle = m_descriptor_heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += m_cpu_descriptor_handle_index * m_descriptor_handle_increment_size;

	++m_cpu_descriptor_handle_index;
	if (m_cpu_descriptor_handle_index >= GetNumDescriptors())
	{
		m_cpu_descriptor_handle_index = 0;
	}

	return handle;
}

BKSGE_INLINE ::UINT
DescriptorHeap::GetNumDescriptors(void) const
{
	if (!m_descriptor_heap)
	{
		return 0;
	}

	auto const desc = m_descriptor_heap->GetDesc();
	return desc.NumDescriptors;
}

BKSGE_INLINE void
DescriptorHeap::BeginFrame(void)
{
	m_gpu_descriptor_handle_index = 0;
	m_cpu_descriptor_handle_index = 0;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_DESCRIPTOR_HEAP_INL_HPP
