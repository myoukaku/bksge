/**
 *	@file	accumulate.hpp
 *
 *	@brief	accumulate クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_ACCUMULATE_HPP
#define BKSGE_FND_TMP_ACCUMULATE_HPP

#include <bksge/fnd/tmp/plus.hpp>

namespace bksge
{

namespace tmp
{

namespace detail
{

template <template <typename U, U, U> class F, typename T, T... Is>
struct accumulate_impl;

template <template <typename U, U, U> class F, typename T, T x>
struct accumulate_impl<F, T, x>
{
	static T const value = x;
};

template <template <typename U, U, U> class F, typename T, T x, T y, T... Rest>
struct accumulate_impl<F, T, x, y, Rest...>
{
	static T const value =
		accumulate_impl<
			F, T, F<T, x, y>::value, Rest...
		>::value;
};

}	// namespace detail

template <
	typename Sequence,
	typename Sequence::value_type Init = 0,
	template <typename T, T, T> class F = bksge::tmp::plus
>
struct accumulate;

template <
	typename T, T... Is,
	template <typename U, U...> class Sequence,
	typename Sequence<T, Is...>::value_type Init,
	template <typename V, V, V> class F
>
struct accumulate<Sequence<T, Is...>, Init, F>
{
	static T const value =
		detail::accumulate_impl<F, T, Init, Is...>::value;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_ACCUMULATE_HPP
