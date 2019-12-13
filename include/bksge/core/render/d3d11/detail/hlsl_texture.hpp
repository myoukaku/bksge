/**
 *	@file	hlsl_texture.hpp
 *
 *	@brief	HlslTexture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_TEXTURE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_TEXTURE_HPP

#include <bksge/core/render/d3d11/detail/fwd/hlsl_texture_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/resource_cache_fwd.hpp>
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
class HlslTexture
{
public:
	explicit HlslTexture(::D3D11_SHADER_INPUT_BIND_DESC const& desc);

	~HlslTexture();

	void Load(
		ResourceCache* resource_cache,
		DeviceContext* device_context,
		bksge::ShaderParameterMap const& shader_parameter_map,
		HlslShaderBase* hlsl_shader,
		::UINT slot);

private:
	std::string		m_name;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/hlsl_texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_TEXTURE_HPP
