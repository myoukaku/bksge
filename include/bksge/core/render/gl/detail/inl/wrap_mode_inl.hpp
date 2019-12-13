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
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLint
GlWrapMode(bksge::WrapMode mode)
{
	static std::unordered_map<bksge::WrapMode, ::GLint> const m =
	{
		{ bksge::WrapMode::kRepeat,	GL_REPEAT },
		{ bksge::WrapMode::kClamp,		GL_CLAMP_TO_EDGE },
		{ bksge::WrapMode::kBorder,	GL_CLAMP_TO_BORDER },
	};

	return m.at(mode);
}

}	// namespace detail

BKSGE_INLINE
WrapMode::WrapMode(bksge::WrapMode wrap_mode)
	: m_wrap_mode(detail::GlWrapMode(wrap_mode))
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
