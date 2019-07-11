/**
 *	@file	fence.hpp
 *
 *	@brief	Fence クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_FENCE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_FENCE_HPP

#include <bksge/render/vulkan/detail/fwd/fence_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct FenceCreateInfo : public ::VkFenceCreateInfo
{
	FenceCreateInfo(void);
};

class Fence
{
public:
	explicit Fence(
		std::shared_ptr<vk::Device> const& device,
		vk::FenceCreateInfo const& info);

	~Fence();

	operator ::VkFence() const;

	::VkFence const* GetAddress() const;

private:
	::VkFence					m_fence;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/fence_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_FENCE_HPP
