/**
 *	@file	viewport_inl.hpp
 *
 *	@brief	Viewport クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_VIEWPORT_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_VIEWPORT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/viewport.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/viewport.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE void
Viewport::Apply(bksge::Viewport const& viewport)
{
	auto const& rect = viewport.rect();
	::glViewport(
		static_cast<::GLint>(rect.left()),
		static_cast<::GLint>(rect.top()),
		static_cast<::GLsizei>(rect.width()),
		static_cast<::GLsizei>(rect.height()));

	::glDepthRangef(viewport.min_depth(), viewport.max_depth());
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_VIEWPORT_INL_HPP
