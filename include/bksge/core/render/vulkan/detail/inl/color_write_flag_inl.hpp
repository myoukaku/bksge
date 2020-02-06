/**
 *	@file	color_write_flag_inl.hpp
 *
 *	@brief	ColorWriteFlag の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/color_write_flag.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/color_write_flag.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkColorComponentFlags
ToVulkanColorWriteFlag(bksge::ColorWriteFlag color_write_flag)
{
	::VkColorComponentFlags result = 0;

	if ((color_write_flag & bksge::ColorWriteFlag::kRed) != bksge::ColorWriteFlag::kNone)
	{
		result |= VK_COLOR_COMPONENT_R_BIT;
	}
	if ((color_write_flag & bksge::ColorWriteFlag::kGreen) != bksge::ColorWriteFlag::kNone)
	{
		result |= VK_COLOR_COMPONENT_G_BIT;
	}
	if ((color_write_flag & bksge::ColorWriteFlag::kBlue) != bksge::ColorWriteFlag::kNone)
	{
		result |= VK_COLOR_COMPONENT_B_BIT;
	}
	if ((color_write_flag & bksge::ColorWriteFlag::kAlpha) != bksge::ColorWriteFlag::kNone)
	{
		result |= VK_COLOR_COMPONENT_A_BIT;
	}

	return result;
}

}	// namespace detail

BKSGE_INLINE
ColorWriteFlag::ColorWriteFlag(bksge::ColorWriteFlag color_write_flag)
	: m_color_write_flag(detail::ToVulkanColorWriteFlag(color_write_flag))
{}

BKSGE_INLINE
ColorWriteFlag::operator ::VkColorComponentFlags() const
{
	return m_color_write_flag;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP
