﻿/**
 *	@file	debug_report_callback_inl.hpp
 *
 *	@brief	DebugReportCallback クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEBUG_REPORT_CALLBACK_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEBUG_REPORT_CALLBACK_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/debug_report_callback.hpp>
#include <bksge/core/render/vulkan/detail/instance.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
DebugReportCallback::DebugReportCallback(
	vulkan::InstanceSharedPtr const& instance,
	::VkDebugReportFlagsEXT flags,
	::PFN_vkDebugReportCallbackEXT func)
	: m_callback(VK_NULL_HANDLE)
	, m_instance(instance)
{
	vk::DebugReportCallbackCreateInfoEXT info;
	info.flags       = flags;
	info.pfnCallback = func;
	info.pUserData   = nullptr;

	m_callback = m_instance->CreateDebugReportCallback(info);
}

BKSGE_INLINE
DebugReportCallback::~DebugReportCallback()
{
	m_instance->DestroyDebugReportCallback(m_callback);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEBUG_REPORT_CALLBACK_INL_HPP
