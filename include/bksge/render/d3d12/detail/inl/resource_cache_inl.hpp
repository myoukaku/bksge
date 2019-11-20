/**
 *	@file	resource_cache_inl.hpp
 *
 *	@brief	ResourceCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_RESOURCE_CACHE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_RESOURCE_CACHE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/resource_cache.hpp>
#include <bksge/render/d3d12/detail/texture.hpp>
#include <bksge/render/d3d12/detail/sampler.hpp>
#include <bksge/render/d3d12/detail/command_queue.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/fence.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/render/sampler.hpp>
#include <bksge/utility/forward.hpp>
#include <bksge/memory/make_unique.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

template <typename Ret, typename Map, typename Id, typename... Args>
inline typename Map::mapped_type
GetOrCreate(Map& map, Id const& id, Args... args)
{
	{
		auto const& it = map.find(id);

		if (it != map.end())
		{
			return it->second;
		}
	}

	auto p = std::make_shared<Ret>(bksge::forward<Args>(args)...);
	map[id] = p;
	return p;
}

}	// namespace detail

BKSGE_INLINE
ResourceCache::ResourceCache(Device* device)
	: m_device(device)
{
	m_command_queue = bksge::make_unique<CommandQueue>(m_device);
	m_command_list  = bksge::make_unique<CommandList>(m_device);
	m_fence         = bksge::make_unique<Fence>(m_device);
	m_command_list->Close();
}

BKSGE_INLINE
ResourceCache::~ResourceCache()
{
}

BKSGE_INLINE TextureShared
ResourceCache::GetD3D12Texture(
	bksge::Texture const& texture,
	::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	return detail::GetOrCreate<Texture>(
		m_texture_map,
		texture.id(),
		m_device,
		m_command_list.get(),
		m_command_queue.get(),
		m_fence.get(),
		texture,
		dest);
}

BKSGE_INLINE SamplerShared
ResourceCache::GetD3D12Sampler(
	bksge::Sampler const& sampler,
	::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	return detail::GetOrCreate<Sampler>(
		m_sampler_map,
		sampler.id(),
		m_device,
		sampler,
		dest);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_RESOURCE_CACHE_INL_HPP
