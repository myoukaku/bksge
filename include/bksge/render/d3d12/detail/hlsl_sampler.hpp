/**
 *	@file	hlsl_sampler.hpp
 *
 *	@brief	HlslSampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_HLSL_SAMPLER_HPP
#define BKSGE_RENDER_D3D12_DETAIL_HLSL_SAMPLER_HPP

#include <bksge/render/d3d12/detail/fwd/hlsl_sampler_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/d3d12shader.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
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

	void SetDescriptorHandle(::D3D12_CPU_DESCRIPTOR_HANDLE dest);

	void UpdateParameters(
		ResourceCache* resource_cache,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	std::string		m_name;
	::D3D12_CPU_DESCRIPTOR_HANDLE m_dest;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/hlsl_sampler_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_HLSL_SAMPLER_HPP
