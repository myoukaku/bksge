/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_GEOMETRY_HPP
#define BKSGE_RENDER_D3D11_DETAIL_GEOMETRY_HPP

#include <bksge/render/d3d11/detail/fwd/geometry_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/render/d3d11/detail/vertex_buffer.hpp>
#include <bksge/render/d3d11/detail/index_buffer.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

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
	::D3D11_PRIMITIVE_TOPOLOGY m_primitive;
	::UINT			           m_vertex_count;
	::UINT			           m_index_count;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_GEOMETRY_HPP
