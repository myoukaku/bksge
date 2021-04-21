/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_GEOMETRY_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_GEOMETRY_HPP

#include <bksge/core/render/vulkan/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/vertex_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/index_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Geometry
{
public:
	explicit Geometry(
		vulkan::DeviceSharedPtr const& device,
		bksge::Geometry const& geometry);

	~Geometry();

	void Draw(vulkan::CommandBuffer* command_buffer);

private:
	// noncopyable
	Geometry(Geometry const&) = delete;
	Geometry& operator=(Geometry const&) = delete;

private:
	bksge::unique_ptr<vulkan::VertexBuffer>		m_vertex_buffer;
	bksge::unique_ptr<vulkan::IndexBuffer>		m_index_buffer;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_GEOMETRY_HPP
