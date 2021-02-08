/**
 *	@file	expint.hpp
 *
 *	@brief	expint 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_EXPINT_HPP
#define BKSGE_FND_CMATH_EXPINT_HPP

#include <bksge/fnd/cmath/detail/expint_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	指数積分 (exponential integral) を計算する。
 *
 *	@param	x
 *
 *	@return	引数 x の指数積分を返す
 *
 *	x が NaN のとき、NaN を返す
 *	x が ±0  のとき、-∞  を返す
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
expint(Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::expint_impl(static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
expintf(float x) BKSGE_NOEXCEPT
{
	return detail::expint_impl(x);
}

inline BKSGE_CXX14_CONSTEXPR long double
expintl(long double x) BKSGE_NOEXCEPT
{
	return detail::expint_impl(x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_EXPINT_HPP
