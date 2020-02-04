/**
 *	@file	depth_stencil.hpp
 *
 *	@brief	DepthStencil クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_STENCIL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_STENCIL_HPP

#include <bksge/core/render/d3d12/detail/fwd/depth_stencil_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class DepthStencil
{
public:
	explicit DepthStencil(Device* device, ::UINT width, ::UINT height);

	~DepthStencil();

	::D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(void) const;

private:
	// noncopyable
	DepthStencil(DepthStencil const&) = delete;
	DepthStencil& operator=(DepthStencil const&) = delete;

private:
	ComPtr<ID3D12ResourceN>				m_resource;
	ComPtr<::ID3D12DescriptorHeap>		m_descriptor_heap;
//	::UINT								m_descriptor_size;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/depth_stencil_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_STENCIL_HPP
