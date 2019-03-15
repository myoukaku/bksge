/**
 *	@file	d3d11_vertex_buffer.hpp
 *
 *	@brief	D3D11VertexBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_VERTEX_BUFFER_HPP
#define BKSGE_RENDER_D3D11_D3D11_VERTEX_BUFFER_HPP

#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d11/com_ptr.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	D3D11での頂点バッファ
 */
class D3D11VertexBuffer
{
public:
	D3D11VertexBuffer(D3D11Renderer* renderer, Geometry const& geometry);

	~D3D11VertexBuffer();

	void Bind(D3D11Renderer* renderer) const;

private:
	ComPtr<ID3D11Buffer> m_buffer;
	UINT                 m_stride = 0;
	UINT                 m_offset = 0;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_VERTEX_BUFFER_HPP
