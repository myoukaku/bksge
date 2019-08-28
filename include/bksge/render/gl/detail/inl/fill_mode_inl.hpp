/**
 *	@file	fill_mode_inl.hpp
 *
 *	@brief	FillMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_FILL_MODE_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_FILL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/fill_mode.hpp>
#include <bksge/render/fill_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
GlFillMode(bksge::FillMode mode)
{
	static std::unordered_map<bksge::FillMode, ::GLenum> const m =
	{
		{ bksge::FillMode::kSolid,		GL_FILL },
		{ bksge::FillMode::kWireframe,	GL_LINE },
	};

	return m.at(mode);
}

}	// namespace detail

BKSGE_INLINE
FillMode::FillMode(bksge::FillMode fill_mode)
	: m_fill_mode(detail::GlFillMode(fill_mode))
{}

BKSGE_INLINE
FillMode::operator ::GLenum() const
{
	return m_fill_mode;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_FILL_MODE_INL_HPP
