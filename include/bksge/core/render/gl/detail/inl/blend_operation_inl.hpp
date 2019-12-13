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
GlBlendOperation(bksge::BlendOperation mode)
{
	static std::unordered_map<bksge::BlendOperation, ::GLenum> const m =
	{
		{ bksge::BlendOperation::kAdd,             GL_FUNC_ADD },
		{ bksge::BlendOperation::kSubtract,        GL_FUNC_SUBTRACT },
		{ bksge::BlendOperation::kReverseSubtract, GL_FUNC_REVERSE_SUBTRACT },
		{ bksge::BlendOperation::kMin,             GL_MIN },
		{ bksge::BlendOperation::kMax,             GL_MAX },
	};

	return m.at(mode);
}

}	// namespace detail

BKSGE_INLINE
BlendOperation::BlendOperation(bksge::BlendOperation blend_operation)
	: m_blend_operation(detail::GlBlendOperation(blend_operation))
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
