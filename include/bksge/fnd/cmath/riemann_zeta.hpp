/**
 *	@file	riemann_zeta.hpp
 *
 *	@brief	riemann_zeta 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_RIEMANN_ZETA_HPP
#define BKSGE_FND_CMATH_RIEMANN_ZETA_HPP

#include <bksge/fnd/cmath/detail/riemann_zeta_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	リーマンのゼータ関数 (Riemann zeta function) を求める
 *
 *	@param	x
 *
 *	@return	引数 x のリーマンゼータ関数を返す
 *
 *	x が NaN のとき、NaN を返す
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
riemann_zeta(Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::riemann_zeta_impl(static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
riemann_zetaf(float x) BKSGE_NOEXCEPT
{
	return detail::riemann_zeta_impl(x);
}

inline BKSGE_CXX14_CONSTEXPR long double
riemann_zetal(long double x) BKSGE_NOEXCEPT
{
	return detail::riemann_zeta_impl(x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_RIEMANN_ZETA_HPP
