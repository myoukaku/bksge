/**
 *	@file	comparison_function_inl.hpp
 *
 *	@brief	ComparisonFunction クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_comparison_function_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_comparison_function_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/comparison_function.hpp>
#include <bksge/core/render/comparison_function.hpp>
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
GlComparisonFunction(bksge::ComparisonFunction mode)
{
	static std::unordered_map<bksge::ComparisonFunction, ::GLenum> const m =
	{
		{ bksge::ComparisonFunction::kNever,		GL_NEVER },
		{ bksge::ComparisonFunction::kLess,			GL_LESS },
		{ bksge::ComparisonFunction::kEqual,		GL_EQUAL },
		{ bksge::ComparisonFunction::kLessEqual,	GL_LEQUAL },
		{ bksge::ComparisonFunction::kGreater,		GL_GREATER },
		{ bksge::ComparisonFunction::kNotEqual,		GL_NOTEQUAL },
		{ bksge::ComparisonFunction::kGreaterEqual,	GL_GEQUAL },
		{ bksge::ComparisonFunction::kAlways,		GL_ALWAYS },
	};

	return m.at(mode);
}

}	// namespace detail

BKSGE_INLINE
ComparisonFunction::ComparisonFunction(bksge::ComparisonFunction comparison_function)
	: m_comparison_function(detail::GlComparisonFunction(comparison_function))
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

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_comparison_function_INL_HPP
