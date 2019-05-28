/**
 *	@file	gl_fill_mode_inl.hpp
 *
 *	@brief	ToGlFillMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_FILL_MODE_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_FILL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_fill_mode.hpp>
#include <bksge/render/fill_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLenum ToGlFillMode(FillMode mode)
{
	static std::unordered_map<FillMode, GLenum> const m =
	{
		{ FillMode::kSolid,		GL_FILL },
		{ FillMode::kWireframe,	GL_LINE },
	};

	return m.at(mode);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_FILL_MODE_INL_HPP
