/**
 *	@file	is_standard_signed_integer.hpp
 *
 *	@brief	is_standard_signed_integer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_STANDARD_SIGNED_INTEGER_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_STANDARD_SIGNED_INTEGER_HPP

#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>

namespace bksge
{

namespace detail
{

template <typename T, typename... Types>
using is_standard_signed_integer_impl =
	bksge::disjunction<bksge::is_same<T, Types>...>;

template <typename T>
using is_standard_signed_integer =
	is_standard_signed_integer_impl<
		bksge::remove_cv_t<T>,
		signed char,
		signed short,
		signed int,
		signed long,
		signed long long
	>;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_STANDARD_SIGNED_INTEGER_HPP
