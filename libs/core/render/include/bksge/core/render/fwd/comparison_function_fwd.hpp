/**
 *	@file	comparison_function_fwd.hpp
 *
 *	@brief	ComparisonFunction の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_COMPARISON_FUNCTION_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_COMPARISON_FUNCTION_FWD_HPP

#include <bksge/fnd/cstdint/uint32_t.hpp>

namespace bksge
{

namespace render
{

enum class ComparisonFunction : bksge::uint32_t;

}	// namespace render

using render::ComparisonFunction;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_COMPARISON_FUNCTION_FWD_HPP
