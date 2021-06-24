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
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE bksge::string
to_string(ComparisonFunction const& comparison_function)
{
#define BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(x)	case x: return #x

	switch (comparison_function)
	{
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kNever);
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kLess);
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kEqual);
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kLessEqual);
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kGreater);
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kNotEqual);
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kGreaterEqual);
		BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP(ComparisonFunction::kAlways);
	}

	return "";

#undef BKSGE_CORE_RENDER_COMPARISON_FUNCTION_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_COMPARISON_FUNCTION_INL_HPP
