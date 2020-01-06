/**
 *	@file	comparison_function_inl.hpp
 *
 *	@brief	ComparisonFunction クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/comparison_function.hpp>
#include <bksge/core/render/comparison_function.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlComparisonFunction(bksge::ComparisonFunction comparison_function)
{
	switch (comparison_function)
	{
	case bksge::ComparisonFunction::kNever:        return GL_NEVER;
	case bksge::ComparisonFunction::kLess:         return GL_LESS;
	case bksge::ComparisonFunction::kEqual:        return GL_EQUAL;
	case bksge::ComparisonFunction::kLessEqual:    return GL_LEQUAL;
	case bksge::ComparisonFunction::kGreater:      return GL_GREATER;
	case bksge::ComparisonFunction::kNotEqual:     return GL_NOTEQUAL;
	case bksge::ComparisonFunction::kGreaterEqual: return GL_GEQUAL;
	case bksge::ComparisonFunction::kAlways:       return GL_ALWAYS;
	}
	return GL_NEVER;
}

}	// namespace detail

BKSGE_INLINE
ComparisonFunction::ComparisonFunction(bksge::ComparisonFunction comparison_function)
	: m_comparison_function(detail::ToGlComparisonFunction(comparison_function))
{}

BKSGE_INLINE
ComparisonFunction::operator ::GLenum() const
{
	return m_comparison_function;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
