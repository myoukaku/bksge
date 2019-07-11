/**
 *	@file	debug_report_callback.hpp
 *
 *	@brief	DebugReportCallback クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP

#include <bksge/render/vulkan/detail/fwd/debug_report_callback_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/instance_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct DebugReportCallbackCreateInfoEXT
	: public ::VkDebugReportCallbackCreateInfoEXT
{
	DebugReportCallbackCreateInfoEXT(void);
};

class DebugReportCallbackEXT
{
public:
	explicit DebugReportCallbackEXT(
		std::shared_ptr<vk::Instance> const& instance,
		vk::DebugReportCallbackCreateInfoEXT const& info);

	~DebugReportCallbackEXT();

private:
	::VkDebugReportCallbackEXT		m_callback;
	std::shared_ptr<vk::Instance>	m_instance;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/debug_report_callback_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP
