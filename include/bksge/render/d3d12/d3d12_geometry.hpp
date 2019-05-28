/**
 *	@file	d3d12_geometry.hpp
 *
 *	@brief	D3D12Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_GEOMETRY_HPP
#define BKSGE_RENDER_D3D12_D3D12_GEOMETRY_HPP

#include <bksge/render/d3d12/fwd/d3d12_geometry_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_vertex_buffer_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_index_buffer_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

class D3D12Geometry
{
public:
	D3D12Geometry(Geometry const& geometry, D3D12Device* device);

	~D3D12Geometry();

	void Draw(D3D12CommandList* command_list);

private:
	std::unique_ptr<D3D12VertexBuffer>		m_vertex_buffer;
	std::unique_ptr<D3D12IndexBuffer>		m_index_buffer;
	::D3D12_PRIMITIVE_TOPOLOGY				m_primitive_topology;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_geometry_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_GEOMETRY_HPP
