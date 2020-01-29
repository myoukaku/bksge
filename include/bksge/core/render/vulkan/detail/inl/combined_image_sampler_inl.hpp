/**
 *	@file	combined_image_sampler_inl.hpp
 *
 *	@brief	CombinedImageSampler クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMBINED_IMAGE_SAMPLER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMBINED_IMAGE_SAMPLER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/combined_image_sampler.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/sampler.hpp>
#include <bksge/core/render/vulkan/detail/texture.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/sampler.hpp>
#include <bksge/fnd/memory/make_unique.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
CombinedImageSampler::CombinedImageSampler(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::Sampler const& sampler)
{
	m_sampler = bksge::make_unique<vulkan::Sampler>(device, sampler);
	m_texture = bksge::make_unique<vulkan::Texture>(device, command_pool, sampler.source());
}

BKSGE_INLINE
CombinedImageSampler::~CombinedImageSampler()
{
}

BKSGE_INLINE ::VkDescriptorImageInfo
CombinedImageSampler::GetImageInfo(void) const
{
	::VkDescriptorImageInfo info;
	info.sampler     = *m_sampler;
	info.imageView   = *(m_texture->GetImageView());
	info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	return info;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMBINED_IMAGE_SAMPLER_INL_HPP
