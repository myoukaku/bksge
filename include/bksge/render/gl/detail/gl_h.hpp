/**
 *	@file	gl_h.hpp
 *
 *	@brief	OpenGL のヘッダをインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_GL_H_HPP
#define BKSGE_RENDER_GL_DETAIL_GL_H_HPP

#include <bksge/config.hpp>

#if defined(BKSGE_PLATFORM_WIN32)
//#  include <bksge/detail/win32.hpp>
#  define GL_GLEXT_PROTOTYPES
//#  include <GL/gl.h>
#  include <GL/glcorearb.h>
#  include <GL/glext.h>
#  define WGL_WGLEXT_PROTOTYPES
//#  include <GL/wgl.h>
#  include <GL/wglext.h>
#elif defined(BKSGE_PLATFORM_MACOS)
#  define GL_GLEXT_PROTOTYPES
//#  include <GL/gl.h>
#  include <GL/glcorearb.h>
#  include <GL/glext.h>
#elif defined(BKSGE_PLATFORM_LINUX)
#  define GL_GLEXT_PROTOTYPES
//#  include <GL/gl.h>
#  include <GL/glcorearb.h>
#  include <GL/glext.h>
#  define GLX_GLXEXT_PROTOTYPES
#  include <GL/glx.h>
#  include <GL/glxext.h>
#  undef None
#  undef Bool
#endif

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/glext_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_GL_H_HPP
