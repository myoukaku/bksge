/**
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
#include <cstring>

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
	::VkExtent2D extent)
{
	auto command_buffer = BeginSingleTimeCommands(command_pool);

	::VkBufferImageCopy region {};
	region.bufferOffset                    = 0;
	region.bufferRowLength                 = 0;
	region.bufferImageHeight               = 0;
	region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel       = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount     = 1;
	region.imageOffset                     = {0, 0, 0};
	region.imageExtent = {extent.width,extent.height,1};

	vk::CmdCopyBufferToImage(
		*command_buffer,
		buffer,
		image,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1,
		&region);

	EndSingleTimeCommands(command_pool, command_buffer);
}

BKSGE_INLINE
Texture::Texture(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::Texture const& texture)
{
	auto const& physical_device = device->GetPhysicalDevice();

	::VkFormat format = vulkan::TextureFormat(texture.format());

	::VkFormatProperties format_props;
	vk::GetPhysicalDeviceFormatProperties(
		*physical_device, format, &format_props);

	::VkFormatFeatureFlags const features = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT;

	bool const needs_staging =
		((format_props.linearTilingFeatures & features) != features);

	::VkImageTiling const tiling = needs_staging ?
		VK_IMAGE_TILING_OPTIMAL :
		VK_IMAGE_TILING_LINEAR;

	::VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT;
	if (needs_staging)
	{
		usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	}

	::VkImageLayout const initial_layout = needs_staging ?
		VK_IMAGE_LAYOUT_UNDEFINED :
		VK_IMAGE_LAYOUT_PREINITIALIZED;

	::VkExtent2D extent = vulkan::Extent2D(texture.extent());

	::VkFlags requirements_mask = needs_staging ?
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT :
		(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	m_image = bksge::make_unique<vulkan::ImageObject>(
		device,
		format,
		extent,
		VK_SAMPLE_COUNT_1_BIT,
		tiling,
		usage,
		initial_layout,
		requirements_mask);

	auto image_size = texture.stride() * texture.height();

	std::unique_ptr<vulkan::BufferObject> staging_buffer;
	if (needs_staging)
	{
		staging_buffer = bksge::make_unique<vulkan::BufferObject>(
			device,
			image_size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
			VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	}

	void* dst;
	if (needs_staging)
	{
		dst = staging_buffer->MapMemory(VK_WHOLE_SIZE);
	}
	else
	{
		dst = m_image->MapMemory(VK_WHOLE_SIZE);
	}

	std::memcpy(dst, texture.data(), image_size);

	if (needs_staging)
	{
		staging_buffer->UnmapMemory();
	}
	else
	{
		m_image->UnmapMemory();
	}

	if (!needs_staging)
	{
		m_image->TransitionLayout(
			command_pool,
			VK_IMAGE_ASPECT_COLOR_BIT,
			initial_layout,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	}
	else
	{
		m_image->TransitionLayout(
			command_pool,
			VK_IMAGE_ASPECT_COLOR_BIT,
			initial_layout,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		CopyBufferToImage(
			command_pool,
			staging_buffer->GetBuffer(),
			m_image->GetImage(),
			extent);

		m_image->TransitionLayout(
			command_pool,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	}

	m_image_view = bksge::make_unique<vulkan::ImageView>(
		device, m_image->GetImage(), format, VK_IMAGE_ASPECT_COLOR_BIT);
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
