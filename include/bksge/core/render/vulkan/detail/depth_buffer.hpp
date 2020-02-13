/**
 *	@file	depth_buffer.hpp
 *
 *	@brief	DepthBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DEPTH_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DEPTH_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/depth_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_object_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_view_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/clear_state_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DepthBuffer
{
public:
	explicit DepthBuffer(
		vulkan::DeviceSharedPtr const& device,
		vulkan::CommandPoolSharedPtr const& command_pool,
		::VkExtent2D const& extent,
		::VkSampleCountFlagBits num_samples);

	~DepthBuffer();

	void Clear(
		vulkan::CommandPoolSharedPtr const& command_pool,
		bksge::ClearState const& clear_state);

	::VkFormat const& GetFormat(void) const;

	vulkan::ImageView const& GetImageView(void) const;

private:
	// noncopyable
	DepthBuffer(DepthBuffer const&) = delete;
	DepthBuffer& operator=(DepthBuffer const&) = delete;

private:
	vulkan::ImageObjectUniquePtr	m_image;
	vulkan::ImageViewUniquePtr		m_image_view;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/depth_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DEPTH_BUFFER_HPP
