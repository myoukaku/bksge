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
GlFilterMode(bksge::FilterMode mode)
{
	static std::unordered_map<bksge::FilterMode, ::GLint> const m =
	{
		{ bksge::FilterMode::kLinear,	GL_LINEAR },
		{ bksge::FilterMode::kNearest,	GL_NEAREST },
	};

	return m.at(mode);
}

}	// namespace detail

BKSGE_INLINE
FilterMode::FilterMode(bksge::FilterMode mode)
	: m_mode(detail::GlFilterMode(mode))
{}

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
