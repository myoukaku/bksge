/**
 *	@file	context.hpp
 *
 *	@brief	Context クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_CONTEXT_HPP
#define BKSGE_RENDER_GL_DETAIL_CONTEXT_HPP

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	OpenGLコンテキストの基底クラス
 */
class Context
{
public:
	virtual ~Context() {}

	virtual void SwapBuffers(void) = 0;

	virtual void MakeCurrent(bool current) = 0;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_DETAIL_CONTEXT_HPP
