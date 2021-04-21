/**
 *	@file	egl_context.hpp
 *
 *	@brief	EglContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_EGL_EGL_CONTEXT_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_EGL_EGL_CONTEXT_HPP

#include <bksge/fnd/config.hpp>
#if 0//BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/context.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/window/fwd/window_fwd.hpp>
#include <bksge/core/math/fwd/extent2_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	ContextのEGL版
 */
class EglContext : public Context
{
public:
	explicit EglContext(Window const& window);
	virtual ~EglContext();
	void SwapBuffers(void) override;
	void MakeCurrent(bool current) override;

	bksge::Extent2f extent(void) const override;

private:
	::EGLDisplay	m_display = EGL_NO_DISPLAY;
	::EGLSurface	m_surface = EGL_NO_SURFACE;
	::EGLContext	m_context = EGL_NO_CONTEXT;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/egl/inl/egl_context_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_EGL_EGL_CONTEXT_HPP
