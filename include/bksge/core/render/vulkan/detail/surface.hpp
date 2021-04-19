/**
 *	@file	surface.hpp
 *
 *	@brief	Surface クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SURFACE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SURFACE_HPP

#include <bksge/core/render/vulkan/detail/fwd/surface_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/instance_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/physical_device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Surface
{
public:
	explicit Surface(
		vulkan::InstanceSharedPtr const& instance,
		Window const& window);

	~Surface();

	::VkSurfaceCapabilitiesKHR
	GetCapabilities(vulkan::PhysicalDevice const& physical_device) const;

	bksge::uint32_t
	GetPresentQueueFamilyIndex(vulkan::PhysicalDevice const& physical_device) const;

	bksge::vector<::VkSurfaceFormatKHR>
	GetFormats(vulkan::PhysicalDevice const& physical_device) const;

	::VkSurfaceKHR Get(void) const;

private:
	// noncopyable
	Surface(Surface const&) = delete;
	Surface& operator=(Surface const&) = delete;

private:
	::VkSurfaceKHR				m_surface;
	vulkan::InstanceSharedPtr   m_instance;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/surface_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SURFACE_HPP
