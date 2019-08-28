/**
 *	@file	cull_mode_inl.hpp
 *
 *	@brief	CullMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_CULL_MODE_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_CULL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/cull_mode.hpp>
#include <bksge/render/cull_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
GlCullMode(bksge::CullMode mode)
{
	static std::unordered_map<bksge::CullMode, ::GLenum> const m =
	{
		{ bksge::CullMode::kBack,	GL_BACK },
		{ bksge::CullMode::kFront,	GL_FRONT },
	};

	return m.at(mode);
}

}	// namespace detail

BKSGE_INLINE
CullMode::CullMode(bksge::CullMode cull_mode)
	: m_cull_mode(detail::GlCullMode(cull_mode))
{}

BKSGE_INLINE
CullMode::operator ::GLenum() const
{
	return m_cull_mode;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_CULL_MODE_INL_HPP
