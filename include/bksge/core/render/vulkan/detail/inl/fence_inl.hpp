/**
 *	@file	fence_inl.hpp
 *
 *	@brief	Fence クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FENCE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FENCE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/fence.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Fence::Fence(
	vulkan::DeviceSharedPtr const& device)
	: m_device(device)
	, m_fence(VK_NULL_HANDLE)
{
	vk::FenceCreateInfo info;
	vk::CreateFence(*m_device, &info, nullptr, &m_fence);
}

BKSGE_INLINE
Fence::~Fence()
{
	vk::DestroyFence(*m_device, m_fence, nullptr);
}

BKSGE_INLINE
Fence::operator ::VkFence() const
{
	return m_fence;
}

BKSGE_INLINE ::VkResult
Fence::Wait(::VkBool32 wait_all, std::uint64_t timeout)
{
	return vk::WaitForFences(
		*m_device, 1, &m_fence, wait_all, timeout);
}

BKSGE_INLINE ::VkResult
Fence::Reset(void)
{
	return vk::ResetFences(*m_device, 1, &m_fence);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FENCE_INL_HPP
