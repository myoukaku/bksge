/**
 *	@file	wrap_mode_inl.hpp
 *
 *	@brief	WrapMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_WRAP_MODE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_WRAP_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/wrap_mode.hpp>
#include <bksge/core/render/wrap_mode.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLint
ToGlWrapMode(bksge::WrapMode wrap_mode)
{
	switch (wrap_mode)
	{
	case bksge::WrapMode::kRepeat: return GL_REPEAT;
	case bksge::WrapMode::kClamp:  return GL_CLAMP_TO_EDGE;
	case bksge::WrapMode::kBorder: return GL_CLAMP_TO_BORDER;
	}
	return GL_REPEAT;
}

}	// namespace detail

BKSGE_INLINE
WrapMode::WrapMode(bksge::WrapMode wrap_mode)
	: m_wrap_mode(detail::ToGlWrapMode(wrap_mode))
{}

BKSGE_INLINE
WrapMode::operator ::GLint() const
{
	return m_wrap_mode;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_WRAP_MODE_INL_HPP
