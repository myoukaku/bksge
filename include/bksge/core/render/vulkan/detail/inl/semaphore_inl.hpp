/**
 *	@file	semaphore_inl.hpp
 *
 *	@brief	Semaphore クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SEMAPHORE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SEMAPHORE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/semaphore.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Semaphore::Semaphore(vulkan::DeviceSharedPtr const& device)
	: m_device(device)
{
	vk::SemaphoreCreateInfo info;
	vk::CreateSemaphore(*m_device, &info, nullptr, &m_semaphore);
}

BKSGE_INLINE
Semaphore::~Semaphore()
{
	vk::DestroySemaphore(*m_device, m_semaphore, nullptr);
}

BKSGE_INLINE
Semaphore::operator ::VkSemaphore() const
{
	return m_semaphore;
}

BKSGE_INLINE
::VkSemaphore const* Semaphore::GetAddressOf(void) const
{
	return &m_semaphore;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SEMAPHORE_INL_HPP
