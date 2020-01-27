/**
 *	@file	cull_mode_inl.hpp
 *
 *	@brief	CullMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_CULL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_CULL_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/cull_mode.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/cull_mode.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkCullModeFlags
ToVulkanCullMode(bksge::CullMode cull_mode)
{
	switch (cull_mode)
	{
	case bksge::CullMode::kNone:  return VK_CULL_MODE_NONE;
	case bksge::CullMode::kFront: return VK_CULL_MODE_FRONT_BIT;
	case bksge::CullMode::kBack:  return VK_CULL_MODE_BACK_BIT;
	}
	return VK_CULL_MODE_NONE;
}

}	// namespace detail

BKSGE_INLINE
CullMode::CullMode(bksge::CullMode cull_mode)
	: m_cull_mode(detail::ToVulkanCullMode(cull_mode))
{}

BKSGE_INLINE
CullMode::operator ::VkCullModeFlags() const
{
	return m_cull_mode;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_CULL_MODE_INL_HPP
