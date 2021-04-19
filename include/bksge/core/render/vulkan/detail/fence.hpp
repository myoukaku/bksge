/**
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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint64_t.hpp>

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

	::VkResult Wait(::VkBool32 wait_all, bksge::uint64_t timeout);

	::VkResult Reset(void);

	operator ::VkFence() const;

private:
	// noncopyable
	Fence(Fence const&) = delete;
	Fence& operator=(Fence const&) = delete;

private:
	::VkFence					m_fence;
	vulkan::DeviceSharedPtr		m_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/fence_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FENCE_HPP
