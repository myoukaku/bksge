﻿/**
 *	@file	texture_inl.hpp
 *
 *	@brief	Texture クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/texture.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/texture_format.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cstring/memcpy.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline void
CopyBufferToImage(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkBuffer buffer,
	::VkImage image,
	bksge::TextureFormat format,
	vulkan::Extent2D extent,
	bksge::uint32_t mipmap_count,
	::VkImageAspectFlags aspect)
{
	auto command_buffer = BeginSingleTimeCommands(command_pool);

	::VkDeviceSize src_offset = 0;
	auto width  = extent.width;
	auto height = extent.height;

	for (bksge::uint32_t i = 0; i < mipmap_count; ++i)
	{
		::VkBufferImageCopy region {};
		region.bufferOffset                    = src_offset;
		region.bufferRowLength                 = 0;
		region.bufferImageHeight               = 0;
		region.imageSubresource.aspectMask     = aspect;
		region.imageSubresource.mipLevel       = i;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount     = 1;
		region.imageOffset                     = {0, 0, 0};
		region.imageExtent                     = {width, height, 1};

		command_buffer->CopyBufferToImage(
			buffer,
			image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&region);

		src_offset += GetSizeInBytes(format, width, height);
		width  = bksge::max(width  / 2, 1u);
		height = bksge::max(height / 2, 1u);
	}

	EndSingleTimeCommands(command_buffer);
}

}	// namespace detail

BKSGE_INLINE
Texture::Texture(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkFormat format,
	vulkan::Extent2D const& extent,
	bksge::uint32_t mipmap_count,
	::VkSampleCountFlagBits num_samples,
	::VkImageUsageFlags usage,
	::VkImageLayout image_layout)
{
	auto physical_device = device->physical_device();

	::VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
	auto const props = physical_device->GetFormatProperties(format);
	if (props.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
	{
		tiling = VK_IMAGE_TILING_LINEAR;
	}
	else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
	{
		tiling = VK_IMAGE_TILING_OPTIMAL;
	}
	else
	{
		// TODO エラー処理
	}

	::VkFlags const requirements_mask = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	::VkImageAspectFlags const aspect = VK_IMAGE_ASPECT_COLOR_BIT;

	m_image = bksge::make_shared<vulkan::Image>(
		device,
		format,
		extent,
		mipmap_count,
		num_samples,
		tiling,
		usage,
		VK_IMAGE_LAYOUT_UNDEFINED,
		requirements_mask);

	if (image_layout != VK_IMAGE_LAYOUT_UNDEFINED)
	{
		m_image->TransitionLayout(command_pool, aspect, image_layout);
	}

	m_image_view = bksge::make_shared<vulkan::ImageView>(
		device,
		*m_image,
		aspect);
}

BKSGE_INLINE
Texture::Texture(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::Texture const& texture)
	: Texture(
		device,
		command_pool,
		vulkan::TextureFormat(texture.format()),
		vulkan::Extent2D(texture.extent()),
		static_cast<bksge::uint32_t>(texture.mipmap_count()),
		VK_SAMPLE_COUNT_1_BIT,
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED)
{
	auto image_size = GetMipmappedSizeInBytes(
		texture.format(),
		texture.width(),
		texture.height(),
		texture.mipmap_count());

	auto staging_buffer = bksge::make_unique<vulkan::Buffer>(
		device,
		image_size,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	// TODO staging_buffer->Copy(texture.data(), image_size);
	{
		void* dst = staging_buffer->MapMemory(VK_WHOLE_SIZE);
		bksge::memcpy(dst, texture.data(), image_size);
		staging_buffer->UnmapMemory();
	}

	// TODO m_image->CopyFromBuffer(command_pool, staging_buffer->buffer());
	{
		auto const aspect = m_image_view->aspect_mask();

		m_image->TransitionLayout(
			command_pool,
			aspect,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		detail::CopyBufferToImage(
			command_pool,
			*staging_buffer->GetAddressOf(),
			*m_image,
			texture.format(),
			m_image->extent(),
			m_image->mipmap_count(),
			aspect);

		m_image->TransitionLayout(
			command_pool,
			aspect,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	}
}

BKSGE_INLINE
Texture::Texture(
	vulkan::ImageSharedPtr const& image,
	vulkan::ImageViewSharedPtr const& image_view)
	: m_image(image)
	, m_image_view(image_view)
{}

BKSGE_INLINE
Texture::~Texture()
{}

BKSGE_INLINE vulkan::ImageSharedPtr const&
Texture::image(void) const
{
	return m_image;
}

BKSGE_INLINE vulkan::ImageViewSharedPtr const&
Texture::image_view(void) const
{
	return m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_INL_HPP
