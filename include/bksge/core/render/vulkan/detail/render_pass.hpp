/**
 *	@file	render_pass.hpp
 *
 *	@brief	RenderPass クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP

#include <bksge/core/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class RenderPass
{
public:
	explicit RenderPass(
		vulkan::DeviceSharedPtr const& device,
		::VkSampleCountFlagBits num_samples,
		::VkFormat surface_format,
		::VkFormat depth_format,
		bool include_depth);

	~RenderPass();

	operator ::VkRenderPass() const;

private:
	// noncopyable
	RenderPass(RenderPass const&) = delete;
	RenderPass& operator=(RenderPass const&) = delete;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkRenderPass				m_render_pass;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/render_pass_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP
