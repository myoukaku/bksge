/**
 *	@file	surface_inl.hpp
 *
 *	@brief	SurfaceKHR クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INL_SURFACE_INL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INL_SURFACE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/detail/surface.hpp>
#include <bksge/render/vulkan/detail/instance.hpp>
#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/window/window.hpp>
#include <bksge/config.hpp>
#include <memory>

#if defined(BKSGE_PLATFORM_WIN32)
#include <bksge/detail/win32.hpp>
#endif
namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
SurfaceKHR::SurfaceKHR(
	std::shared_ptr<vk::Instance> const& instance,
	Window const& window)
	: m_surface(VK_NULL_HANDLE)
	, m_instance(instance)
{
#if defined(BKSGE_PLATFORM_WIN32)
	::VkWin32SurfaceCreateInfoKHR createInfo = {};
	createInfo.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext     = nullptr;
	createInfo.hinstance = win32::GetModuleHandle<char>(nullptr);
	createInfo.hwnd      = window.handle();
	vk::CreateWin32SurfaceKHR(*m_instance, &createInfo, nullptr, &m_surface);
#else
	(void)window;
#endif
}

BKSGE_INLINE
SurfaceKHR::~SurfaceKHR()
{
	vk::DestroySurfaceKHR(*m_instance, m_surface, nullptr);
}

BKSGE_INLINE
SurfaceKHR::operator ::VkSurfaceKHR() const
{
	return m_surface;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_DETAIL_INL_SURFACE_INL_HPP
