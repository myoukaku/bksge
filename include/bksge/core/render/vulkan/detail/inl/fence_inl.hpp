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

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
FenceCreateInfo::FenceCreateInfo(void)
{
	sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	pNext = nullptr;
	flags = 0;
}

BKSGE_INLINE
Fence::Fence(
	std::shared_ptr<vk::Device> const& device,
	vk::FenceCreateInfo const& info)
	: m_fence(VK_NULL_HANDLE)
	, m_device(device)
{
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

BKSGE_INLINE
::VkFence const* Fence::GetAddress() const
{
	return &m_fence;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FENCE_INL_HPP
