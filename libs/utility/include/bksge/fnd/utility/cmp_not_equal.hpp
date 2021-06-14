/**
 *	@file	cmp_not_equal.hpp
 *
 *	@brief	cmp_not_equal を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_CMP_NOT_EQUAL_HPP
#define BKSGE_FND_UTILITY_CMP_NOT_EQUAL_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace bksge
{

using std::cmp_not_equal;

}	// namespace bksge

#else

#include <bksge/fnd/utility/cmp_equal.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename U>
inline BKSGE_CONSTEXPR bool
cmp_not_equal(T t, U u) BKSGE_NOEXCEPT
{
	return !bksge::cmp_equal(t, u);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_CMP_NOT_EQUAL_HPP
