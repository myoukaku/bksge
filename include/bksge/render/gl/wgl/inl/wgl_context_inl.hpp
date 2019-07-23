/**
 *	@file	wgl_context_inl.hpp
 *
 *	@brief	WglContext の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_WGL_INL_WGL_CONTEXT_INL_HPP
#define BKSGE_RENDER_GL_WGL_INL_WGL_CONTEXT_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/wgl/wgl_context.hpp>
#include <bksge/render/gl/wgl/wglext.hpp>
#include <bksge/window/window.hpp>

#if defined(_MSC_VER)
#	pragma comment(lib, "OpenGL32.lib")
#endif

namespace bksge
{

namespace render
{

namespace wgl_context_detail
{

///////////////////////////////////////////////////////////////////////////////
//
//	非メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
inline void SetPixelFormat(HDC hdc, int color_depth)
{
	PIXELFORMATDESCRIPTOR const pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		(BYTE)color_depth, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24, //Number of bits for the depthbuffer
		8, //Number of bits for the stencilbuffer
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int const format = ::ChoosePixelFormat(hdc, &pfd);

	if (format == 0)
	{
		return; // 該当するピクセルフォーマットが無い
	}

	// OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
	if (!::SetPixelFormat(hdc, format, &pfd))
	{
		return; // DCへフォーマットを設定するのに失敗
	}
}

}	// namespace wgl_context_detail

///////////////////////////////////////////////////////////////////////////////
//
//	メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
WglContext::WglContext(Window const& window)
	: m_hwnd(nullptr)
	, m_hdc(nullptr)
	, m_hglrc(nullptr)
{
	m_hwnd = window.handle();
	m_hdc = ::GetDC(m_hwnd);
	wgl_context_detail::SetPixelFormat(m_hdc, 32);

	// 仮のGLコンテキストの作成
	auto hglrc_dummy = ::wglCreateContext(m_hdc);
	::wglMakeCurrent(m_hdc, hglrc_dummy);

	// 使用する OpenGL のバージョンとプロファイルの指定
	static const int att[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_DEBUG_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,
	};

	// 使用するGLコンテキストの作成
	m_hglrc = ::wglCreateContextAttribsARB(m_hdc, NULL, att);
	::wglMakeCurrent(m_hdc, m_hglrc);

	// 仮のGLコンテキストの削除
	::wglDeleteContext(hglrc_dummy);
}

BKSGE_INLINE
WglContext::~WglContext()
{
//	MakeCurrent(false);
	::wglDeleteContext(m_hglrc);
	::ReleaseDC(m_hwnd, m_hdc);
}

BKSGE_INLINE
void WglContext::SwapBuffers(void)
{
	::SwapBuffers(m_hdc);

	// TODO
	::wglSwapIntervalEXT(1);
}

BKSGE_INLINE
void WglContext::MakeCurrent(bool current)
{
	if (current)
	{
		::wglMakeCurrent(m_hdc, m_hglrc);
	}
	else
	{
		::wglMakeCurrent(nullptr, nullptr);
	}
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_RENDER_GL_WGL_INL_WGL_CONTEXT_INL_HPP
