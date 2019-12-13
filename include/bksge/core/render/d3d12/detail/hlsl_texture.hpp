/**
 *	@file	hlsl_texture.hpp
 *
 *	@brief	HlslTexture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_TEXTURE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_TEXTURE_HPP

#include <bksge/core/render/d3d12/detail/fwd/hlsl_texture_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/resource_cache_fwd.hpp>
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

/**
 *	@brief
 */
class HlslTexture
{
public:
	explicit HlslTexture(::D3D12_SHADER_INPUT_BIND_DESC const& bind_desc);

	void UpdateParameters(
		Device* device,
		DescriptorHeaps* descriptor_heaps,
		ResourceCache* resource_cache,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	std::string		m_name;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/hlsl_texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_TEXTURE_HPP
