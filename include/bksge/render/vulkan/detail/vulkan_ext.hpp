/**
 *	@file	vulkan_ext.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_VULKAN_EXT_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_VULKAN_EXT_HPP

#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/render/vulkan/detail/check_error.hpp>

namespace bksge
{

namespace render
{

namespace vk
{

#define BKSGE_VKEXT_FUNC(funcname, instance, ...)			\
	static auto p = reinterpret_cast<PFN_ ## funcname>(		\
		::vkGetInstanceProcAddr(instance, #funcname));		\
	if (p)	                                                \
	{	                                                    \
		p(instance, __VA_ARGS__);						    \
	}

#define BKSGE_VKEXT_RESULT_FUNC(funcname, instance, ...)	\
	static auto p = reinterpret_cast<PFN_ ## funcname>(		\
		::vkGetInstanceProcAddr(instance, #funcname));		\
	if (p)	                                                \
	{	                                                    \
		return vk::CheckError(p(instance, __VA_ARGS__));	\
	}														\
	return VK_SUCCESS

inline VkResult CreateDebugReportCallbackEXT(
	VkInstance instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	BKSGE_VKEXT_RESULT_FUNC(vkCreateDebugReportCallbackEXT, instance, pCreateInfo, pAllocator, pCallback);
}

inline void DestroyDebugReportCallbackEXT(
	VkInstance instance,
	VkDebugReportCallbackEXT callback,
	const VkAllocationCallbacks* pAllocator)
{
	BKSGE_VKEXT_FUNC(vkDestroyDebugReportCallbackEXT, instance, callback, pAllocator);
}

#undef BKSGE_VKEXT_FUNC
#undef BKSGE_VKEXT_RESULT_FUNC

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_VULKAN_EXT_HPP
