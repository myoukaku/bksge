/**
 *	@file	debug_report_callback.hpp
 *
 *	@brief	DebugReportCallback クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/instance.hpp>
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
	DebugReportCallbackCreateInfoEXT(void)
	{
		sType       = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		pNext       = nullptr;
		flags       = 0;
		pfnCallback = nullptr;
		pUserData   = nullptr;
	}
};

class DebugReportCallbackEXT
{
public:
	explicit DebugReportCallbackEXT(
		std::shared_ptr<vk::Instance> const& instance,
		vk::DebugReportCallbackCreateInfoEXT const& info)
		: m_callback(VK_NULL_HANDLE)
		, m_instance(instance)
	{
		vk::CreateDebugReportCallbackEXT(*m_instance, &info, nullptr, &m_callback);
	}

	~DebugReportCallbackEXT()
	{
		vk::DestroyDebugReportCallbackEXT(*m_instance, m_callback, nullptr);
	}

private:
	::VkDebugReportCallbackEXT		m_callback;
	std::shared_ptr<vk::Instance>	m_instance;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_DEBUG_REPORT_CALLBACK_HPP
