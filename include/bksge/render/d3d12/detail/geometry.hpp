/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_GEOMETRY_HPP
#define BKSGE_RENDER_D3D12_DETAIL_GEOMETRY_HPP

#include <bksge/render/d3d12/detail/fwd/geometry_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/vertex_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/index_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class Geometry
{
public:
	Geometry(bksge::Geometry const& geometry, Device* device);

	~Geometry();

	void Draw(CommandList* command_list);

private:
	std::unique_ptr<VertexBuffer>		m_vertex_buffer;
	std::unique_ptr<IndexBuffer>		m_index_buffer;
	::D3D12_PRIMITIVE_TOPOLOGY			m_primitive_topology;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_GEOMETRY_HPP
