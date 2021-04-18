/**
 *	@file	texture.hpp
 *
 *	@brief	Texture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_TEXTURE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_TEXTURE_HPP

#include <bksge/core/render/vulkan/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_view_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Texture
{
public:
	explicit Texture(
		vulkan::DeviceSharedPtr const& device,
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkFormat format,
		::VkExtent2D const& extent,
		bksge::uint32_t mipmap_count,
		::VkSampleCountFlagBits num_samples,
		::VkImageUsageFlags usage,
		::VkImageLayout image_layout);

	explicit Texture(
		vulkan::DeviceSharedPtr const& device,
		vulkan::CommandPoolSharedPtr const& command_pool,
		bksge::Texture const& texture);

	explicit Texture(
		vulkan::ImageSharedPtr const& image,
		vulkan::ImageViewSharedPtr const& image_view);

	~Texture();

	vulkan::ImageSharedPtr const& image(void) const;

	vulkan::ImageViewSharedPtr const& image_view(void) const;

private:
	// noncopyable
	Texture(Texture const&) = delete;
	Texture& operator=(Texture const&) = delete;

private:
	vulkan::ImageSharedPtr			m_image;
	vulkan::ImageViewSharedPtr		m_image_view;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_TEXTURE_HPP
