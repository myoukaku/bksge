﻿/**
 *	@file	image.hpp
 *
 *	@brief	Image クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_HPP

#include <bksge/core/render/vulkan/detail/fwd/image_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Image
{
public:
	explicit Image(
		vulkan::DeviceSharedPtr const& device,
		::VkFormat format,
		::VkExtent2D const& extent,
		::VkSampleCountFlagBits num_samples,
		::VkImageTiling tiling,
		::VkImageUsageFlags usage,
		::VkImageLayout initial_layout);

	~Image();

	void TransitionLayout(
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkImageAspectFlags aspect_mask,
		::VkImageLayout old_layout,
		::VkImageLayout new_layout);

	::VkFormat const&		format(void) const;

	::VkMemoryRequirements	requirements(void) const;

	operator ::VkImage() const;

private:
	// noncopyable
	Image(Image const&) = delete;
	Image& operator=(Image const&) = delete;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkImage					m_image;
	::VkFormat					m_format;
};

void TransitionImageLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImage image,
	::VkImageAspectFlags aspect_mask,
	::VkImageLayout old_layout,
	::VkImageLayout new_layout);

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/image_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_HPP
