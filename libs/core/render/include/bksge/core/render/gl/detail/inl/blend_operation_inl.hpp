/**
 *	@file	blend_operation_inl.hpp
 *
 *	@brief	BlendOperation クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/blend_operation.hpp>
#include <bksge/core/render/blend_operation.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlBlendOperation(bksge::BlendOperation blend_operation)
{
	switch (blend_operation)
	{
	case bksge::BlendOperation::kAdd:             return GL_FUNC_ADD;
	case bksge::BlendOperation::kSubtract:        return GL_FUNC_SUBTRACT;
	case bksge::BlendOperation::kReverseSubtract: return GL_FUNC_REVERSE_SUBTRACT;
	case bksge::BlendOperation::kMin:             return GL_MIN;
	case bksge::BlendOperation::kMax:             return GL_MAX;
	}
	return GL_FUNC_ADD;
}

}	// namespace detail

BKSGE_INLINE
BlendOperation::BlendOperation(bksge::BlendOperation blend_operation)
	: m_blend_operation(detail::ToGlBlendOperation(blend_operation))
{}

BKSGE_INLINE
BlendOperation::operator ::GLenum() const
{
	return m_blend_operation;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_BLEND_OPERATION_INL_HPP
