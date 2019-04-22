/**
 *	@file	comparison_function_fwd.hpp
 *
 *	@brief	ComparisonFunction の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FWD_COMPARISON_FUNCTION_FWD_HPP
#define BKSGE_RENDER_FWD_COMPARISON_FUNCTION_FWD_HPP

#include <cstdint>

namespace bksge
{

namespace render
{

enum class ComparisonFunction : std::uint32_t;

}	// namespace render

using render::ComparisonFunction;

}	// namespace bksge

#endif // BKSGE_RENDER_FWD_COMPARISON_FUNCTION_FWD_HPP
