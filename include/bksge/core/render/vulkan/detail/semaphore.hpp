/**
 *	@file	semaphore.hpp
 *
 *	@brief	Semaphore クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SEMAPHORE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SEMAPHORE_HPP

#include <bksge/core/render/vulkan/detail/fwd/semaphore_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Semaphore
{
public:
	explicit Semaphore(vulkan::DeviceSharedPtr const& device);

	~Semaphore();

	::VkSemaphore const* GetAddressOf() const;

private:
	// noncopyable
	Semaphore(Semaphore const&) = delete;
	Semaphore& operator=(Semaphore const&) = delete;

private:
	::VkSemaphore				m_semaphore;
	vulkan::DeviceSharedPtr		m_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/semaphore_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SEMAPHORE_HPP
