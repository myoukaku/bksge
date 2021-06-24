/**
 *	@file	wgl_context.hpp
 *
 *	@brief	WglContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_WGL_WGL_CONTEXT_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_WGL_WGL_CONTEXT_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

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
 *	@brief	ContextのWindows版
 */
class WglContext : public Context
{
public:
	explicit WglContext(Window const& window);
	virtual ~WglContext();
	void SwapBuffers(void) override;
	void MakeCurrent(bool current) override;

	bksge::Extent2f extent(void) const override;

private:
	::HWND		m_hwnd;
	::HDC		m_hdc;
	::HGLRC		m_hglrc;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/wgl/inl/wgl_context_inl.hpp>
#endif

#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_WGL_WGL_CONTEXT_HPP
