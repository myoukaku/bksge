/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	FillMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_FILL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_FILL_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/fill_mode.hpp>
#include <bksge/core/render/fill_mode.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlFillMode(bksge::FillMode fill_mode)
{
	switch (fill_mode)
	{
	case bksge::FillMode::kSolid:     return GL_FILL;
	case bksge::FillMode::kWireframe: return GL_LINE;
	}
	return GL_FILL;
}

}	// namespace detail

BKSGE_INLINE
FillMode::FillMode(bksge::FillMode fill_mode)
	: m_fill_mode(detail::ToGlFillMode(fill_mode))
{}

BKSGE_INLINE
FillMode::operator ::GLenum() const
{
	return m_fill_mode;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_FILL_MODE_INL_HPP
