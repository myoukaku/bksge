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
#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
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
		::VkImage image,
		::VkFormat format,
		vulkan::Extent2D const& extent,
		bksge::uint32_t mipmap_count);

	explicit Image(
		vulkan::DeviceSharedPtr const& device,
		::VkFormat format,
		vulkan::Extent2D const& extent,
		bksge::uint32_t mipmap_count,
		::VkSampleCountFlagBits num_samples,
		::VkImageUsageFlags usage);

	~Image();

	void* MapMemory(::VkDeviceSize size);

	void UnmapMemory(void);

	void ClearColor(
		vulkan::CommandBuffer* command_buffer,
		::VkImageAspectFlags aspect_mask,
		bksge::Color4f const& color);

	void ClearDepthStencil(
		vulkan::CommandBuffer* command_buffer,
		::VkImageAspectFlags aspect_mask,
		float depth,
		bksge::uint32_t stencil);

	::VkImageLayout TransitionLayout(
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkImageLayout new_layout);

	::VkImageLayout TransitionLayout(
		vulkan::CommandBuffer* command_buffer,
		::VkImageLayout new_layout);

public:
	::VkImageAspectFlags aspect_mask(void) const;

public:
	::VkFormat const& format(void) const;

public:
	vulkan::Extent2D const& extent(void) const;

public:
	bksge::uint32_t mipmap_count(void) const;

public:
	::VkImageLayout layout(void) const;

public:
	::VkImage image(void) const;

	::VkImageView image_view(void) const;

private:
	// noncopyable
	Image(Image const&) = delete;
	Image& operator=(Image const&) = delete;

private:
	::VkImage						m_image = VK_NULL_HANDLE;
	::VkImageView					m_image_view = VK_NULL_HANDLE;
	vulkan::DeviceMemoryUniquePtr	m_device_memory;
	::VkImageAspectFlags			m_aspect_mask;
	::VkFormat						m_format;
	vulkan::Extent2D				m_extent;
	bksge::uint32_t					m_mipmap_count;
	::VkImageLayout					m_layout;
	vulkan::DeviceSharedPtr			m_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/image_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_IMAGE_HPP
