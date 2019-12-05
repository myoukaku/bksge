/**
 *	@file	constant_buffer_inl.hpp
 *
 *	@brief	ConstantBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/constant_buffer.hpp>
#include <bksge/render/d3d12/detail/device.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/throw_if_failed.hpp>
#include <bksge/cmath/round_up.hpp>
#include <cstdint>
#include <vector>
#include <cstring>	// memcpy

//#include <iostream>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
ConstantBuffer::ConstantBuffer(
	Device* device,
	::UINT	size)
{
	size = bksge::round_up(size, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);

	// Create resource.
	{
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
		desc.SampleDesc       = {1, 0};
		desc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags            = D3D12_RESOURCE_FLAG_NONE;

		m_resource = device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr);
	}

	// Map the constant buffer. We don't unmap this until the app closes.
	// Keeping things mapped for the lifetime of the resource is okay.
	m_resource->Map(0, nullptr, reinterpret_cast<void**>(&m_mapped_resource));
}

BKSGE_INLINE
ConstantBuffer::~ConstantBuffer()
{
}

BKSGE_INLINE ConstantBuffer::Subresource
ConstantBuffer::AssignSubresource(std::size_t size)
{
	size = bksge::round_up(size, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);

	ComPtr<::ID3D12Device> device;
	ThrowIfFailed(m_resource->GetDevice(IID_PPV_ARGS(&device)));

	auto offset = m_offset;

	if (m_offset + size >= GetSizeInBytes())
	{
		m_offset = 0;
	}
	else
	{
		m_offset += size;
	}

	return
	{
		device,
		static_cast<::UINT>(size),
		m_resource->GetGPUVirtualAddress() + offset,
		m_mapped_resource + offset
	};
}

BKSGE_INLINE
ConstantBuffer::Subresource::Subresource(
	ComPtr<::ID3D12Device> const& device,
	::UINT						  size,
	::D3D12_GPU_VIRTUAL_ADDRESS	  gpu_virtual_address,
	std::uint8_t*				  mapped_resource)
	: m_device(device)
	, m_size(size)
	, m_gpu_virtual_address(gpu_virtual_address)
	, m_mapped_resource(mapped_resource)
{
}

BKSGE_INLINE
ConstantBuffer::Subresource::~Subresource()
{
}

BKSGE_INLINE void
ConstantBuffer::Subresource::Update(std::vector<std::uint8_t> const& buffer)
{
	std::memcpy(
		m_mapped_resource,
		buffer.data(),
		buffer.size());
}

BKSGE_INLINE void
ConstantBuffer::Subresource::CreateView(::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	::D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
	desc.BufferLocation = m_gpu_virtual_address;
	desc.SizeInBytes    = m_size;
	m_device->CreateConstantBufferView(&desc, dest);
}

#if 0
BKSGE_INLINE void
ConstantBuffer::Update(std::vector<std::uint8_t> const& buffer)
{
	std::memcpy(
		m_mapped_resource,
		buffer.data(),
		buffer.size());
}

BKSGE_INLINE void
ConstantBuffer::CreateView(::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	ComPtr<::ID3D12Device> device;
	ThrowIfFailed(m_resource->GetDevice(IID_PPV_ARGS(&device)));

	::D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};
	desc.BufferLocation = m_resource->GetGPUVirtualAddress();
	desc.SizeInBytes    = GetSizeInBytes();
	device->CreateConstantBufferView(&desc, dest);
}
#endif

BKSGE_INLINE ::UINT
ConstantBuffer::GetSizeInBytes(void) const
{
	auto const desc = m_resource->GetDesc();
	return static_cast<::UINT>(desc.Width);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_CONSTANT_BUFFER_INL_HPP
