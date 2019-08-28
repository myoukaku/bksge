/**
 *	@file	wgl_context.hpp
 *
 *	@brief	WglContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_WGL_WGL_CONTEXT_HPP
#define BKSGE_RENDER_GL_DETAIL_WGL_WGL_CONTEXT_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/gl/detail/context.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	ContextのWindows版
 */
class WglContext : public Context
{
public:
	explicit WglContext(Window const& window);
	virtual ~WglContext();
	void SwapBuffers(void) override;
	void MakeCurrent(bool current) override;

private:
	::HWND		m_hwnd;
	::HDC		m_hdc;
	::HGLRC		m_hglrc;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/wgl/inl/wgl_context_inl.hpp>
#endif

#endif

#endif // BKSGE_RENDER_GL_DETAIL_WGL_WGL_CONTEXT_HPP
