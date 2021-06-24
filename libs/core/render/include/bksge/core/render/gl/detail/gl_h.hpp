/**
 *	@file	gl_h.hpp
 *
 *	@brief	OpenGL のヘッダをインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_GL_H_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_GL_H_HPP

#include <bksge/fnd/config.hpp>

// 先にwindows.hをインクルードしないとminとかmaxがdefineされてしまう
#if defined(BKSGE_PLATFORM_WIN32)
#  include <bksge/core/detail/win32.hpp>
#endif

#define GL_GLEXT_PROTOTYPES
//#include <GL/gl.h>
#include <GL/glcorearb.h>
#include <GL/glext.h>

//#define EGL_EGLEXT_PROTOTYPES
//#include <EGL/egl.h>
//#include <EGL/eglext.h>

#if defined(BKSGE_PLATFORM_WIN32)
#  define WGL_WGLEXT_PROTOTYPES
//#  include <GL/wgl.h>
#  include <GL/wglext.h>
#elif defined(BKSGE_PLATFORM_MACOS)
#elif defined(BKSGE_PLATFORM_LINUX)
#  define GLX_GLXEXT_PROTOTYPES
#  include <GL/glx.h>
#  include <GL/glxext.h>
#  undef None
#  undef Bool
#endif

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/glext_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GL_H_HPP
