﻿/**
 *	@file	descriptor_heap.hpp
 *
 *	@brief	DescriptorHeap クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAP_HPP
#define BKSGE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAP_HPP

#include <bksge/render/d3d12/detail/fwd/descriptor_heap_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_texture_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_sampler_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/root_parameters_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class DescriptorHeap
{
public:
	using ConstantBuffers =
		std::vector<std::unique_ptr<ConstantBuffer>>;
	using HlslTextures =
		std::vector<std::unique_ptr<HlslTexture>>;
	using HlslSamplers =
		std::vector<std::unique_ptr<HlslSampler>>;

	explicit DescriptorHeap(
		Device* device,
		RootParameters const& root_parameters,
		ConstantBuffers const& constant_buffers,
		HlslTextures const& hlsl_textures,
		HlslSamplers const& hlsl_samplers);

	~DescriptorHeap();

	void SetEnable(CommandList* command_list);

private:
	void CreateCbvSrvUavDescriptorHeap(
		Device* device,
		ConstantBuffers const& constant_buffers,
		HlslTextures const& hlsl_textures);
	void CreateSamplerDescriptorHeap(
		Device* device,
		HlslSamplers const& hlsl_samplers);

private:
	ComPtr<::ID3D12DescriptorHeap>		m_cbv_srv_uav_descriptor_heap;
	::UINT								m_cbv_srv_uav_descriptor_handle_incrementsize;
	ComPtr<::ID3D12DescriptorHeap>		m_sampler_descriptor_heap;
	::UINT								m_sampler_descriptor_handle_incrementsize;
	std::vector<::D3D12_GPU_DESCRIPTOR_HANDLE> m_gpu_handles;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/descriptor_heap_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_DESCRIPTOR_HEAP_HPP
