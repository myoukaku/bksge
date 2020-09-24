/**
 *	@file	unsigned_integral.hpp
 *
 *	@brief	unsigned_integral の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_UNSIGNED_INTEGRAL_HPP
#define BKSGE_FND_CONCEPTS_UNSIGNED_INTEGRAL_HPP

#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/signed_integral.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept unsigned_integral = bksge::integral<T> && !bksge::signed_integral<T>;

template <typename T>
using is_unsigned_integral = bksge::bool_constant<unsigned_integral<T>>;

#else

template <typename T>
using unsigned_integral =
	bksge::bool_constant<
		bksge::integral<T>::value && !bksge::signed_integral<T>::value
	>;

template <typename T>
using is_unsigned_integral = unsigned_integral<T>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_UNSIGNED_INTEGRAL_HPP
