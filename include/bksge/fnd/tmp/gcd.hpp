/**
 *	@file	gcd.hpp
 *
 *	@brief	gcd クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_GCD_HPP
#define BKSGE_FND_TMP_GCD_HPP

#include <bksge/fnd/tmp/abs.hpp>

namespace bksge
{

namespace tmp
{

namespace detail
{

template <typename T, T x, T y, bool = (y == 0)>
struct gcd_impl
{
	static T const value = gcd_impl<T, y, x % y>::value;
};

template <typename T, T x, T y>
struct gcd_impl<T, x, y, true>
{
	static T const value = x;
};

}	// namespace detail

template <typename T, T x, T y>
struct gcd
{
	static T const value = bksge::tmp::abs<T, detail::gcd_impl<T, x, y>::value>::value;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_GCD_HPP
