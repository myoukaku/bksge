/**
 *	@file	egl_context_inl.hpp
 *
 *	@brief	EglContext の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_EGL_INL_EGL_CONTEXT_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_EGL_INL_EGL_CONTEXT_INL_HPP

#include <bksge/core/render/config.hpp>
#if 0//BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/egl/egl_context.hpp>
#include <bksge/core/window/window.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
EglContext::EglContext(Window const& window)
{
	auto hwnd = window.handle();
	auto hdc = ::GetDC(hwnd);

	// GL用ディスプレイを作成
	m_display = ::eglGetDisplay(hdc);
	if (m_display == EGL_NO_DISPLAY)
	{
		// 失敗した時用
		m_display = ::eglGetDisplay((::EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}

	// GLを初期化する
	::EGLint major_version;
	::EGLint minor_version;
	if (!::eglInitialize(m_display, &major_version, &minor_version))
	{
		// TODO エラー
	}

	// APIをバインドする
	::eglBindAPI(EGL_OPENGL_ES_API);

	// コンフィグ選択
	::EGLint const config_attribs[] =
	{
		EGL_LEVEL,             0,
		EGL_SURFACE_TYPE,      EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,   EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE, EGL_FALSE,
		EGL_DEPTH_SIZE,        EGL_DONT_CARE,
		EGL_NONE
	};

	::EGLConfig config;
	::EGLint num_config;
	if (!::eglChooseConfig(m_display, config_attribs, &config, 1, &num_config) || (num_config != 1))
	{
		// TODO エラー
	}

	// サーフェイスを作成する
	::EGLint surface_attributes[] = { EGL_NONE };
	m_surface = ::eglCreateWindowSurface(m_display, config, hwnd, surface_attributes);
	if (m_surface == EGL_NO_SURFACE)
	{
		// TODO エラー
	}

	// コンテキストを作成する
	::EGLint context_attribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	m_context = ::eglCreateContext(m_display, config, NULL, context_attribs);
	//if (!TestEGLError(hWnd, "eglCreateContext"))
	//{
	//	return false;
	//}

	MakeCurrent(true);
	::eglSwapInterval(m_display, 1);
}

BKSGE_INLINE
EglContext::~EglContext()
{
	MakeCurrent(false);
	::eglDestroySurface(m_display, m_surface);
	::eglDestroyContext(m_display, m_context);
	::eglTerminate(m_display);
}

BKSGE_INLINE void
EglContext::SwapBuffers(void)
{
	::eglSwapBuffers(m_display, m_surface);
}

BKSGE_INLINE void
EglContext::MakeCurrent(bool current)
{
	if (current)
	{
		::eglMakeCurrent(m_display, m_surface, m_surface, m_context);
	}
	else
	{
		::eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	}
}

BKSGE_INLINE bksge::Extent2f
EglContext::extent(void) const
{
	//::RECT rect;
	//::GetClientRect(m_hwnd, &rect);
	//return {
	//	static_cast<float>(rect.right - rect.left),
	//	static_cast<float>(rect.bottom - rect.top)
	//};

	return {};
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_EGL_INL_EGL_CONTEXT_INL_HPP
