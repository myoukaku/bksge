/**
 *	@file	maybe_const_t.hpp
 *
 *	@brief	maybe_const_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_MAYBE_CONST_T_HPP
#define BKSGE_FND_RANGES_DETAIL_MAYBE_CONST_T_HPP

#include <bksge/fnd/type_traits/conditional.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <bool Const, typename T>
using maybe_const_t = bksge::conditional_t<Const, T const, T>;

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_MAYBE_CONST_T_HPP
