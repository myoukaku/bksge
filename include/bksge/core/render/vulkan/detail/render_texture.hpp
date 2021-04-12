﻿/**
 *	@file	render_texture.hpp
 *
 *	@brief	RenderTexture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_TEXTURE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_TEXTURE_HPP

#include <bksge/core/render/vulkan/detail/fwd/render_texture_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_object_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_view_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/clear_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class RenderTexture
{
public:
	explicit RenderTexture(
		vulkan::DeviceSharedPtr const& device,
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkFormat format,
		::VkExtent2D const& extent,
		::VkSampleCountFlagBits num_samples);

	~RenderTexture();

	void TransitionLayout(
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkImageLayout new_layout);

	void Clear(
		vulkan::CommandPoolSharedPtr const& command_pool,
		bksge::ClearState const& clear_state);

	vulkan::Image const& image(void) const;

	vulkan::ImageView const& image_view(void) const;

private:
	// noncopyable
	RenderTexture(RenderTexture const&) = delete;
	RenderTexture& operator=(RenderTexture const&) = delete;

private:
	vulkan::ImageObjectUniquePtr	m_image;
	vulkan::ImageViewUniquePtr		m_image_view;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/render_texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_TEXTURE_HPP
