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

#endif

template <typename T>
struct unsigned_integral_t
	: public bksge::bool_constant<
		bksge::integral_t<T>::value && !bksge::signed_integral_t<T>::value
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_UNSIGNED_INTEGRAL_HPP
