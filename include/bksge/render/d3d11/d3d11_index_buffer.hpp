/**
 *	@file	d3d11_index_buffer.hpp
 *
 *	@brief	D3D11IndexBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_INDEX_BUFFER_HPP
#define BKSGE_RENDER_D3D11_D3D11_INDEX_BUFFER_HPP

#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	D3D11でのインデックスバッファ
 */
class D3D11IndexBuffer
{
public:
	D3D11IndexBuffer(D3D11Renderer* renderer, Geometry const& geometry);

	~D3D11IndexBuffer();

	void Bind(D3D11Renderer* renderer) const;

	bool enable(void) const;

private:
	ComPtr<::ID3D11Buffer> m_buffer;
	::DXGI_FORMAT          m_format = DXGI_FORMAT_UNKNOWN;
	bool                   m_enable = false;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_index_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_INDEX_BUFFER_HPP
