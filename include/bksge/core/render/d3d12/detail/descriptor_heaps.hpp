/**
 *	@file	descriptor_heaps.hpp
 *
 *	@brief	DescriptorHeaps クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAPS_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAPS_HPP

#include <bksge/core/render/d3d12/detail/fwd/descriptor_heaps_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/descriptor_heap_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/root_parameters_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class DescriptorHeaps
{
public:
	explicit DescriptorHeaps(
		Device* device,
		::UINT num_cbv_srv_uav,
		::UINT num_samplers,
		::UINT num_render_target_views,
		::UINT num_depth_stencil_views);

	~DescriptorHeaps();

	void SetEnable(CommandList* command_list);

	void SetDescriptorTables(
		CommandList* command_list,
		RootParameters const& root_parameters);

	::D3D12_GPU_DESCRIPTOR_HANDLE
	AssignGpuDescriptorHandle(::D3D12_DESCRIPTOR_HEAP_TYPE type);

	::D3D12_CPU_DESCRIPTOR_HANDLE
	AssignCpuDescriptorHandle(::D3D12_DESCRIPTOR_HEAP_TYPE type);

	void BeginFrame(void);

private:
	// noncopyable
	DescriptorHeaps(DescriptorHeaps const&) = delete;
	DescriptorHeaps& operator=(DescriptorHeaps const&) = delete;

private:
	std::unique_ptr<DescriptorHeap> m_descriptor_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/descriptor_heaps_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAPS_HPP
