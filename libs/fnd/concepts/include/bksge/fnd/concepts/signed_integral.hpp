/**
 *	@file	signed_integral.hpp
 *
 *	@brief	signed_integral の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_SIGNED_INTEGRAL_HPP
#define BKSGE_FND_CONCEPTS_SIGNED_INTEGRAL_HPP

#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_signed.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept signed_integral = bksge::integral<T> && bksge::is_signed<T>::value;

template <typename T>
using is_signed_integral = bksge::bool_constant<signed_integral<T>>;

#else

template <typename T>
using signed_integral =
	bksge::conjunction<
		bksge::integral<T>, bksge::is_signed<T>
	>;

template <typename T>
using is_signed_integral = signed_integral<T>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_SIGNED_INTEGRAL_HPP
