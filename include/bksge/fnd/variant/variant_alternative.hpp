/**
 *	@file	variant_alternative.hpp
 *
 *	@brief	variant_alternative の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_VARIANT_ALTERNATIVE_HPP
#define BKSGE_FND_VARIANT_VARIANT_ALTERNATIVE_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::variant_alternative;
using std::variant_alternative_t;

}	// namespace bksge

#else

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/type_traits/add_const.hpp>
#include <bksge/fnd/type_traits/add_volatile.hpp>
#include <bksge/fnd/type_traits/add_cv.hpp>
#include <bksge/fnd/type_traits/nth.hpp>
#include <cstddef>

namespace bksge
{

/**
 *	@class	variant_alternative
 *
 *	@brief	variant のI番目の型を取得する
 */
template <std::size_t I, typename T>
struct variant_alternative;

template <std::size_t I, typename T>
using variant_alternative_t =
	typename variant_alternative<I, T>::type;

template <std::size_t I, typename T>
struct variant_alternative<I, T const>
	: public bksge::add_const<variant_alternative_t<I, T>> {};

template <std::size_t I, typename T>
struct variant_alternative<I, T volatile>
	: public bksge::add_volatile<variant_alternative_t<I, T>> {};

template <std::size_t I, typename T>
struct variant_alternative<I, T const volatile>
	: public bksge::add_cv<variant_alternative_t<I, T>> {};

template <std::size_t I, typename... Types>
struct variant_alternative<I, variant<Types...>>
{
	static_assert(I < sizeof...(Types), "Index out of bounds in std::variant_alternative<>");
	using type = bksge::nth_t<I, Types...>;
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_VARIANT_VARIANT_ALTERNATIVE_HPP
