/**
 *	@file	debug_report_callback_inl.hpp
 *
 *	@brief	DebugReportCallbackEXT クラスの実装
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
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
DebugReportCallbackCreateInfoEXT::DebugReportCallbackCreateInfoEXT(void)
{
	sType       = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	pNext       = nullptr;
	flags       = 0;
	pfnCallback = nullptr;
	pUserData   = nullptr;
}

BKSGE_INLINE
DebugReportCallbackEXT::DebugReportCallbackEXT(
	std::shared_ptr<vk::Instance> const& instance,
	vk::DebugReportCallbackCreateInfoEXT const& info)
	: m_callback(VK_NULL_HANDLE)
	, m_instance(instance)
{
	vk::CreateDebugReportCallbackEXT(*m_instance, &info, nullptr, &m_callback);
}

BKSGE_INLINE
DebugReportCallbackEXT::~DebugReportCallbackEXT()
{
	vk::DestroyDebugReportCallbackEXT(*m_instance, m_callback, nullptr);
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEBUG_REPORT_CALLBACK_INL_HPP
