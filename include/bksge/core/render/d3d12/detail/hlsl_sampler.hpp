/**
 *	@file	hlsl_sampler.hpp
 *
 *	@brief	HlslSampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_SAMPLER_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_SAMPLER_HPP

#include <bksge/core/render/d3d12/detail/fwd/hlsl_sampler_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/descriptor_heaps_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/d3d12shader.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <string>

namespace bksge
{

namespace render
{

namespace d3d12
{

class HlslSampler
{
public:
	explicit HlslSampler(::D3D12_SHADER_INPUT_BIND_DESC const& bind_desc);

	void UpdateParameters(
		Device* device,
		DescriptorHeaps* descriptor_heaps,
		ResourcePool* resource_pool,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	// noncopyable
	HlslSampler(HlslSampler const&) = delete;
	HlslSampler& operator=(HlslSampler const&) = delete;

private:
	std::string		m_name;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/hlsl_sampler_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_SAMPLER_HPP
