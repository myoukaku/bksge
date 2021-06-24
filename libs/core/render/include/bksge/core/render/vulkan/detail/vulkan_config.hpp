/**
 *	@file	vulkan_config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_CONFIG_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_CONFIG_HPP

#include <bksge/fnd/config.hpp>

#if defined(BKSGE_PLATFORM_WIN32)
#	define VK_USE_PLATFORM_WIN32_KHR
#elif defined(BKSGE_PLATFORM_MACOS)
//#	define VK_USE_PLATFORM_MACOS_MVK
#elif defined(BKSGE_PLATFORM_ANDROID)
//#	define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(BKSGE_PLATFORM_IOS)
//#	define VK_USE_PLATFORM_IOS_MVK
#elif defined(BKSGE_PLATFORM_LINUX)
//#	if XCB
//#		define VK_USE_PLATFORM_XCB_KHR
//#	elif XLIB
//#		define VK_USE_PLATFORM_XLIB_KHR
//#	elif WAYLAND
//#		define VK_USE_PLATFORM_WAYLAND_KHR
//#	endif
#else
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_CONFIG_HPP
