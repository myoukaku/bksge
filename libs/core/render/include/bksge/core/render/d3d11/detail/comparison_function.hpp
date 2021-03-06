﻿/**
 *	@file	comparison_function.hpp
 *
 *	@brief	ComparisonFunction クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_COMPARISON_FUNCTION_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_COMPARISON_FUNCTION_HPP

#include <bksge/core/render/fwd/comparison_function_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class ComparisonFunction
{
public:
	explicit ComparisonFunction(bksge::ComparisonFunction comparison_function);

	operator ::D3D11_COMPARISON_FUNC() const;

private:
	::D3D11_COMPARISON_FUNC	m_comparison_function;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/comparison_function_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_COMPARISON_FUNCTION_HPP
