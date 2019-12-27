/**
 *	@file	comparison_function_inl.hpp
 *
 *	@brief	ComparisonFunction クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/comparison_function.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/comparison_function.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_COMPARISON_FUNC
D3D12ComparisonFunction(bksge::ComparisonFunction comparison_function)
{
	static std::unordered_map<bksge::ComparisonFunction, ::D3D12_COMPARISON_FUNC> const m =
	{
		{ bksge::ComparisonFunction::kNever,			D3D12_COMPARISON_FUNC_NEVER },
		{ bksge::ComparisonFunction::kLess,				D3D12_COMPARISON_FUNC_LESS },
		{ bksge::ComparisonFunction::kEqual,			D3D12_COMPARISON_FUNC_EQUAL },
		{ bksge::ComparisonFunction::kLessEqual,		D3D12_COMPARISON_FUNC_LESS_EQUAL },
		{ bksge::ComparisonFunction::kGreater,			D3D12_COMPARISON_FUNC_GREATER },
		{ bksge::ComparisonFunction::kNotEqual,			D3D12_COMPARISON_FUNC_NOT_EQUAL },
		{ bksge::ComparisonFunction::kGreaterEqual,		D3D12_COMPARISON_FUNC_GREATER_EQUAL },
		{ bksge::ComparisonFunction::kAlways,			D3D12_COMPARISON_FUNC_ALWAYS },
	};

	return m.at(comparison_function);
}

}	// namespace detail

BKSGE_INLINE
ComparisonFunction::ComparisonFunction(bksge::ComparisonFunction comparison_function)
	: m_comparison_function(detail::D3D12ComparisonFunction(comparison_function))
{}

BKSGE_INLINE
ComparisonFunction::operator ::D3D12_COMPARISON_FUNC() const
{
	return m_comparison_function;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
