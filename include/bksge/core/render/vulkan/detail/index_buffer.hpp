/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INDEX_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INDEX_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/index_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class IndexBuffer
{
public:
	explicit IndexBuffer(
		vulkan::DeviceSharedPtr const& device,
		bksge::Geometry const& geometry);

	~IndexBuffer();

	void Bind(CommandBuffer* command_buffer);
	void Draw(CommandBuffer* command_buffer);

	bool enable(void) const;

private:
	std::unique_ptr<Buffer>			m_buffer;
	std::unique_ptr<DeviceMemory>	m_device_memory;
	std::uint32_t					m_count = 0;
	::VkIndexType					m_type;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/index_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INDEX_BUFFER_HPP
