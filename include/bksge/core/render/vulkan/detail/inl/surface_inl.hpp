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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/window/window.hpp>
#include <bksge/fnd/config.hpp>
#include <memory>

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
	: m_instance(instance)
	, m_surface(VK_NULL_HANDLE)
{
#if defined(BKSGE_PLATFORM_WIN32)
	vk::Win32SurfaceCreateInfoKHR info;
	info.hinstance = win32::GetModuleHandle<char>(nullptr);
	info.hwnd      = window.handle();
	vk::CreateWin32SurfaceKHR(*m_instance, &info, nullptr, &m_surface);
#else
	(void)window;
#endif
}

BKSGE_INLINE
Surface::~Surface()
{
	vk::DestroySurfaceKHR(*m_instance, m_surface, nullptr);
}

BKSGE_INLINE
Surface::operator ::VkSurfaceKHR() const
{
	return m_surface;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SURFACE_INL_HPP
