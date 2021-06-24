/**
 *	@file	viewport.hpp
 *
 *	@brief	Viewport クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_VIEWPORT_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_VIEWPORT_HPP

#include <bksge/core/render/fwd/viewport_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class Viewport
{
public:
	static void Apply(bksge::Viewport const& state);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/viewport_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_VIEWPORT_HPP
