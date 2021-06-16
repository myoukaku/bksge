/**
 *	@file	laguerre.hpp
 *
 *	@brief	laguerre 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LAGUERRE_HPP
#define BKSGE_FND_CMATH_LAGUERRE_HPP

#include <bksge/fnd/cmath/detail/laguerre_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ラゲール多項式 (Laguerre polynomials) を計算する。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x のラゲール多項式を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	x が負の値のとき、NaN を返す(std::laguerre と違い、例外を投げない)
 *	n >= 128 のとき、振る舞いは実装定義
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
laguerre(unsigned int n, Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::laguerre_impl(n, static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
laguerref(unsigned int n, float x) BKSGE_NOEXCEPT
{
	return detail::laguerre_impl(n, x);
}

inline BKSGE_CXX14_CONSTEXPR long double
laguerrel(unsigned int n, long double x) BKSGE_NOEXCEPT
{
	return detail::laguerre_impl(n, x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LAGUERRE_HPP
