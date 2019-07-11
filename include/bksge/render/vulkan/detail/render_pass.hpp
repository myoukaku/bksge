/**
 *	@file	render_pass.hpp
 *
 *	@brief	RenderPass クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP

#include <bksge/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct RenderPassBeginInfo : public ::VkRenderPassBeginInfo
{
	RenderPassBeginInfo(void);
};

struct RenderPassCreateInfo : public ::VkRenderPassCreateInfo
{
	RenderPassCreateInfo(void);
};

class RenderPass
{
public:
	explicit RenderPass(
		std::shared_ptr<vk::Device> const& device,
		vk::RenderPassCreateInfo const& info);

	~RenderPass();

	operator ::VkRenderPass() const;

private:
	::VkRenderPass				m_render_pass;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/render_pass_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP
