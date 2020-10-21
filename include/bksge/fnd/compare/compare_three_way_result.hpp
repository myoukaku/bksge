/**
 *	@file	compare_three_way_result.hpp
 *
 *	@brief	compare_three_way_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_COMPARE_THREE_WAY_RESULT_HPP
#define BKSGE_FND_COMPARE_COMPARE_THREE_WAY_RESULT_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::compare_three_way_result;
using std::compare_three_way_result_t;

}	// namespace bksge

#else	// defined(BKSGE_USE_STD_COMPARE)

#include <bksge/fnd/compare/detail/compare_three_way_result_impl.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename U = T>
struct compare_three_way_result
	: detail::compare_three_way_result_impl<T, U>
{};

template <typename T, typename U = T>
using compare_three_way_result_t =
	typename detail::compare_three_way_result_impl<T, U>::type;

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_COMPARE)

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // BKSGE_FND_COMPARE_COMPARE_THREE_WAY_RESULT_HPP
