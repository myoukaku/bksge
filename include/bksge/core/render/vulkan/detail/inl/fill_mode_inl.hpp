/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	FillMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FILL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FILL_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/fill_mode.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/fill_mode.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkPolygonMode
ToVulkanFillMode(bksge::FillMode fill_mode)
{
	switch (fill_mode)
	{
	case bksge::FillMode::kSolid:     return VK_POLYGON_MODE_FILL;
	case bksge::FillMode::kWireframe: return VK_POLYGON_MODE_LINE;
	}
	return VK_POLYGON_MODE_FILL;
}

}	// namespace detail

BKSGE_INLINE
FillMode::FillMode(bksge::FillMode fill_mode)
	: m_fill_mode(detail::ToVulkanFillMode(fill_mode))
{}

BKSGE_INLINE
FillMode::operator ::VkPolygonMode() const
{
	return m_fill_mode;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FILL_MODE_INL_HPP
