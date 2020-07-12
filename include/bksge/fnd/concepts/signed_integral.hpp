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
#include <bksge/fnd/type_traits/is_signed.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept signed_integral = bksge::integral<T> && bksge::is_signed<T>::value;

#endif

template <typename T>
struct signed_integral_t
	: public bksge::conjunction<
		bksge::integral_t<T>, bksge::is_signed<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_SIGNED_INTEGRAL_HPP
