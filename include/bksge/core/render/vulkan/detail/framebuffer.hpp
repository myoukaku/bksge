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
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <vector>

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
		::VkRenderPass const& render_pass,
		std::vector<::VkImageView> const& attachments,
		::VkExtent2D const& extent);

	~Framebuffer();

	operator ::VkFramebuffer() const;

private:
	// noncopyable
	Framebuffer(Framebuffer const&) = delete;
	Framebuffer& operator=(Framebuffer const&) = delete;

private:
	vulkan::DeviceSharedPtr	m_device;
	::VkFramebuffer			m_framebuffer;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/framebuffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP
