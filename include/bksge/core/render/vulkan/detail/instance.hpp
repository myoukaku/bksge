/**
 *	@file	instance.hpp
 *
 *	@brief	Instance クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INSTANCE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INSTANCE_HPP

#include <bksge/core/render/vulkan/detail/fwd/instance_fwd.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <cstddef>
#include <vector>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Instance
{
public:
	explicit Instance(char const* app_name);

	~Instance();

	std::vector<::VkPhysicalDevice> EnumeratePhysicalDevices(void) const;

	operator ::VkInstance() const;

private:
	::VkInstance m_instance;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/instance_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INSTANCE_HPP
