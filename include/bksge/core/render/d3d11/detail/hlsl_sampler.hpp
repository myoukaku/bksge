/**
 *	@file	hlsl_sampler.hpp
 *
 *	@brief	HlslSampler の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_SAMPLER_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_SAMPLER_HPP

#include <bksge/core/render/d3d11/detail/fwd/hlsl_sampler_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/d3d11shader.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <string>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class HlslSampler
{
public:
	explicit HlslSampler(::D3D11_SHADER_INPUT_BIND_DESC const& desc);

	~HlslSampler();

	void Load(
		ResourcePool* resource_pool,
		Device* device,
		DeviceContext* device_context,
		bksge::ShaderParameterMap const& shader_parameter_map,
		HlslShaderBase* hlsl_shader,
		::UINT slot);

private:
	// noncopyable
	HlslSampler(HlslSampler const&) = delete;
	HlslSampler& operator=(HlslSampler const&) = delete;

private:
	std::string		m_name;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/hlsl_sampler_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_SAMPLER_HPP
