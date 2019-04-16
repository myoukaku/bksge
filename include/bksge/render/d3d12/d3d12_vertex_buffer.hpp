﻿/**
 *	@file	d3d12_vertex_buffer.hpp
 *
 *	@brief	D3D12VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_VERTEX_BUFFER_HPP
#define BKSGE_RENDER_D3D12_D3D12_VERTEX_BUFFER_HPP

#include <bksge/render/d3d12/fwd/d3d12_vertex_buffer_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

class D3D12VertexBuffer
{
public:
	D3D12VertexBuffer(Geometry const& geometry, D3D12Device* device);

	~D3D12VertexBuffer();

	void SetEnable(D3D12CommandList* command_list);
	void Draw(D3D12CommandList* command_list);

private:
	ComPtr<::ID3D12Resource>	m_resource;
	::D3D12_VERTEX_BUFFER_VIEW	m_view;
	::UINT						m_count = 0;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_VERTEX_BUFFER_HPP
