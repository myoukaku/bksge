/**
 *	@file	render_texture_inl.hpp
 *
 *	@brief	RenderTexture の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_RENDER_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_INL_RENDER_TEXTURE_INL_HPP

#include <bksge/core/render/render_texture.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
RenderTexture::RenderTexture(
	TextureFormat format, ExtentType const& extent)
	: m_format(format)
	, m_extent(extent)
{}

BKSGE_INLINE TextureFormat
RenderTexture::format(void) const
{
	return m_format;
}

BKSGE_INLINE auto
RenderTexture::extent(void) const
-> ExtentType const&
{
	return m_extent;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_RENDER_TEXTURE_INL_HPP
