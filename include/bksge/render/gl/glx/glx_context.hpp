/**
 *	@file	glx_context.hpp
 *
 *	@brief	GlxContext の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GLX_GLX_CONTEXT_HPP
#define BKSGE_RENDER_GL_GLX_GLX_CONTEXT_HPP

#include <bksge/config.hpp>
#if 1//defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/gl/gl_context.hpp>
#include <bksge/window/fwd/window_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	GlContext の GLX版
 */
class GlxContext : public GlContext
{
public:
	explicit GlxContext(Window const& window);
	virtual ~GlxContext();
	void SwapBuffers(void) override;
	void MakeCurrent(bool current) override;

private:
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/glx/inl/glx_context_inl.hpp>
#endif

#endif

#endif // BKSGE_RENDER_GL_GLX_GLX_CONTEXT_HPP
