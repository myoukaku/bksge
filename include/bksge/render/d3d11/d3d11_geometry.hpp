/**
 *	@file	d3d11_geometry.hpp
 *
 *	@brief	D3D11Geometry の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_GEOMETRY_HPP
#define BKSGE_RENDER_D3D11_D3D11_GEOMETRY_HPP

#include <bksge/render/d3d11/fwd/d3d11_geometry_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_context_fwd.hpp>
#include <bksge/render/d3d11/d3d11_vertex_buffer.hpp>
#include <bksge/render/d3d11/d3d11_index_buffer.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	GeometryをD3D11で使えるように変換したクラス
 */
class D3D11Geometry
{
public:
	explicit D3D11Geometry(D3D11Device* device, Geometry const& geometry);

	~D3D11Geometry();

	void Draw(D3D11DeviceContext* device_context) const;

private:
	D3D11VertexBuffer	       m_vertex_buffer;
	D3D11IndexBuffer	       m_index_buffer;
	::D3D11_PRIMITIVE_TOPOLOGY m_primitive;
	::UINT			           m_vertex_count;
	::UINT			           m_index_count;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_geometry_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_GEOMETRY_HPP
