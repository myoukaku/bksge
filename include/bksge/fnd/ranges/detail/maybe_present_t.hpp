/**
 *	@file	maybe_present_t.hpp
 *
 *	@brief	maybe_present_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_MAYBE_PRESENT_T_HPP
#define BKSGE_FND_RANGES_DETAIL_MAYBE_PRESENT_T_HPP

#include <bksge/fnd/type_traits/conditional.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

struct Empty {};

template <bool Present, typename T>
using maybe_present_t = conditional_t<Present, T, Empty>;

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_MAYBE_PRESENT_T_HPP
