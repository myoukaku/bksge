/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INDEX_BUFFER_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INDEX_BUFFER_HPP

#include <bksge/render/d3d12/detail/fwd/index_buffer_fwd.hpp>
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

class IndexBuffer
{
public:
	IndexBuffer(bksge::Geometry const& geometry, Device* device);

	~IndexBuffer();

	void SetEnable(CommandList* command_list);
	void Draw(CommandList* command_list);

	bool enable(void) const;

private:
	bool						m_enable;
	ComPtr<::ID3D12Resource>	m_resource;
	::D3D12_INDEX_BUFFER_VIEW	m_view;
	::UINT						m_count;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/index_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_INDEX_BUFFER_HPP
