/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INDEX_BUFFER_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INDEX_BUFFER_HPP

#include <bksge/core/render/d3d12/detail/fwd/index_buffer_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class IndexBuffer
{
public:
	explicit IndexBuffer(Device* device, bksge::Geometry const& geometry);

	~IndexBuffer();

	void SetEnable(CommandList* command_list);
	void Draw(CommandList* command_list);

	bool enable(void) const;

private:
	// noncopyable
	IndexBuffer(IndexBuffer const&) = delete;
	IndexBuffer& operator=(IndexBuffer const&) = delete;

private:
	bool						m_enable;
	ComPtr<ID3D12ResourceN>		m_resource;
	::D3D12_INDEX_BUFFER_VIEW	m_view;
	::UINT						m_count;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/index_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INDEX_BUFFER_HPP
