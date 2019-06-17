/**
 *	@file	lcm.hpp
 *
 *	@brief	lcm クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TMP_LCM_HPP
#define BKSGE_TMP_LCM_HPP

#include <bksge/tmp/gcd.hpp>
#include <bksge/tmp/abs.hpp>

namespace bksge
{

namespace tmp
{

namespace detail
{

template <typename T, T x, T y, bool x_is_0 = (x == 0), bool y_is_0 = (y == 0)>
struct lcm_impl
{
	static T const value = x / gcd<T, x, y>::value * y;
};

template <typename T, T x, T y>
struct lcm_impl<T, x, y, false, true>
{
	static T const value = 0;
};

template <typename T, T x, T y, bool y_is_0>
struct lcm_impl<T, x, y, true, y_is_0>
{
	static T const value = 0;
};

}	// namespace detail

template <typename T, T x, T y>
struct lcm
{
	static T const value = bksge::tmp::abs<T, detail::lcm_impl<T, x, y>::value>::value;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_TMP_LCM_HPP
