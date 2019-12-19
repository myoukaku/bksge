﻿/**
 *	@file	surface.hpp
 *
 *	@brief	SurfaceKHR クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SURFACE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SURFACE_HPP

#include <bksge/core/render/vulkan/detail/fwd/surface_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/instance_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

class SurfaceKHR
{
public:
	explicit SurfaceKHR(
		std::shared_ptr<vk::Instance> const& instance,
		Window const& window);

	~SurfaceKHR();

	operator ::VkSurfaceKHR() const;

private:
	::VkSurfaceKHR					m_surface;
	std::shared_ptr<vk::Instance>   m_instance;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/surface_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SURFACE_HPP