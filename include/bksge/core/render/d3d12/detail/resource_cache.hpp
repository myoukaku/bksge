/**
 *	@file	resource_cache.hpp
 *
 *	@brief	ResourceCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_RESOURCE_CACHE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_RESOURCE_CACHE_HPP

#include <bksge/core/render/d3d12/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/pipeline_state_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/fence_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/primitive_topology_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>
#include <bksge/core/render/fwd/sampler_fwd.hpp>
#include <memory>
#include <vector>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace d3d12
{

class ResourceCache
{
public:
	explicit ResourceCache(Device* device);

	~ResourceCache();

	ConstantBufferShared GetD3D12ConstantBuffer();

	PipelineStateShared GetD3D12PipelineState(
		Device* device,
		bksge::Shader const& shader,
		bksge::RenderState const& render_state,
		bksge::PrimitiveTopology primitive_topology);

	HlslProgramShared GetD3D12HlslProgram(Device* device, bksge::Shader const& shader);

	GeometryShared GetD3D12Geometry(Device* device, bksge::Geometry const& geometry);

	TextureShared GetD3D12Texture(Device* device, bksge::Texture const& texture);

	SamplerShared GetD3D12Sampler(bksge::Sampler const& sampler);

private:
	std::unique_ptr<CommandQueue>	m_command_queue;
	std::unique_ptr<CommandList>	m_command_list;
	std::unique_ptr<Fence>			m_fence;
	ConstantBufferShared			m_constant_buffer;
	PipelineStateMap				m_pipeline_state;
	HlslProgramMap					m_hlsl_program_map;
	GeometryMap						m_geometry_map;
	TextureMap						m_texture_map;
	SamplerMap						m_sampler_map;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/resource_cache_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_RESOURCE_CACHE_HPP
