/**
 *	@file	comparison_function_inl.hpp
 *
 *	@brief	ComparisonFunction の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_COMPARISON_FUNCTION_INL_HPP
#define BKSGE_RENDER_INL_COMPARISON_FUNCTION_INL_HPP

#include <bksge/render/comparison_function.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(ComparisonFunction const& comparison_function)
{
#define BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(x)	{ x, #x }

	static std::unordered_map<ComparisonFunction, std::string> const m =
	{
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kNever),
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kLess),
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kEqual),
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kLessEqual),
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kGreater),
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kNotEqual),
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kGreaterEqual),
		BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kAlways),
	};

	return m.at(comparison_function);

#undef BKSGE_RENDER_MAKE_COMPARISON_FUNCTION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_COMPARISON_FUNCTION_INL_HPP
