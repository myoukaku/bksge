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
#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d12/detail/texture.hpp>
#include <bksge/render/d3d12/detail/sampler.hpp>
#include <bksge/render/d3d12/detail/command_queue.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/fence.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/render/sampler.hpp>
#include <bksge/utility/forward.hpp>
#include <bksge/memory/make_unique.hpp>
#include <bksge/functional/hash_combine.hpp>
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
	, m_constant_buffer_index(0)
{
	m_command_queue = bksge::make_unique<CommandQueue>(m_device);
	m_command_list  = bksge::make_unique<CommandList>(m_device);
	m_fence         = bksge::make_unique<Fence>(m_device);
	m_command_list->Close();

	for (int i = 0; i < 1000; ++i)
	{
		m_constant_buffers.push_back(std::make_shared<ConstantBuffer>(device, 256));
	}
}

BKSGE_INLINE
ResourceCache::~ResourceCache()
{
}

BKSGE_INLINE ConstantBufferShared
ResourceCache::GetD3D12ConstantBuffer(
	std::vector<std::uint8_t> const& buf)
{
#if 0
	std::size_t id = 0;
	for (auto x : buf)
	{
		id = bksge::hash_combine(id, x);
	}

	return detail::GetOrCreate<ConstantBuffer>(
		m_constant_buffer_map,
		id,
		m_device,
		(::UINT)buf.size());
#else
	//auto p = std::make_shared<ConstantBuffer>(m_device, (::UINT)buf.size());
	//m_constant_buffers.push_back(p);
	//return p;

	if (buf.size() != 256)
	{
		return {};
	}

	auto p = m_constant_buffers[m_constant_buffer_index];

	++m_constant_buffer_index;
	if (m_constant_buffer_index >= m_constant_buffers.size())
	{
		m_constant_buffer_index = 0;
	}

	return p;
#endif
}

BKSGE_INLINE TextureShared
ResourceCache::GetD3D12Texture(
	bksge::Texture const& texture)
{
	return detail::GetOrCreate<Texture>(
		m_texture_map,
		texture.id(),
		m_device,
		m_command_list.get(),
		m_command_queue.get(),
		m_fence.get(),
		texture);
}

BKSGE_INLINE SamplerShared
ResourceCache::GetD3D12Sampler(
	bksge::Sampler const& sampler)
{
	return detail::GetOrCreate<Sampler>(
		m_sampler_map,
		sampler.id(),
		m_device,
		sampler);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_RESOURCE_CACHE_INL_HPP
