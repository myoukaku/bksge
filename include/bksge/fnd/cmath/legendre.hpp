/**
 *	@file	legendre.hpp
 *
 *	@brief	legendre 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LEGENDRE_HPP
#define BKSGE_FND_CMATH_LEGENDRE_HPP

#include <bksge/fnd/cmath/detail/legendre_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ルジャンドル多項式 (Legendre polynomials) を計算する。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x のルジャンドル多項式を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	|x| > 1 のとき、NaN を返す
 *	n >= 128 のとき、振る舞いは実装定義
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
legendre(unsigned int n, Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::legendre_impl(n, static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
legendref(unsigned int n, float x) BKSGE_NOEXCEPT
{
	return detail::legendre_impl(n, x);
}

inline BKSGE_CXX14_CONSTEXPR long double
legendrel(unsigned int n, long double x) BKSGE_NOEXCEPT
{
	return detail::legendre_impl(n, x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LEGENDRE_HPP
