/**
 *	@file	resource_cache_inl.hpp
 *
 *	@brief	ResourceCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_CACHE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_CACHE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/resource_cache.hpp>
#include <bksge/core/render/vulkan/detail/geometry.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <memory>	// make_shared

namespace bksge
{

namespace render
{

namespace vulkan
{

#if 0
namespace detail
{

template <typename Ret, typename Map, typename Id, typename... Args>
inline typename Map::mapped_type
GetOrCreate(Map& map, Id const& id, Args&&... args)
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
ResourceCache::ResourceCache(void)
{
}

BKSGE_INLINE
ResourceCache::~ResourceCache()
{
}

BKSGE_INLINE GeometryShared
ResourceCache::GetVulkanGeometry(DeviceSharedPtr const& device, bksge::Geometry const& geometry)
{
	return detail::GetOrCreate<Geometry>(
		m_geometry_map, geometry.id(), device, geometry);
}
#endif

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RESOURCE_CACHE_INL_HPP
