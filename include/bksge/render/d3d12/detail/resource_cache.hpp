/**
 *	@file	resource_cache.hpp
 *
 *	@brief	ResourceCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_RESOURCE_CACHE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_RESOURCE_CACHE_HPP

#include <bksge/render/d3d12/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/texture_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/sampler_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_queue_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/fence_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>
#include <bksge/render/fwd/sampler_fwd.hpp>
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

	TextureShared GetD3D12Texture(
		bksge::Texture const& texture);

	SamplerShared GetD3D12Sampler(
		bksge::Sampler const& sampler);

private:
	Device*							m_device;	// TODO 生ポインタを保存しない
	std::unique_ptr<CommandQueue>	m_command_queue;
	std::unique_ptr<CommandList>	m_command_list;
	std::unique_ptr<Fence>			m_fence;
	ConstantBufferShared			m_constant_buffer;
	TextureMap						m_texture_map;
	SamplerMap						m_sampler_map;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/resource_cache_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_RESOURCE_CACHE_HPP
