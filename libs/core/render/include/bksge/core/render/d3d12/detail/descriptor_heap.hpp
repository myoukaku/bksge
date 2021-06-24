/**
 *	@file	descriptor_heap.hpp
 *
 *	@brief	DescriptorHeap クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAP_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAP_HPP

#include <bksge/core/render/d3d12/detail/fwd/descriptor_heap_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class DescriptorHeap
{
public:
	explicit DescriptorHeap(
		Device*							device,
		::D3D12_DESCRIPTOR_HEAP_TYPE	type,
		::UINT							num_descriptors,
		::D3D12_DESCRIPTOR_HEAP_FLAGS	flags);

	~DescriptorHeap();

	::ID3D12DescriptorHeap* Get(void) const;

	::D3D12_GPU_DESCRIPTOR_HANDLE AssignGpuDescriptorHandle(void);

	::D3D12_CPU_DESCRIPTOR_HANDLE AssignCpuDescriptorHandle(void);

	void BeginFrame(void);

private:
	::UINT GetNumDescriptors(void) const;

private:
	// noncopyable
	DescriptorHeap(DescriptorHeap const&) = delete;
	DescriptorHeap& operator=(DescriptorHeap const&) = delete;

private:
	ComPtr<::ID3D12DescriptorHeap>	m_descriptor_heap;
	::UINT							m_descriptor_handle_increment_size;
	::UINT							m_gpu_descriptor_handle_index;
	::UINT							m_cpu_descriptor_handle_index;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/descriptor_heap_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAP_HPP
