/**
 *	@file	index_buffer.hpp
 *
 *	@brief	IndexBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INDEX_BUFFER_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INDEX_BUFFER_HPP

#include <bksge/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/dxgiformat.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief	D3D11でのインデックスバッファ
 */
class IndexBuffer
{
public:
	explicit IndexBuffer(Device* device, bksge::Geometry const& geometry);

	~IndexBuffer();

	void Bind(DeviceContext* device_context) const;

	bool enable(void) const;

private:
	ComPtr<::ID3D11Buffer> m_buffer;
	::DXGI_FORMAT          m_format = DXGI_FORMAT_UNKNOWN;
	bool                   m_enable = false;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/index_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_INDEX_BUFFER_HPP
