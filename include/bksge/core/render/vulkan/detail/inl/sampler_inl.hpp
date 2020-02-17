/**
 *	@file	sampler_inl.hpp
 *
 *	@brief	Sampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SAMPLER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SAMPLER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/sampler.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/filter_mode.hpp>
#include <bksge/core/render/vulkan/detail/mipmap_mode.hpp>
#include <bksge/core/render/vulkan/detail/address_mode.hpp>
#include <bksge/core/render/vulkan/detail/border_color.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/address_mode.hpp>
#include <bksge/core/render/sampler.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Sampler::Sampler(
	vulkan::DeviceSharedPtr const& device,
	bksge::Sampler const& sampler)
	: m_device(device)
{
	vk::SamplerCreateInfo info;
	info.magFilter               = vulkan::FilterMode(sampler.mag_filter());
	info.minFilter               = vulkan::FilterMode(sampler.min_filter());
	info.mipmapMode              = vulkan::MipmapMode(sampler.mip_filter());
	info.addressModeU            = vulkan::AddressMode(sampler.address_mode_u());
	info.addressModeV            = vulkan::AddressMode(sampler.address_mode_v());
	info.addressModeW            = vulkan::AddressMode(sampler.address_mode_w());
	info.mipLodBias              = 0;
	info.anisotropyEnable        = VK_FALSE;
	info.maxAnisotropy           = 1;
	info.compareEnable           = VK_FALSE;
	info.compareOp               = VK_COMPARE_OP_NEVER;
	info.minLod                  = sampler.enable_mipmap() ? sampler.min_lod() : 0.0f;
	info.maxLod                  = sampler.enable_mipmap() ? sampler.max_lod() : 0.0f;
	info.borderColor             = vulkan::BorderColor(sampler.border_color());
	info.unnormalizedCoordinates = VK_FALSE;

	vk::CreateSampler(*m_device, &info, nullptr, &m_sampler);
}

BKSGE_INLINE
Sampler::~Sampler()
{
	vk::DestroySampler(*m_device, m_sampler, nullptr);
}

BKSGE_INLINE
Sampler::operator ::VkSampler() const
{
	return m_sampler;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SAMPLER_INL_HPP
