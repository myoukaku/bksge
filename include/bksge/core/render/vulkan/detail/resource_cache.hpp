/**
 *	@file	resource_cache.hpp
 *
 *	@brief	ResourceCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_RESOURCE_CACHE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_RESOURCE_CACHE_HPP

#include <bksge/core/render/vulkan/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{
#if 0
class ResourceCache
{
public:
	explicit ResourceCache(void);

	~ResourceCache();

	GeometryShared GetVulkanGeometry(DeviceSharedPtr const&, bksge::Geometry const& geometry);

private:
	GeometryMap						m_geometry_map;
};
#endif
}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/resource_cache_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_RESOURCE_CACHE_HPP
