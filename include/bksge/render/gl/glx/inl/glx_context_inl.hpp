/**
 *	@file	glx_context_inl.hpp
 *
 *	@brief	GlxContext の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GLX_INL_GLX_CONTEXT_INL_HPP
#define BKSGE_RENDER_GL_GLX_INL_GLX_CONTEXT_INL_HPP

#include <bksge/config.hpp>
#if 1//defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/glx/glx_context.hpp>
#include <bksge/window/window.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlxContext::GlxContext(Window const& window)
{
	(void)window;
}

BKSGE_INLINE
GlxContext::~GlxContext()
{
}

BKSGE_INLINE
void GlxContext::SwapBuffers(void)
{
}

BKSGE_INLINE
void GlxContext::MakeCurrent(bool current)
{
	(void)current;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_RENDER_GL_GLX_INL_GLX_CONTEXT_INL_HPP
