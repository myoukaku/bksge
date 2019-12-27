/**
 *	@file	comparison_function_inl.hpp
 *
 *	@brief	ComparisonFunction クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/comparison_function.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/comparison_function.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_COMPARISON_FUNC
D3D11ComparisonFunction(bksge::ComparisonFunction comparison_function)
{
	static std::unordered_map<bksge::ComparisonFunction, ::D3D11_COMPARISON_FUNC> const m =
	{
		{ bksge::ComparisonFunction::kNever,			D3D11_COMPARISON_NEVER },
		{ bksge::ComparisonFunction::kLess,				D3D11_COMPARISON_LESS },
		{ bksge::ComparisonFunction::kEqual,			D3D11_COMPARISON_EQUAL },
		{ bksge::ComparisonFunction::kLessEqual,		D3D11_COMPARISON_LESS_EQUAL },
		{ bksge::ComparisonFunction::kGreater,			D3D11_COMPARISON_GREATER },
		{ bksge::ComparisonFunction::kNotEqual,			D3D11_COMPARISON_NOT_EQUAL },
		{ bksge::ComparisonFunction::kGreaterEqual,		D3D11_COMPARISON_GREATER_EQUAL },
		{ bksge::ComparisonFunction::kAlways,			D3D11_COMPARISON_ALWAYS },
	};

	return m.at(comparison_function);
}

}	// namespace detail

BKSGE_INLINE
ComparisonFunction::ComparisonFunction(bksge::ComparisonFunction comparison_function)
	: m_comparison_function(detail::D3D11ComparisonFunction(comparison_function))
{}

BKSGE_INLINE
ComparisonFunction::operator ::D3D11_COMPARISON_FUNC() const
{
	return m_comparison_function;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
