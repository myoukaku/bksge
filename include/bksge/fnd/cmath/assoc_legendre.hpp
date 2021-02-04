/**
 *	@file	assoc_legendre.hpp
 *
 *	@brief	assoc_legendre 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ASSOC_LEGENDRE_HPP
#define BKSGE_FND_CMATH_ASSOC_LEGENDRE_HPP

#include <bksge/fnd/cmath/detail/assoc_legendre_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ルジャンドル陪関数 (associated Legendre functions) を計算する。
 *
 *	@param	n
 *	@param	m
 *	@param	x
 *
 *	@return	引数 n, m, x のルジャンドル陪関数を返す
 *
 *	引数 x が NaN のとき、NaN を返す
 *	|x| > 1 のとき、NaN を返す(std::assoc_legendre と違い、例外を投げない)
 *	n >= 128 のとき、振る舞いは実装定義
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
assoc_legendre(unsigned int n, unsigned int m, Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::assoc_legendre_impl(n, m, static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
assoc_legendref(unsigned int n, unsigned int m, float x) BKSGE_NOEXCEPT
{
	return detail::assoc_legendre_impl(n, m, x);
}

inline BKSGE_CXX14_CONSTEXPR long double
assoc_legendrel(unsigned int n, unsigned int m, long double x) BKSGE_NOEXCEPT
{
	return detail::assoc_legendre_impl(n, m, x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ASSOC_LEGENDRE_HPP
