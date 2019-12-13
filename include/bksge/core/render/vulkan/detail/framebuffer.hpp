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
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct FramebufferCreateInfo : public ::VkFramebufferCreateInfo
{
	FramebufferCreateInfo(void);
};

class Framebuffer
{
public:
	explicit Framebuffer(
		std::shared_ptr<vk::Device> const& device,
		vk::FramebufferCreateInfo const& info);

	~Framebuffer();

	operator ::VkFramebuffer() const;

private:
	::VkFramebuffer				m_framebuffer;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/framebuffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP
