/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_VERTEX_BUFFER_HPP
#define BKSGE_RENDER_D3D12_DETAIL_VERTEX_BUFFER_HPP

#include <bksge/render/d3d12/detail/fwd/vertex_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class VertexBuffer
{
public:
	explicit VertexBuffer(Device* device, bksge::Geometry const& geometry);

	~VertexBuffer();

	void SetEnable(CommandList* command_list);
	void Draw(CommandList* command_list);

private:
	ComPtr<::ID3D12Resource>	m_resource;
	::D3D12_VERTEX_BUFFER_VIEW	m_view;
	::UINT						m_count = 0;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_VERTEX_BUFFER_HPP
