/**
 *	@file	address_mode_inl.hpp
 *
 *	@brief	AddressMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_ADDRESS_MODE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_ADDRESS_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/address_mode.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/address_mode.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkSamplerAddressMode
ToVulkanAddressMode(bksge::AddressMode address_mode)
{
	switch (address_mode)
	{
	case bksge::AddressMode::kRepeat: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
	case bksge::AddressMode::kClamp:  return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	case bksge::AddressMode::kBorder: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	}
	return VK_SAMPLER_ADDRESS_MODE_REPEAT;
}

}	// namespace detail

BKSGE_INLINE
AddressMode::AddressMode(bksge::AddressMode address_mode)
	: m_address_mode(detail::ToVulkanAddressMode(address_mode))
{}

BKSGE_INLINE
AddressMode::operator ::VkSamplerAddressMode() const
{
	return m_address_mode;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_ADDRESS_MODE_INL_HPP
