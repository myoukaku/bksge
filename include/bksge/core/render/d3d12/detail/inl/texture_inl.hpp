/**
 *	@file	texture_inl.hpp
 *
 *	@brief	Texture クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/texture.hpp>
#include <bksge/core/render/d3d12/detail/device.hpp>
#include <bksge/core/render/d3d12/detail/command_list.hpp>
#include <bksge/core/render/d3d12/detail/command_queue.hpp>
#include <bksge/core/render/d3d12/detail/fence.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/throw_if_failed.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::DXGI_FORMAT
ToDXGIPixelFormat(bksge::TextureFormat format)
{
	// TODO
	(void)format;
	return DXGI_FORMAT_R8G8B8A8_UNORM;
}

}	// namespace detail

inline void MemcpySubresource(
	::D3D12_MEMCPY_DEST const* dst,
	::D3D12_SUBRESOURCE_DATA const* src,
	::SIZE_T row_size_in_bytes,
	::UINT num_rows,
	::UINT num_slices)
{
	for (::UINT z = 0; z < num_slices; ++z)
	{
		auto dst_slice = reinterpret_cast<::BYTE*>(dst->pData) + dst->SlicePitch * z;
		auto src_slice = reinterpret_cast<::BYTE const*>(src->pData) + src->SlicePitch * z;
		for (::UINT y = 0; y < num_rows; ++y)
		{
			std::memcpy(
				dst_slice + dst->RowPitch * y,
				src_slice + src->RowPitch * y,
				row_size_in_bytes);
		}
	}
}

inline void UpdateSubresource(
	Device* device,
	CommandList* command_list,
	CommandQueue* command_queue,
	Fence* fence,
	ID3D12ResourceN* destination_resource,
	bksge::Texture const& src_texture)
{
	auto const mipmap_count = src_texture.mipmap_count();
	auto const num_subresources = mipmap_count;
	auto const destination_desc = destination_resource->GetDesc();
	std::vector<::D3D12_PLACED_SUBRESOURCE_FOOTPRINT> footprints;
	std::vector<::UINT> num_rows;
	std::vector<::UINT64> row_size_in_bytes;
	::UINT64 required_size = 0;
	footprints.resize(num_subresources);
	num_rows.resize(num_subresources);
	row_size_in_bytes.resize(num_subresources);
	device->GetCopyableFootprints(
		&destination_desc,
		0,	// first_subresource
		static_cast<::UINT>(num_subresources),
		0,
		footprints.data(),
		num_rows.data(),
		row_size_in_bytes.data(),
		&required_size);

	::D3D12_HEAP_PROPERTIES prop = {};
	prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	prop.CreationNodeMask     = 1;
	prop.VisibleNodeMask      = 1;

	::D3D12_RESOURCE_DESC desc = {};
	desc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Alignment          = 0;
	desc.Width              = required_size;
	desc.Height             = 1;
	desc.DepthOrArraySize   = 1;
	desc.MipLevels          = 1;
	desc.Format             = DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count   = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.Flags              = D3D12_RESOURCE_FLAG_NONE;

	ComPtr<ID3D12ResourceN> intermediate_resource =
		device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr);

	::BYTE* data;
	auto hr = intermediate_resource->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(hr))
	{
		return;
	}

	auto const format = src_texture.format();
	auto src_ptr = src_texture.data();
	auto src_width  = src_texture.width();
	auto src_height = src_texture.height();

	for (bksge::size_t i = 0; i < num_subresources; ++i)
	{
		//if (row_size_in_bytes > ::SIZE_T(-1))
		//{
		//	return;
		//}

		::D3D12_SUBRESOURCE_DATA src_data{};
		src_data.pData = src_ptr;
		src_data.RowPitch = static_cast<::UINT>(GetStrideInBytes(format, src_width));
		src_data.SlicePitch = src_data.RowPitch * src_height;

		::D3D12_MEMCPY_DEST dst_data{};
		dst_data.pData      = data + footprints[i].Offset;
		dst_data.RowPitch   = footprints[i].Footprint.RowPitch;
		dst_data.SlicePitch = dst_data.RowPitch * ::SIZE_T(num_rows[i]);

		MemcpySubresource(
			&dst_data,
			&src_data,
			static_cast<::SIZE_T>(row_size_in_bytes[i]),
			num_rows[i],
			footprints[i].Footprint.Depth);

		src_ptr += GetSizeInBytes(format, src_width, src_height);
		src_width  = bksge::max(src_width  / 2, 1u);
		src_height = bksge::max(src_height / 2, 1u);
	}
	intermediate_resource->Unmap(0, nullptr);

	command_list->Reset(0);

	//if (destination_desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
	//{
	//	command_list->CopyBufferRegion(
	//		destination_resource,
	//		0,
	//		intermediate_resource.Get(),
	//		footprints[0].Offset,
	//		footprints[0].Footprint.Width);
	//}
	//else
	{
		for (bksge::size_t i = 0; i < num_subresources; ++i)
		{
			::D3D12_TEXTURE_COPY_LOCATION dst;
			::D3D12_TEXTURE_COPY_LOCATION src;

			dst.pResource        = destination_resource;
			dst.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
			dst.SubresourceIndex = static_cast<::UINT>(i);

			src.pResource       = intermediate_resource.Get();
			src.Type            = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
			src.PlacedFootprint = footprints[i];

			command_list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
		}
	}

	command_list->ResourceBarrier(
		destination_resource,
		D3D12_RESOURCE_STATE_COPY_DEST,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	command_list->Close();
	command_queue->ExecuteCommandLists(command_list);
	fence->WaitForGpu(command_queue, 0);
}

BKSGE_INLINE
Texture::Texture(
	Device* device,
	CommandList* command_list,
	CommandQueue* command_queue,
	Fence* fence,
	bksge::Texture const& texture)
{
	::D3D12_HEAP_PROPERTIES prop = {};
	prop.Type                 = D3D12_HEAP_TYPE_DEFAULT;
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	prop.CreationNodeMask     = 1;
	prop.VisibleNodeMask      = 1;

	::D3D12_RESOURCE_DESC desc = {};
	desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment          = 0;
	desc.Width              = texture.width();
	desc.Height             = texture.height();
	desc.DepthOrArraySize   = 1;
	desc.MipLevels          = static_cast<::UINT16>(texture.mipmap_count());
	desc.Format             = detail::ToDXGIPixelFormat(texture.format());
	desc.SampleDesc.Count   = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags              = D3D12_RESOURCE_FLAG_NONE;

	m_resource = device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_COPY_DEST,//D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr);

	UpdateSubresource(device, command_list, command_queue, fence, m_resource.Get(), texture);
}

BKSGE_INLINE
Texture::~Texture()
{
}

BKSGE_INLINE void
Texture::CreateView(Device* device, ::D3D12_CPU_DESCRIPTOR_HANDLE dest)
{
	auto const desc = m_resource->GetDesc();

	::D3D12_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
	srv_desc.Format                        = desc.Format;
	srv_desc.ViewDimension                 = D3D12_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Shader4ComponentMapping       = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srv_desc.Texture2D.MostDetailedMip     = 0;
	srv_desc.Texture2D.MipLevels           = desc.MipLevels;
	srv_desc.Texture2D.PlaneSlice          = 0;
	srv_desc.Texture2D.ResourceMinLODClamp = 0;

	device->CreateShaderResourceView(m_resource.Get(), &srv_desc, dest);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_TEXTURE_INL_HPP
