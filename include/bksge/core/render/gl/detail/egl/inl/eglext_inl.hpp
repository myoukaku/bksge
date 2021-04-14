/**
 *	@file	eglext_inl.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_EGL_INL_EGLEXT_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_EGL_INL_EGLEXT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/gl/detail/egl/eglext.hpp>

BKSGE_WARNING_PUSH()
#if defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION >= 80000)
BKSGE_WARNING_DISABLE_GCC("-Wcast-function-type")
#endif

#define BKSGE_EGLEXT_FUNC(funcptr, funcname, ...)	\
	static funcptr p = (funcptr)eglGetProcAddress(#funcname);	\
	if (p)	\
	{	\
		return p(__VA_ARGS__);	\
	}


#undef BKSGE_EGLEXT_FUNC

BKSGE_WARNING_POP()

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_EGL_INL_EGLEXT_INL_HPP
