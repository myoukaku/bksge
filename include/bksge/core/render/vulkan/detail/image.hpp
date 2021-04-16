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
#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/math/color4.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

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
		bksge::uint32_t mipmap_count,
		::VkSampleCountFlagBits num_samples,
		::VkImageTiling tiling,
		::VkImageUsageFlags usage,
		::VkImageLayout initial_layout,
		::VkFlags requirements_mask);

	~Image();

	void* MapMemory(::VkDeviceSize size);

	void UnmapMemory(void);

	void ClearColor(
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkImageAspectFlags aspect_mask,
		bksge::Color4f const& color);

	void ClearDepthStencil(
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkImageAspectFlags aspect_mask,
		float depth,
		bksge::uint32_t stencil);

	::VkImageLayout TransitionLayout(
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkImageAspectFlags aspect_mask,
		::VkImageLayout new_layout);

	::VkFormat const&		format(void) const;

	::VkExtent2D const&		extent(void) const;

	bksge::uint32_t			mipmap_count(void) const;

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
	::VkExtent2D				m_extent;
	bksge::uint32_t				m_mipmap_count;
	::VkImageLayout				m_layout;
	vulkan::DeviceMemoryUniquePtr	m_device_memory;
};

void TransitionImageLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImage image,
	::VkImageAspectFlags aspect_mask,
	bksge::uint32_t mipmap_count,
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
