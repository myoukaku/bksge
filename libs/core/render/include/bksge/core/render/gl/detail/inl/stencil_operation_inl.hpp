/**
 *	@file	stencil_operation_inl.hpp
 *
 *	@brief	StencilOperation クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_STENCIL_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_STENCIL_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/stencil_operation.hpp>
#include <bksge/core/render/stencil_operation.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlStencilOperation(bksge::StencilOperation stencil_operation)
{
	switch (stencil_operation)
	{
	case bksge::StencilOperation::kKeep:         return GL_KEEP;
	case bksge::StencilOperation::kZero:         return GL_ZERO;
	case bksge::StencilOperation::kReplace:      return GL_REPLACE;
	case bksge::StencilOperation::kIncrSaturate: return GL_INCR_WRAP;
	case bksge::StencilOperation::kDecrSaturate: return GL_DECR_WRAP;
	case bksge::StencilOperation::kInvert:       return GL_INVERT;
	case bksge::StencilOperation::kIncr:         return GL_INCR;
	case bksge::StencilOperation::kDecr:         return GL_DECR;
	}
	return GL_KEEP;
}

}	// namespace detail

BKSGE_INLINE
StencilOperation::StencilOperation(bksge::StencilOperation stencil_operation)
	: m_stencil_operation(detail::ToGlStencilOperation(stencil_operation))
{}

BKSGE_INLINE
StencilOperation::operator ::GLenum() const
{
	return m_stencil_operation;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_STENCIL_OPERATION_INL_HPP
