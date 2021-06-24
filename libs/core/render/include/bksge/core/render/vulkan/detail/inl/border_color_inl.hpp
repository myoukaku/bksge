/**
 *	@file	border_color_inl.hpp
 *
 *	@brief	BorderColor の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BORDER_COLOR_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BORDER_COLOR_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/border_color.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/border_color.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkBorderColor
ToVulkanBorderColor(bksge::BorderColor border_color)
{
	switch (border_color)
	{
	case bksge::BorderColor::kTransparentBlack: return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
	case bksge::BorderColor::kOpaqueBlack:      return VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
	case bksge::BorderColor::kOpaqueWhite:      return VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	}
	return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
}

}	// namespace detail

BKSGE_INLINE
BorderColor::BorderColor(bksge::BorderColor border_color)
	: m_border_color(detail::ToVulkanBorderColor(border_color))
{}

BKSGE_INLINE
BorderColor::operator ::VkBorderColor() const
{
	return m_border_color;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BORDER_COLOR_INL_HPP
