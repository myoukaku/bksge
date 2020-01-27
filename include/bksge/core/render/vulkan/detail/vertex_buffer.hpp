/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VERTEX_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VERTEX_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/vertex_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class VertexBuffer
{
public:
	explicit VertexBuffer(
		vulkan::DeviceSharedPtr const& device,
		bksge::Geometry const& geometry);

	~VertexBuffer();

	void Bind(CommandBuffer* command_buffer);
	void Draw(CommandBuffer* command_buffer);

private:
	std::unique_ptr<vulkan::Buffer>			m_buffer;
	std::unique_ptr<vulkan::DeviceMemory>	m_device_memory;
	std::uint32_t							m_count = 0;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VERTEX_BUFFER_HPP
