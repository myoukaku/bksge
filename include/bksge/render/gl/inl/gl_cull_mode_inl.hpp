/**
 *	@file	gl_cull_mode_inl.hpp
 *
 *	@brief	ToGlCullMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_CULL_MODE_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_CULL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_cull_mode.hpp>
#include <bksge/render/cull_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLenum ToGlCullMode(CullMode mode)
{
	static std::unordered_map<CullMode, GLenum> const m =
	{
		{ CullMode::kBack,	GL_BACK },
		{ CullMode::kFront,	GL_FRONT },
	};

	return m.at(mode);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_CULL_MODE_INL_HPP
