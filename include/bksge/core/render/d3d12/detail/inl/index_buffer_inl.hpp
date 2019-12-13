/**
 *	@file	index_buffer_inl.hpp
 *
 *	@brief	IndexBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_INDEX_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_INDEX_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/index_buffer.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/command_list.hpp>
#include <bksge/core/render/d3d12/detail/type_enum.hpp>
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
IndexBuffer::IndexBuffer(Device* device, bksge::Geometry const& geometry)
	: m_enable(false)
{
	auto const src  = geometry.index_array_data();
	auto const size = geometry.index_array_bytes();

	if (src != nullptr && size != 0u)
	{
		m_enable = true;

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

		// Describe the index buffer view.
		m_view.BufferLocation = m_resource->GetGPUVirtualAddress();
		m_view.Format = TypeEnum(geometry.index_array_type());
		m_view.SizeInBytes = static_cast<::UINT>(size);

		m_count = static_cast<::UINT>(geometry.index_array_count());
	}
}

BKSGE_INLINE
IndexBuffer::~IndexBuffer()
{
}

BKSGE_INLINE void
IndexBuffer::SetEnable(CommandList* command_list)
{
	command_list->IASetIndexBuffer(&m_view);
}

BKSGE_INLINE void
IndexBuffer::Draw(CommandList* command_list)
{
	command_list->DrawIndexedInstanced(m_count, 1, 0, 0, 0);
}

BKSGE_INLINE bool
IndexBuffer::enable(void) const
{
	return m_enable;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_INDEX_BUFFER_INL_HPP
