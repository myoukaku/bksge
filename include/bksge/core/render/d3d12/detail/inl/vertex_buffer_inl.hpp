/**
 *	@file	vertex_buffer_inl.hpp
 *
 *	@brief	VertexBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_VERTEX_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_VERTEX_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/vertex_buffer.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/command_list.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>
#include <bksge/core/render/geometry.hpp>
#include <cstring>	// memcpy

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
VertexBuffer::VertexBuffer(Device* device, bksge::Geometry const& geometry)
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
VertexBuffer::~VertexBuffer()
{
}

BKSGE_INLINE void
VertexBuffer::SetEnable(CommandList* command_list)
{
	command_list->IASetVertexBuffers(0, 1, &m_view);
}

BKSGE_INLINE void
VertexBuffer::Draw(CommandList* command_list)
{
	command_list->DrawInstanced(m_count, 1, 0, 0);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_VERTEX_BUFFER_INL_HPP
