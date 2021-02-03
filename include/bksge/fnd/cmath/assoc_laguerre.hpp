/**
 *	@file	assoc_laguerre.hpp
 *
 *	@brief	assoc_laguerre 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ASSOC_LAGUERRE_HPP
#define BKSGE_FND_CMATH_ASSOC_LAGUERRE_HPP

#include <bksge/fnd/cmath/detail/assoc_laguerre_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ラゲール陪多項式 (associated Laguerre polynomials) を計算する。
 *
 *	@param	n
 *	@param	m
 *	@param	x
 *
 *	@return	引数 n, m, x のラゲール陪多項式を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	x が負の値のとき、NaN を返す(std::assoc_laguerre と違い、例外を投げない)
 *	n >= 128 または m >= 128 のとき、振る舞いは実装定義
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline /*BKSGE_CONSTEXPR*/ bksge::float_promote_t<Arithmetic>
assoc_laguerre(unsigned int n, unsigned int m, Arithmetic x)
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::assoc_laguerre_impl(n, m, static_cast<type>(x));
}

inline /*BKSGE_CONSTEXPR*/ float
assoc_laguerref(unsigned int n, unsigned int m, float x)
{
	return detail::assoc_laguerre_impl(n, m, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
assoc_laguerrel(unsigned int n, unsigned int m, long double x)
{
	return detail::assoc_laguerre_impl(n, m, x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ASSOC_LAGUERRE_HPP
