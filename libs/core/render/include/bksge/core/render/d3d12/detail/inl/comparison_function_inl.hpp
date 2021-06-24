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

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_COMPARISON_FUNC
ToD3D12ComparisonFunction(bksge::ComparisonFunction comparison_function)
{
	switch (comparison_function)
	{
	case bksge::ComparisonFunction::kNever:        return D3D12_COMPARISON_FUNC_NEVER;
	case bksge::ComparisonFunction::kLess:         return D3D12_COMPARISON_FUNC_LESS;
	case bksge::ComparisonFunction::kEqual:        return D3D12_COMPARISON_FUNC_EQUAL;
	case bksge::ComparisonFunction::kLessEqual:    return D3D12_COMPARISON_FUNC_LESS_EQUAL;
	case bksge::ComparisonFunction::kGreater:      return D3D12_COMPARISON_FUNC_GREATER;
	case bksge::ComparisonFunction::kNotEqual:     return D3D12_COMPARISON_FUNC_NOT_EQUAL;
	case bksge::ComparisonFunction::kGreaterEqual: return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	case bksge::ComparisonFunction::kAlways:       return D3D12_COMPARISON_FUNC_ALWAYS;
	}
	return D3D12_COMPARISON_FUNC_NEVER;
}

}	// namespace detail

BKSGE_INLINE
ComparisonFunction::ComparisonFunction(bksge::ComparisonFunction comparison_function)
	: m_comparison_function(detail::ToD3D12ComparisonFunction(comparison_function))
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
