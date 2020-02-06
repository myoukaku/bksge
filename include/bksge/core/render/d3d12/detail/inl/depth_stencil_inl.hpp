/**
 *	@file	depth_stencil_inl.hpp
 *
 *	@brief	DepthStencil クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_STENCIL_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_STENCIL_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/depth_stencil.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
DepthStencil::DepthStencil(Device* device, ::UINT width, ::UINT height)
{
	::DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	{
		// Describe and create a depth stencil view (DSV) descriptor heap.
		::D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = 1;
		desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		m_descriptor_heap = device->CreateDescriptorHeap(desc);
	}

	// Create resource.
	{
		::D3D12_HEAP_PROPERTIES prop = {};
		prop.Type                 = D3D12_HEAP_TYPE_DEFAULT;
		prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask     = 1;
		prop.VisibleNodeMask      = 1;

		::D3D12_RESOURCE_DESC desc = {};
		desc.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		desc.Alignment        = 0;
		desc.Width            = width;
		desc.Height           = height;
		desc.DepthOrArraySize = 1;
		desc.MipLevels        = 0;
		desc.Format           = format;
		desc.SampleDesc       = {1, 0};
		desc.Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		desc.Flags            = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		::D3D12_CLEAR_VALUE clear_value;
		clear_value.Format               = format;
		clear_value.DepthStencil.Depth   = 1.0f;
		clear_value.DepthStencil.Stencil = 0;

		m_resource = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&clear_value);
	}

	// Create the depth stencil view.
	{
		::D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};
		desc.Format        = format;
		desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		desc.Flags         = D3D12_DSV_FLAG_NONE;

		device->CreateDepthStencilView(m_resource.Get(), &desc, m_descriptor_heap->GetCPUDescriptorHandleForHeapStart());
	}
}

BKSGE_INLINE
DepthStencil::~DepthStencil()
{
}

BKSGE_INLINE ::D3D12_CPU_DESCRIPTOR_HANDLE
DepthStencil::GetHandle(void) const
{
	return m_descriptor_heap->GetCPUDescriptorHandleForHeapStart();
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_STENCIL_INL_HPP
