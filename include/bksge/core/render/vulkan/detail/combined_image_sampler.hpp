/**
 *	@file	combined_image_sampler.hpp
 *
 *	@brief	CombinedImageSampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_COMBINED_IMAGE_SAMPLER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_COMBINED_IMAGE_SAMPLER_HPP

#include <bksge/core/render/vulkan/detail/fwd/combined_image_sampler_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/sampled_texture_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CombinedImageSampler
{
public:
	explicit CombinedImageSampler(
		vulkan::ResourcePool* resource_pool,
		vulkan::CommandPoolSharedPtr const& command_pool,
		bksge::SampledTexture const& sampled_texture);

	~CombinedImageSampler();

	::VkDescriptorImageInfo	GetImageInfo(void) const;

private:
	// noncopyable
	CombinedImageSampler(CombinedImageSampler const&) = delete;
	CombinedImageSampler& operator=(CombinedImageSampler const&) = delete;

private:
	vulkan::SamplerSharedPtr		m_sampler;
	vulkan::TextureSharedPtr		m_texture;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/combined_image_sampler_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMBINED_IMAGE_SAMPLER_HPP
