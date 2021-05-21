/**
 *	@file	framebuffer.hpp
 *
 *	@brief	Framebuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/framebuffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/image_fwd.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/clear_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Framebuffer
{
public:
	explicit Framebuffer(
		vulkan::DeviceSharedPtr const& device,
		vulkan::Extent2D const& extent,
		::VkSampleCountFlagBits num_samples,
		vulkan::ImageSharedPtr const& color_buffer,
		vulkan::ImageSharedPtr const& depth_stencil_buffer);

	~Framebuffer();

	void Clear(
		vulkan::CommandBuffer* command_buffer,
		bksge::ClearState const& clear_state);

	vk::RenderPassBeginInfo GetRenderPassBeginInfo(void) const;

public:
	vulkan::ImageSharedPtr const& color_buffer(void) const;

	vulkan::RenderPassSharedPtr const& render_pass(void) const;

private:
	// noncopyable
	Framebuffer(Framebuffer const&) = delete;
	Framebuffer& operator=(Framebuffer const&) = delete;

private:
	::VkFramebuffer					m_framebuffer;
	vulkan::DeviceSharedPtr			m_device;
	vulkan::Extent2D				m_extent;
	vulkan::ImageSharedPtr			m_color_buffer;
	vulkan::ImageSharedPtr			m_depth_stencil_buffer;
	vulkan::RenderPassSharedPtr		m_render_pass;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/framebuffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP
