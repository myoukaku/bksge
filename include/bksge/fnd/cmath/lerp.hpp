/**
 *	@file	lerp.hpp
 *
 *	@brief	lerp 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LERP_HPP
#define BKSGE_FND_CMATH_LERP_HPP

#include <cmath>

#if defined(__cpp_lib_interpolate) && (__cpp_lib_interpolate >= 201902)

namespace bksge
{

using std::lerp;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	２つの値の間を線形補間します
 *
 *	@param	a		1つ目の値
 *	@param	b		2つ目の値
 *	@param	t		補間係数
 *	@return	２つの値を線形補間した値
 *
 *	tは 0.0 から 1.0 までの値を基本的には指定するが、1.0を超える指定も許可されている。
 *
 *	isfinite(a) && isfinite(b)である場合、戻り値rは以下のようになる：
 *	・t == 0である場合、r == a
 *	・t == 1である場合、r == b
 *	・t >= 0 && t <= 1である場合、isfinite(r) != 0
 *	・isfinite(t) && a == bである場合、r == a
 *	・isfinite(t) || !isnan(t) && b - a != 0である場合、!isnan(r)
 * 
 *	比較関数CMP(x, y)を、x > yであれば1、x < yであれば-1、そうでなければ0を返すものであるとして、
 *	あらゆる時間値t1とt2についてCMP(lerp(a,b,t2), lerp(a,b,t1))、CMP(t2, t1)、CMP(b,a)はいずれも非負となる
 */
BKSGE_CXX14_CONSTEXPR float lerp(float a, float b, float t) BKSGE_NOEXCEPT;
BKSGE_CXX14_CONSTEXPR double lerp(double a, double b, double t) BKSGE_NOEXCEPT;
BKSGE_CXX14_CONSTEXPR long double lerp(long double a, long double b, long double t) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/lerp_inl.hpp>

#endif

#endif // BKSGE_FND_CMATH_LERP_HPP
