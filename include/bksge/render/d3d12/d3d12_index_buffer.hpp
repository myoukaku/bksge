/**
 *	@file	d3d12_index_buffer.hpp
 *
 *	@brief	D3D12IndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_INDEX_BUFFER_HPP
#define BKSGE_RENDER_D3D12_D3D12_INDEX_BUFFER_HPP

#include <bksge/render/d3d12/fwd/d3d12_index_buffer_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

class D3D12IndexBuffer
{
public:
	D3D12IndexBuffer(Geometry const& geometry, D3D12Device* device);

	~D3D12IndexBuffer();

	void SetEnable(D3D12CommandList* command_list);
	void Draw(D3D12CommandList* command_list);

	bool enable(void) const;

private:
	bool						m_enable;
	ComPtr<::ID3D12Resource>	m_resource;
	::D3D12_INDEX_BUFFER_VIEW	m_view;
	::UINT						m_count;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_index_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_INDEX_BUFFER_HPP
