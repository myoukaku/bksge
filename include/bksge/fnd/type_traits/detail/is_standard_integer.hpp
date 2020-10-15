/**
 *	@file	is_standard_integer.hpp
 *
 *	@brief	is_standard_integer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_STANDARD_INTEGER_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_STANDARD_INTEGER_HPP

#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/detail/is_standard_signed_integer.hpp>
#include <bksge/fnd/type_traits/detail/is_standard_unsigned_integer.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
using is_standard_integer =
	bksge::disjunction<
		bksge::detail::is_standard_signed_integer<T>,
		bksge::detail::is_standard_unsigned_integer<T>
	>;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_STANDARD_INTEGER_HPP
