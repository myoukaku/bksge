/**
 *	@file	wgl_context.hpp
 *
 *	@brief	WglContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_WGL_WGL_CONTEXT_HPP
#define BKSGE_RENDER_GL_WGL_WGL_CONTEXT_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/gl/gl_context.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	GlContextのWindows版
 */
class WglContext : public GlContext
{
public:
	explicit WglContext(Window const& window);
	virtual ~WglContext();
	virtual void SwapBuffers(void) override;
	virtual void MakeCurrent(bool current) override;

private:
	HWND	m_hwnd;
	HDC		m_hdc;
	HGLRC	m_hglrc;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/wgl/inl/wgl_context_inl.hpp>
#endif

#endif

#endif // BKSGE_RENDER_GL_WGL_WGL_CONTEXT_HPP
