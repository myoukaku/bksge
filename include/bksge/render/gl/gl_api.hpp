/**
 *	@file	gl_api.hpp
 *
 *	@brief	OpenGL のヘッダをインクルード
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_API_HPP
#define BKSGE_RENDER_GL_GL_API_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)
#	include <bksge/detail/win32.hpp>
#endif

#include <gl/gl.h>

#include <bksge/render/gl/glext.hpp>

#if defined(_MSC_VER)
#	pragma comment(lib, "OpenGL32.lib")
#endif

#endif // BKSGE_RENDER_GL_GL_API_HPP
