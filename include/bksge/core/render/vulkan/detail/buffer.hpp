/**
 *	@file	buffer.hpp
 *
 *	@brief	Buffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Buffer
{
public:
	explicit Buffer(
		vulkan::DeviceSharedPtr const& device,
		::VkDeviceSize                 size,
		::VkBufferUsageFlags           usage);

	~Buffer();

	::VkMemoryRequirements requirements(void) const;

	operator ::VkBuffer() const;

private:
	// noncopyable
	Buffer(Buffer const&) = delete;
	Buffer& operator=(Buffer const&) = delete;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkBuffer					m_buffer;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_HPP
