/**
 *	@file	filter_mode_inl.hpp
 *
 *	@brief	FilterMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FILTER_MODE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FILTER_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/filter_mode.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/filter_mode.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkFilter
ToVulkanFilterMode(bksge::FilterMode filter_mode)
{
	switch (filter_mode)
	{
	case bksge::FilterMode::kNearest: return VK_FILTER_NEAREST;
	case bksge::FilterMode::kLinear:  return VK_FILTER_LINEAR;
	}
	return VK_FILTER_NEAREST;
}

}	// namespace detail

BKSGE_INLINE
FilterMode::FilterMode(bksge::FilterMode filter_mode)
	: m_filter_mode(detail::ToVulkanFilterMode(filter_mode))
{}

BKSGE_INLINE
FilterMode::operator ::VkFilter() const
{
	return m_filter_mode;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FILTER_MODE_INL_HPP
