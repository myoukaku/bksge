/**
 *	@file	glx_context.hpp
 *
 *	@brief	GlxContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_GLX_GLX_CONTEXT_HPP
#define BKSGE_RENDER_GL_DETAIL_GLX_GLX_CONTEXT_HPP

#include <bksge/config.hpp>
#if 1//defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/gl/detail/context.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	Context の GLX版
 */
class GlxContext : public Context
{
public:
	explicit GlxContext(Window const& window);
	virtual ~GlxContext();
	void SwapBuffers(void) override;
	void MakeCurrent(bool current) override;

private:
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/glx/inl/glx_context_inl.hpp>
#endif

#endif

#endif // BKSGE_RENDER_GL_DETAIL_GLX_GLX_CONTEXT_HPP
