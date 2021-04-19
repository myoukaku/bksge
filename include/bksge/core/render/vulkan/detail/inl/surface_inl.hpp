/**
 *	@file	surface_inl.hpp
 *
 *	@brief	Surface クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SURFACE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SURFACE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/surface.hpp>
#include <bksge/core/render/vulkan/detail/instance.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_PLATFORM_WIN32)
#include <bksge/core/detail/win32.hpp>
#endif
namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Surface::Surface(
	vulkan::InstanceSharedPtr const& instance,
	Window const& window)
	: m_surface(VK_NULL_HANDLE)
	, m_instance(instance)
{
#if defined(BKSGE_PLATFORM_WIN32)
	vk::Win32SurfaceCreateInfoKHR info;
	info.hinstance = win32::GetModuleHandle<char>(nullptr);
	info.hwnd      = window.handle();
	m_surface = m_instance->CreateSurface(info);
#else
	(void)window;
#endif
}

BKSGE_INLINE
Surface::~Surface()
{
	m_instance->DestroySurface(m_surface);
}

BKSGE_INLINE ::VkSurfaceCapabilitiesKHR
Surface::GetCapabilities(vulkan::PhysicalDevice const& physical_device) const
{
	return physical_device.GetSurfaceCapabilities(m_surface);
}

BKSGE_INLINE bksge::uint32_t
Surface::GetPresentQueueFamilyIndex(vulkan::PhysicalDevice const& physical_device) const
{
	return physical_device.GetPresentQueueFamilyIndex(m_surface);
}

BKSGE_INLINE bksge::vector<::VkSurfaceFormatKHR>
Surface::GetFormats(vulkan::PhysicalDevice const& physical_device) const
{
	return physical_device.GetSurfaceFormats(m_surface);
}

BKSGE_INLINE ::VkSurfaceKHR
Surface::Get(void) const
{
	return m_surface;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SURFACE_INL_HPP
