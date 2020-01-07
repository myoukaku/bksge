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
#include <vector>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Instance::Instance(char const* app_name)
	: m_instance(VK_NULL_HANDLE)
{
	std::vector<char const*> layer_names;
	std::vector<char const*> extension_names;

#if 0	// 可能なレイヤーと拡張を全て追加

	// これらのインスタンスは vk::CreateInstance を呼び出すまで生きていなければいけない
	// (layer_names 等には char const* をコピーしているだけなので)
	auto extension_properties = vk::EnumerateInstanceExtensionProperties(nullptr);
	auto layer_properties     = vk::EnumerateInstanceLayerProperties();

	for (auto&& layer_property : layer_properties)
	{
		layer_names.push_back(layer_property.layerName);
		auto layer_extension_properties =
			vk::EnumerateInstanceExtensionProperties(layer_property.layerName);
		for (auto&& layer_extension_property : layer_extension_properties)
		{
			extension_properties.push_back(layer_extension_property);
		}
	}

	for (auto&& extension_property : extension_properties)
	{
		extension_names.push_back(extension_property.extensionName);
	}

#else	// 使うものだけを手動で追加

#if defined(_DEBUG)
	layer_names.push_back("VK_LAYER_LUNARG_standard_validation");
#endif

	extension_names.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	extension_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#if defined(__ANDROID__)
	extension_names.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_WIN32)
	extension_names.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_METAL_EXT)
	extension_names.push_back(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	extension_names.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#else
	extension_names.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#endif

#endif

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

BKSGE_INLINE std::vector<::VkPhysicalDevice>
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
