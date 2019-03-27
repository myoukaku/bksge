/**
 *	@file	wglext_inl.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_WGL_INL_WGLEXT_INL_HPP
#define BKSGE_RENDER_GL_WGL_INL_WGLEXT_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/gl/wgl/wglext.hpp>

BKSGE_WARNING_PUSH()
#if defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION >= 80000)
BKSGE_WARNING_DISABLE_GCC("-Wcast-function-type")
#endif

#define BKSGE_WGLEXT_FUNC(funcptr, funcname, ...)	\
	static funcptr p = (funcptr)wglGetProcAddress(#funcname);	\
	if (p)	\
	{	\
		return p(__VA_ARGS__);	\
	}

BKSGE_INLINE BOOL WINAPI wglSwapIntervalEXT(int interval)
{
	BKSGE_WGLEXT_FUNC(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT, interval);
	return false;
}

#undef BKSGE_WGLEXT_FUNC

BKSGE_WARNING_POP()

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_RENDER_GL_WGL_INL_WGLEXT_INL_HPP
