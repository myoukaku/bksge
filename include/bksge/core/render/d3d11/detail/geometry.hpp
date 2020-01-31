/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_GEOMETRY_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_GEOMETRY_HPP

#include <bksge/core/render/d3d11/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d11/detail/vertex_buffer.hpp>
#include <bksge/core/render/d3d11/detail/index_buffer.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief	GeometryをD3D11で使えるように変換したクラス
 */
class Geometry
{
public:
	explicit Geometry(Device* device, bksge::Geometry const& geometry);

	~Geometry();

	void Draw(DeviceContext* device_context) const;

private:
	VertexBuffer               m_vertex_buffer;
	IndexBuffer                m_index_buffer;
	::D3D11_PRIMITIVE_TOPOLOGY m_primitive_topology;
	::UINT			           m_vertex_count;
	::UINT			           m_index_count;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_GEOMETRY_HPP
