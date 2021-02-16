/**
 *	@file	bigint_or_integral.hpp
 *
 *	@brief	bigint_or_integral コンセプトの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_BIGINT_OR_INTEGRAL_HPP
#define BKSGE_FND_BIGINT_DETAIL_BIGINT_OR_INTEGRAL_HPP

#include <bksge/fnd/bigint/detail/is_bigint.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept bigint_or_integral =
	bksge::detail::is_bigint<T>::value ||
	bksge::is_integral<T>::value;

#else

template <typename T>
using bigint_or_integral =
	bksge::disjunction<
		bksge::detail::is_bigint<T>,
		bksge::is_integral<T>
	>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_BIGINT_OR_INTEGRAL_HPP
