/**
 *	@file	filter_mode_inl.hpp
 *
 *	@brief	FilterMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_FILTER_MODE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_FILTER_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/filter_mode.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/mipmap_mode.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLint
ToGlFilterMode(bksge::FilterMode mag_filter)
{
	switch (mag_filter)
	{
	case bksge::FilterMode::kNearest: return GL_NEAREST;
	case bksge::FilterMode::kLinear:  return GL_LINEAR;
	default: return GL_NEAREST;
	}
}

inline ::GLint
ToGlFilterMode(bksge::FilterMode min_filter, bksge::MipmapMode mip_filter)
{
	switch (min_filter)
	{
	case bksge::FilterMode::kNearest:
		switch (mip_filter)
		{
		case bksge::MipmapMode::kDisable: return GL_NEAREST;
		case bksge::MipmapMode::kNearest: return GL_NEAREST_MIPMAP_NEAREST;
		case bksge::MipmapMode::kLinear:  return GL_NEAREST_MIPMAP_LINEAR;
		}
		break;
	case bksge::FilterMode::kLinear:
		switch (mip_filter)
		{
		case bksge::MipmapMode::kDisable: return GL_LINEAR;
		case bksge::MipmapMode::kNearest: return GL_LINEAR_MIPMAP_NEAREST;
		case bksge::MipmapMode::kLinear:  return GL_LINEAR_MIPMAP_LINEAR;
		}
		break;
	}
	return GL_NEAREST;
}

}	// namespace detail

BKSGE_INLINE
FilterMode::FilterMode(bksge::FilterMode mag_filter)
	: m_mode(detail::ToGlFilterMode(mag_filter))
{
}

BKSGE_INLINE
FilterMode::FilterMode(
	bksge::FilterMode min_filter,
	bksge::MipmapMode mip_filter)
	: m_mode(detail::ToGlFilterMode(min_filter, mip_filter))
{
}

BKSGE_INLINE
FilterMode::operator ::GLint() const
{
	return m_mode;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_FILTER_MODE_INL_HPP
