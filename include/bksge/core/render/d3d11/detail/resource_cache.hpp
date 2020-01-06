/**
 *	@file	resource_cache.hpp
 *
 *	@brief	ResourceCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_RESOURCE_CACHE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_RESOURCE_CACHE_HPP

#include <bksge/core/render/d3d11/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>
#include <bksge/core/render/fwd/sampler_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class ResourceCache
{
public:
	explicit ResourceCache(void);

	~ResourceCache();

	HlslProgramShared GetD3D11HlslProgram(Device* device, bksge::Shader const& shader);
	GeometryShared    GetD3D11Geometry(Device* device, bksge::Geometry const& geometry);
	TextureShared     GetD3D11Texture(Device* device, bksge::Texture const& texture);
	SamplerShared     GetD3D11Sampler(Device* device, bksge::Sampler const& sampler);

private:
	HlslProgramMap	m_hlsl_program_map;
	GeometryMap		m_geometry_map;
	TextureMap		m_texture_map;
	SamplerMap		m_sampler_map;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/resource_cache_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_RESOURCE_CACHE_HPP
