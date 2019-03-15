/**
 *	@file	gl_context.hpp
 *
 *	@brief	GlContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_CONTEXT_HPP
#define BKSGE_RENDER_GL_GL_CONTEXT_HPP

namespace bksge
{

namespace render
{

/**
 *	@brief	OpenGLコンテキストの基底クラス
 */
class GlContext
{
public:
	virtual ~GlContext() {}

	virtual void SwapBuffers(void) = 0;

	virtual void MakeCurrent(bool current) = 0;
};

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_GL_CONTEXT_HPP
