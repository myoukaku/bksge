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
#include <bksge/core/render/vulkan/detail/image_object.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/texture_format.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/buffer_object.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/texture.hpp>
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

inline void
CopyBufferToImage(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkBuffer buffer,
	::VkImage image,
	bksge::TextureFormat format,
	::VkExtent2D extent,
	bksge::uint32_t mipmap_count)
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
		region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel       = i;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount     = 1;
		region.imageOffset                     = {0, 0, 0};
		region.imageExtent = {width, height, 1};

		vk::CmdCopyBufferToImage(
			*command_buffer,
			buffer,
			image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&region);

		src_offset += GetSizeInBytes(format, width, height);
		width  = bksge::max(width  / 2, 1u);
		height = bksge::max(height / 2, 1u);
	}

	EndSingleTimeCommands(command_pool, command_buffer);
}

BKSGE_INLINE
Texture::Texture(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::Texture const& texture)
{
	::VkFormat const format = vulkan::TextureFormat(texture.format());

	::VkExtent2D const extent = vulkan::Extent2D(texture.extent());

	auto const mipmap_count = static_cast<bksge::uint32_t>(texture.mipmap_count());

	::VkImageTiling const tiling = VK_IMAGE_TILING_OPTIMAL;

	::VkImageUsageFlags const usage =
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT;

	::VkImageLayout const initial_layout =
		VK_IMAGE_LAYOUT_UNDEFINED;

	::VkFlags const requirements_mask =
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	m_image = bksge::make_unique<vulkan::ImageObject>(
		device,
		format,
		extent,
		mipmap_count,
		VK_SAMPLE_COUNT_1_BIT,
		tiling,
		usage,
		initial_layout,
		requirements_mask);

	auto image_size = GetMipmappedSizeInBytes(texture.format(), texture.width(), texture.height(), texture.mipmap_count());//texture.stride() * texture.height();

	auto staging_buffer = bksge::make_unique<vulkan::BufferObject>(
		device,
		image_size,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	{
		void* dst = staging_buffer->MapMemory(VK_WHOLE_SIZE);
		bksge::memcpy(dst, texture.data(), image_size);
		staging_buffer->UnmapMemory();
	}

	m_image->TransitionLayout(
		command_pool,
		VK_IMAGE_ASPECT_COLOR_BIT,
		mipmap_count,
		initial_layout,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	CopyBufferToImage(
		command_pool,
		staging_buffer->GetBuffer(),
		m_image->GetImage(),
		texture.format(),
		extent,
		mipmap_count);

	m_image->TransitionLayout(
		command_pool,
		VK_IMAGE_ASPECT_COLOR_BIT,
		mipmap_count,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	m_image_view = bksge::make_unique<vulkan::ImageView>(
		device,
		m_image->GetImage(),
		format,
		VK_IMAGE_ASPECT_COLOR_BIT,
		mipmap_count);
}

BKSGE_INLINE
Texture::~Texture()
{
}

BKSGE_INLINE vulkan::ImageViewUniquePtr const&
Texture::GetImageView(void) const
{
	return m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_TEXTURE_INL_HPP
