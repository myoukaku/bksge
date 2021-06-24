/**
 *	@file	dxgi_format.hpp
 *
 *	@brief	DXGIFormat クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DXGI_DXGI_FORMAT_HPP
#define BKSGE_CORE_RENDER_DXGI_DXGI_FORMAT_HPP

#include <bksge/core/render/d3d_common/dxgiformat.hpp>
#include <bksge/core/render/texture_format.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class DXGIFormat
{
public:
	explicit DXGIFormat(bksge::TextureFormat format);

	operator ::DXGI_FORMAT() const;

private:
	::DXGI_FORMAT	m_format;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/dxgi/inl/dxgi_format_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DXGI_DXGI_FORMAT_HPP
