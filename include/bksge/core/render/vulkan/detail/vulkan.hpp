/**
 *	@file	vulkan.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_HPP

#include <bksge/core/render/vulkan/detail/vulkan_config.hpp>

#include <bksge/core/render/vulkan/detail/vulkan_core.hpp>

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
#	include <bksge/core/render/vulkan/detail/vulkan_android.hpp>
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
#	include <bksge/core/render/vulkan/detail/vulkan_fuchsia.hpp>
#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
#	include <bksge/core/render/vulkan/detail/vulkan_ios.hpp>
#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
#	include <bksge/core/render/vulkan/detail/vulkan_macos.hpp>
#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
#	include <bksge/core/render/vulkan/detail/vulkan_metal.hpp>
#endif
#if defined(VK_USE_PLATFORM_VI_NN)
#	include <bksge/core/render/vulkan/detail/vulkan_vi.hpp>
#endif
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
#	include <bksge/core/render/vulkan/detail/vulkan_wayland.hpp>
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
#	include <bksge/core/render/vulkan/detail/vulkan_win32.hpp>
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
#	include <bksge/core/render/vulkan/detail/vulkan_xcb.hpp>
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
#	include <bksge/core/render/vulkan/detail/vulkan_xlib.hpp>
#endif
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
#	include <bksge/core/render/vulkan/detail/vulkan_xlib_xrandr.hpp>
#endif
#if defined(VK_USE_PLATFORM_GGP)
#	include <bksge/core/render/vulkan/detail/vulkan_ggp.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_HPP
