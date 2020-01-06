/**
 *	@file	cull_mode_inl.hpp
 *
 *	@brief	CullMode クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_CULL_MODE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_CULL_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/cull_mode.hpp>
#include <bksge/core/render/cull_mode.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlCullMode(bksge::CullMode cull_mode)
{
	switch (cull_mode)
	{
	case bksge::CullMode::kBack:  return GL_BACK;
	case bksge::CullMode::kFront: return GL_FRONT;
	}
	return GL_BACK;
}

}	// namespace detail

BKSGE_INLINE
CullMode::CullMode(bksge::CullMode cull_mode)
	: m_cull_mode(detail::ToGlCullMode(cull_mode))
{}

BKSGE_INLINE
CullMode::operator ::GLenum() const
{
	return m_cull_mode;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_CULL_MODE_INL_HPP
