/**
 *	@file	fence.hpp
 *
 *	@brief	Fence クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_FENCE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_FENCE_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct FenceCreateInfo : public ::VkFenceCreateInfo
{
	FenceCreateInfo(void)
	{
		sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		pNext = nullptr;
		flags = 0;
	}
};

class Fence
{
public:
	explicit Fence(
		std::shared_ptr<vk::Device> const& device,
		vk::FenceCreateInfo const& info)
		: m_fence(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreateFence(*m_device, &info, nullptr, &m_fence);
	}

	~Fence()
	{
		vk::DestroyFence(*m_device, m_fence, nullptr);
	}

	operator ::VkFence() const
	{
		return m_fence;
	}

	::VkFence const* GetAddress() const
	{
		return &m_fence;
	}

private:
	::VkFence					m_fence;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_FENCE_HPP
