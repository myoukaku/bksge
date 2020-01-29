/**
 *	@file	wrap_mode_inl.hpp
 *
 *	@brief	WrapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_WRAP_MODE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_WRAP_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/wrap_mode.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/wrap_mode.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkSamplerAddressMode
ToVulkanWrapMode(bksge::WrapMode wrap_mode)
{
	switch (wrap_mode)
	{
	case bksge::WrapMode::kRepeat: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
	case bksge::WrapMode::kClamp:  return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	case bksge::WrapMode::kBorder: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	}
	return VK_SAMPLER_ADDRESS_MODE_REPEAT;
}

}	// namespace detail

BKSGE_INLINE
WrapMode::WrapMode(bksge::WrapMode wrap_mode)
	: m_wrap_mode(detail::ToVulkanWrapMode(wrap_mode))
{}

BKSGE_INLINE
WrapMode::operator ::VkSamplerAddressMode() const
{
	return m_wrap_mode;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_WRAP_MODE_INL_HPP
