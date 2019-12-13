/**
 *	@file	comparison_function_inl.hpp
 *
 *	@brief	ComparisonFunction の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_COMPARISON_FUNCTION_INL_HPP
#define BKSGE_CORE_RENDER_INL_COMPARISON_FUNCTION_INL_HPP

#include <bksge/core/render/comparison_function.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(ComparisonFunction const& comparison_function)
{
#define BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(x)	{ x, #x }

	static std::unordered_map<ComparisonFunction, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kNever),
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kLess),
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kEqual),
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kLessEqual),
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kGreater),
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kNotEqual),
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kGreaterEqual),
		BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP(ComparisonFunction::kAlways),
	};

	return m.at(comparison_function);

#undef BKSGE_CORE_RENDER_MAKE_COMPARISON_FUNCTION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_COMPARISON_FUNCTION_INL_HPP
