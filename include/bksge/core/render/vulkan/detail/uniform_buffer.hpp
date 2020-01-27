/**
 *	@file	uniform_buffer.hpp
 *
 *	@brief	UniformBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class UniformBuffer
{
public:
	explicit UniformBuffer(
		vulkan::DeviceSharedPtr const& device,
		::VkDeviceSize                 size);

	~UniformBuffer();

	vulkan::BufferUniquePtr const& GetBuffer() const;

	std::uint8_t* GetMappedBuffer(void) const;

	std::size_t Allocate(std::size_t size);

	void BeginFrame(void);

private:
	vulkan::DeviceSharedPtr			m_device;
	vulkan::BufferUniquePtr			m_buffer;
	vulkan::DeviceMemoryUniquePtr	m_device_memory;
	std::uint8_t*					m_mapped_buffer = nullptr;
	std::size_t						m_offset = 0;
	std::size_t						m_offset_alignment = 0;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/uniform_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP
