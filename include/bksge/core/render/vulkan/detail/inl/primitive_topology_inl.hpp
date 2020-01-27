/**
 *	@file	primitive_topology_inl.hpp
 *
 *	@brief	PrimitiveTopology の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/primitive_topology.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/primitive.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkPrimitiveTopology
ToVulkanPrimitiveTopology(bksge::Primitive primitive_topology)
{
	switch (primitive_topology)
	{
	case bksge::Primitive::kPoints:    return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
	case bksge::Primitive::kLines:     return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	case bksge::Primitive::kTriangles: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	}
	// TODO エラー
	return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
}

}	// namespace detail

BKSGE_INLINE
PrimitiveTopology::PrimitiveTopology(bksge::Primitive primitive_topology)
	: m_primitive_topology(detail::ToVulkanPrimitiveTopology(primitive_topology))
{}

BKSGE_INLINE
PrimitiveTopology::operator VkPrimitiveTopology() const
{
	return m_primitive_topology;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
