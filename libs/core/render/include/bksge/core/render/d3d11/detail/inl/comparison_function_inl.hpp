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

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_COMPARISON_FUNC
ToD3D11ComparisonFunction(bksge::ComparisonFunction comparison_function)
{
	switch (comparison_function)
	{
	case bksge::ComparisonFunction::kNever:			return D3D11_COMPARISON_NEVER;
	case bksge::ComparisonFunction::kLess:			return D3D11_COMPARISON_LESS;
	case bksge::ComparisonFunction::kEqual:			return D3D11_COMPARISON_EQUAL;
	case bksge::ComparisonFunction::kLessEqual:		return D3D11_COMPARISON_LESS_EQUAL;
	case bksge::ComparisonFunction::kGreater:		return D3D11_COMPARISON_GREATER;
	case bksge::ComparisonFunction::kNotEqual:		return D3D11_COMPARISON_NOT_EQUAL;
	case bksge::ComparisonFunction::kGreaterEqual:	return D3D11_COMPARISON_GREATER_EQUAL;
	case bksge::ComparisonFunction::kAlways:		return D3D11_COMPARISON_ALWAYS;
	}
	return D3D11_COMPARISON_NEVER;
}

}	// namespace detail

BKSGE_INLINE
ComparisonFunction::ComparisonFunction(bksge::ComparisonFunction comparison_function)
	: m_comparison_function(detail::ToD3D11ComparisonFunction(comparison_function))
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
