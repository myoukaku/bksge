/**
 *	@file	d3d12_vertex_buffer_inl.hpp
 *
 *	@brief	D3D12VertexBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_VERTEX_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_VERTEX_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_vertex_buffer.hpp>
#include <bksge/render/d3d12/d3d12_device.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/render/geometry.hpp>
#include <cstring>	// memcpy

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12VertexBuffer::D3D12VertexBuffer(Geometry const& geometry, D3D12Device* device)
{
	auto const src    = geometry.vertex_array_data();
	auto const size   = geometry.vertex_array_bytes();
	auto const stride = geometry.vertex_layout().total_bytes();

	::D3D12_HEAP_PROPERTIES prop = {};
	prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	prop.CreationNodeMask     = 1;
	prop.VisibleNodeMask      = 1;

	::D3D12_RESOURCE_DESC desc = {};
	desc.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Alignment        = 0;
	desc.Width            = size;
	desc.Height           = 1;
	desc.DepthOrArraySize = 1;
	desc.MipLevels        = 1;
	desc.Format           = DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.Flags            = D3D12_RESOURCE_FLAG_NONE;

	m_resource = device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr);

	// バッファにコピー
	::UINT8* p;
	ThrowIfFailed(m_resource->Map(0, nullptr, reinterpret_cast<void**>(&p)));
	std::memcpy(p, src, size);
	m_resource->Unmap(0, nullptr);

	// Viewの初期化
	m_view.BufferLocation = m_resource->GetGPUVirtualAddress();
	m_view.SizeInBytes    = static_cast<::UINT>(size);
	m_view.StrideInBytes  = static_cast<::UINT>(stride);

	m_count = static_cast<::UINT>(geometry.vertex_array_count());
}

BKSGE_INLINE
D3D12VertexBuffer::~D3D12VertexBuffer()
{
}

BKSGE_INLINE void
D3D12VertexBuffer::SetEnable(D3D12CommandList* command_list)
{
	command_list->IASetVertexBuffers(0, 1, &m_view);
}

BKSGE_INLINE void
D3D12VertexBuffer::Draw(D3D12CommandList* command_list)
{
	command_list->DrawInstanced(m_count, 1, 0, 0);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_VERTEX_BUFFER_INL_HPP
