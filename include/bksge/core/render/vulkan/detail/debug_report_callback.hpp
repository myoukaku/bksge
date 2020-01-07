/**
 *	@file	debug_report_callback.hpp
 *
 *	@brief	DebugReportCallback クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP

#include <bksge/core/render/vulkan/detail/fwd/debug_report_callback_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/instance_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DebugReportCallback
{
public:
	explicit DebugReportCallback(
		vulkan::InstanceSharedPtr const& instance,
		::VkDebugReportFlagsEXT flags,
		::PFN_vkDebugReportCallbackEXT func);

	~DebugReportCallback();

private:
	vulkan::InstanceSharedPtr	m_instance;
	::VkDebugReportCallbackEXT	m_callback;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/debug_report_callback_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP
