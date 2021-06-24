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
#include <bksge/fnd/cstdint/uint64_t.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Fence::Fence(vulkan::DeviceSharedPtr const& device)
	: m_fence(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::FenceCreateInfo info;
	m_fence = m_device->CreateFence(info);
}

BKSGE_INLINE
Fence::~Fence()
{
	m_device->DestroyFence(m_fence);
}

BKSGE_INLINE ::VkResult
Fence::Wait(::VkBool32 wait_all, bksge::uint64_t timeout)
{
	return m_device->WaitForFences(1, &m_fence, wait_all, timeout);
}

BKSGE_INLINE ::VkResult
Fence::Reset(void)
{
	return m_device->ResetFences(1, &m_fence);
}

BKSGE_INLINE ::VkFence const*
Fence::GetAddressOf(void) const
{
	return &m_fence;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FENCE_INL_HPP
