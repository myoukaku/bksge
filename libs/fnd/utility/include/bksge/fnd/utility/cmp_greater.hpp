﻿/**
 *	@file	cmp_greater.hpp
 *
 *	@brief	cmp_greater を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_CMP_GREATER_HPP
#define BKSGE_FND_UTILITY_CMP_GREATER_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace bksge
{

using std::cmp_greater;

}	// namespace bksge

#else

#include <bksge/fnd/utility/cmp_less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename U>
inline BKSGE_CONSTEXPR bool
cmp_greater(T t, U u) BKSGE_NOEXCEPT
{
	return bksge::cmp_less(u, t);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_CMP_GREATER_HPP
