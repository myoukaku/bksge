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

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline bksge::vector<bksge::string> EnumerateLayerNames(void)
{
	bksge::vector<bksge::string> result;

	auto layer_properties = vk::EnumerateInstanceLayerProperties();
	for (auto&& layer_property : layer_properties)
	{
		result.push_back(layer_property.layerName);
	}

	return result;
}

inline bksge::vector<bksge::string> EnumerateExtensionNames(void)
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

inline bool AppendIfAvailable(bksge::vector<char const*>* out_list, bksge::vector<bksge::string> const& available_list, char const* s)
{
	if (bksge::ranges::find(available_list, s) != available_list.end())
	{
		out_list->push_back(s);
		return true;
	}

	return false;
}

}	// namespace detail

BKSGE_INLINE
Instance::Instance(char const* app_name)
	: m_instance(VK_NULL_HANDLE)
{
	// 追加可能なレイヤーと拡張を全てリストアップ
	auto const available_layer_names     = detail::EnumerateLayerNames();
	auto const available_extension_names = detail::EnumerateExtensionNames();

	// 追加したいレイヤー
	bksge::vector<char const*> desired_layer_names =
	{
#if defined(_DEBUG)
		"VK_LAYER_KHRONOS_validation",
		"VK_LAYER_LUNARG_standard_validation",
#endif
	};

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

	// 可能であればレイヤーを追加
	bksge::vector<char const*> layer_names;
	for (auto desired_layer_name: desired_layer_names)
	{
		detail::AppendIfAvailable(&layer_names, available_layer_names, desired_layer_name);
	}

	// 可能であれば拡張を追加
	bksge::vector<char const*> extension_names;
	for (auto desired_extension_name: desired_extension_names)
	{
		detail::AppendIfAvailable(&extension_names, available_extension_names, desired_extension_name);
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
	return vk::EnumeratePhysicalDevices(m_instance);
}

BKSGE_INLINE
Instance::operator ::VkInstance() const
{
	return m_instance;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INSTANCE_INL_HPP
