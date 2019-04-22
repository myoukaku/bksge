/**
 *	@file	comparison_function.hpp
 *
 *	@brief	ComparisonFunction の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_COMPARISON_FUNCTION_HPP
#define BKSGE_RENDER_COMPARISON_FUNCTION_HPP

#include <bksge/render/fwd/comparison_function_fwd.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief	比較関数
 */
enum class ComparisonFunction : std::uint32_t
{
	kNever,
	kLess,
	kEqual,
	kLessEqual,
	kGreater,
	kNotEqual,
	kGreaterEqual,
	kAlways,
};

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_COMPARISON_FUNCTION_HPP
