/**
 *	@file	mipmap_mode_inl.hpp
 *
 *	@brief	MipmapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_MIPMAP_MODE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_MIPMAP_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/mipmap_mode.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/mipmap_mode.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkSamplerMipmapMode
ToVulkanMipmapMode(bksge::MipmapMode mipmap_mode)
{
	switch (mipmap_mode)
	{
	case bksge::MipmapMode::kDisable: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
	case bksge::MipmapMode::kNearest: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
	case bksge::MipmapMode::kLinear:  return VK_SAMPLER_MIPMAP_MODE_LINEAR;
	}
	return VK_SAMPLER_MIPMAP_MODE_NEAREST;
}

}	// namespace detail

BKSGE_INLINE
MipmapMode::MipmapMode(bksge::MipmapMode mipmap_mode)
	: m_mipmap_mode(detail::ToVulkanMipmapMode(mipmap_mode))
{}

BKSGE_INLINE
MipmapMode::operator ::VkSamplerMipmapMode() const
{
	return m_mipmap_mode;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_MIPMAP_MODE_INL_HPP
