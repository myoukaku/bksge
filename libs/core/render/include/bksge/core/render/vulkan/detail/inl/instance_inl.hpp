/**
 *	@file	instance_inl.hpp
 *
 *	@brief	Instance クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INSTANCE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INSTANCE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/instance.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/algorithm/ranges/find.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline bksge::vector<bksge::string>
EnumerateInstanceLayerNames(void)
{
	bksge::vector<bksge::string> result;

	auto layer_properties = vk::EnumerateInstanceLayerProperties();
	for (auto&& layer_property : layer_properties)
	{
		result.push_back(layer_property.layerName);
	}

	return result;
}

inline bksge::vector<bksge::string>
EnumerateInstanceExtensionNames(void)
{
	bksge::vector<bksge::string> result;

	auto extension_properties = vk::EnumerateInstanceExtensionProperties(nullptr);
	for (auto&& extension_property : extension_properties)
	{
		result.push_back(extension_property.extensionName);
	}

	auto layer_properties = vk::EnumerateInstanceLayerProperties();
	for (auto&& layer_property : layer_properties)
	{
		auto layer_extension_properties =
			vk::EnumerateInstanceExtensionProperties(layer_property.layerName);
		for (auto&& layer_extension_property : layer_extension_properties)
		{
			result.push_back(layer_extension_property.extensionName);
		}
	}

	return result;
}

}	// namespace detail

BKSGE_INLINE
Instance::Instance(char const* app_name)
	: m_instance(VK_NULL_HANDLE)
{
	bksge::vector<char const*> layer_names;
	{
		// 追加可能なレイヤーを全てリストアップ
		auto const available_layer_names =
			detail::EnumerateInstanceLayerNames();

		// 追加したいレイヤー
		bksge::vector<char const*> desired_layer_names =
		{
#if defined(_DEBUG)
			"VK_LAYER_KHRONOS_validation",
			"VK_LAYER_LUNARG_standard_validation",
#endif
		};

		// 可能であればレイヤーを追加
		for (auto desired_layer_name: desired_layer_names)
		{
			if (bksge::ranges::find(available_layer_names, desired_layer_name) != available_layer_names.end())
			{
				layer_names.push_back(desired_layer_name);
			}
		}
	}

	bksge::vector<char const*> extension_names;
	{
		// 追加可能な拡張を全てリストアップ
		auto const available_extension_names =
			detail::EnumerateInstanceExtensionNames();

		// 追加したい拡張
		bksge::vector<char const*> desired_extension_names =
		{
			VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
			VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
			VK_KHR_SURFACE_EXTENSION_NAME,
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
			VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
			VK_EXT_METAL_SURFACE_EXTENSION_NAME,
#endif
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
			VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
			VK_KHR_XCB_SURFACE_EXTENSION_NAME,
#endif
		};

		// 可能であれば拡張を追加
		for (auto desired_extension_name: desired_extension_names)
		{
			if (bksge::ranges::find(available_extension_names, desired_extension_name) != available_extension_names.end())
			{
				extension_names.push_back(desired_extension_name);
			}
		}
	}

	vk::ApplicationInfo app_info;
	app_info.pApplicationName   = app_name;
	app_info.applicationVersion = 1;
	app_info.pEngineName        = app_name;
	app_info.engineVersion      = 1;
	app_info.apiVersion         = VK_API_VERSION_1_0;

	vk::InstanceCreateInfo info;
	info.pApplicationInfo = &app_info;
	info.SetEnabledLayerNames(layer_names);
	info.SetEnabledExtensionNames(extension_names);

	vk::CreateInstance(&info, nullptr, &m_instance);
}

BKSGE_INLINE
Instance::~Instance()
{
	vk::DestroyInstance(m_instance, nullptr);
}

BKSGE_INLINE bksge::vector<::VkPhysicalDevice>
Instance::EnumeratePhysicalDevices(void) const
{
	for (;;)
	{
		std::uint32_t count;
		vk::EnumeratePhysicalDevices(m_instance, &count, nullptr);

		if (count == 0)
		{
			return {};
		}

		bksge::vector<::VkPhysicalDevice> physical_devices(count);
		auto res = vk::EnumeratePhysicalDevices(
			m_instance, &count, physical_devices.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}

		return physical_devices;
	}
}

BKSGE_INLINE ::VkDebugReportCallbackEXT
Instance::CreateDebugReportCallback(
	::VkDebugReportCallbackCreateInfoEXT const& create_info)
{
	::VkDebugReportCallbackEXT callback;
	vk::CreateDebugReportCallbackEXT(m_instance, &create_info, nullptr, &callback);
	return callback;
}

BKSGE_INLINE void
Instance::DestroyDebugReportCallback(::VkDebugReportCallbackEXT callback)
{
	vk::DestroyDebugReportCallbackEXT(m_instance, callback, nullptr);
}

#if defined(BKSGE_PLATFORM_WIN32)
BKSGE_INLINE ::VkSurfaceKHR
Instance::CreateSurface(::VkWin32SurfaceCreateInfoKHR const& create_info)
{
	::VkSurfaceKHR surface;
	vk::CreateWin32SurfaceKHR(m_instance, &create_info, nullptr, &surface);
	return surface;
}
#else
#endif

BKSGE_INLINE void
Instance::DestroySurface(::VkSurfaceKHR surface)
{
	vk::DestroySurfaceKHR(m_instance, surface, nullptr);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INSTANCE_INL_HPP
