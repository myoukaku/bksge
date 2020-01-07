/**
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
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
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
		::VkImageUsageFlags usage);

	~Image();

	operator ::VkImage() const;

	::VkFormat const&		format(void) const;

	::VkMemoryRequirements	requirements(void) const;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkImage					m_image;
	::VkFormat					m_format;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/image_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_HPP
