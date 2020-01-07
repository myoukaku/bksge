﻿/**
 *	@file	fence.hpp
 *
 *	@brief	Fence クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FENCE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FENCE_HPP

#include <bksge/core/render/vulkan/detail/fwd/fence_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Fence
{
public:
	explicit Fence(vulkan::DeviceSharedPtr const& device);

	~Fence();

	operator ::VkFence() const;

	::VkFence const* GetAddressOf() const;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkFence					m_fence;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/fence_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FENCE_HPP
