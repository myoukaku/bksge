/**
 *	@file	gl_wrap_mode_inl.hpp
 *
 *	@brief	ToGlWrapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_WRAP_MODE_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_WRAP_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_wrap_mode.hpp>
#include <bksge/render/wrap_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLint ToGlWrapMode(WrapMode mode)
{
	static std::unordered_map<WrapMode, GLint> const m =
	{
		{ WrapMode::kRepeat,	GL_REPEAT },
		{ WrapMode::kClamp,		GL_CLAMP_TO_EDGE },
		{ WrapMode::kBorder,	GL_CLAMP_TO_BORDER },
	};

	return m.at(mode);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_WRAP_MODE_INL_HPP
