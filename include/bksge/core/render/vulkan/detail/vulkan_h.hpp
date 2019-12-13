/**
 *	@file	vulkan_h.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_H_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_H_HPP

#include <bksge/fnd/config.hpp>

#if defined(BKSGE_PLATFORM_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX
#endif

#include <vulkan/vulkan.h>

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_H_HPP
