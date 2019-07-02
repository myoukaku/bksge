/**
 *	@file	surface.hpp
 *
 *	@brief	Surface クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_SURFACE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_SURFACE_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/instance.hpp>
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

class Surface
{
public:
	explicit Surface(std::shared_ptr<vk::Instance> const& instance, Window const& window)
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

	~Surface()
	{
		vk::DestroySurfaceKHR(*m_instance, m_surface, nullptr);
	}

	operator ::VkSurfaceKHR() const
	{
		return m_surface;
	}

private:
	::VkSurfaceKHR					m_surface;
	std::shared_ptr<vk::Instance>   m_instance;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_SURFACE_HPP
