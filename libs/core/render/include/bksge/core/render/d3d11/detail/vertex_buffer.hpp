﻿/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_VERTEX_BUFFER_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_VERTEX_BUFFER_HPP

#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief	D3D11での頂点バッファ
 */
class VertexBuffer
{
public:
	explicit VertexBuffer(Device* device, bksge::Geometry const& geometry);

	~VertexBuffer();

	void Bind(DeviceContext* device_context) const;

private:
	// noncopyable
	VertexBuffer(VertexBuffer const&) = delete;
	VertexBuffer& operator=(VertexBuffer const&) = delete;

private:
	ComPtr<::ID3D11Buffer> m_buffer;
	::UINT                 m_stride = 0;
	::UINT                 m_offset = 0;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_VERTEX_BUFFER_HPP
