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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>

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

	void Bind(vulkan::CommandBuffer* command_buffer);

	void Draw(vulkan::CommandBuffer* command_buffer);

private:
	// noncopyable
	VertexBuffer(VertexBuffer const&) = delete;
	VertexBuffer& operator=(VertexBuffer const&) = delete;

private:
	bksge::unique_ptr<vulkan::Buffer>	m_buffer;
	bksge::uint32_t						m_count = 0;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VERTEX_BUFFER_HPP
