/**
 *	@file	beta.hpp
 *
 *	@brief	beta 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_BETA_HPP
#define BKSGE_FND_CMATH_BETA_HPP

#include <bksge/fnd/cmath/detail/beta_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ベータ関数 (beta function) を計算する。
 *
 *	@param	x
 *	@param	y
 *
 *	@return	引数 x, y のベータ関数を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	x <= 0 または y <= 0 のとき、NaN を返す
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
beta(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::beta_impl(static_cast<type>(x), static_cast<type>(y));
}

inline BKSGE_CXX14_CONSTEXPR float
betaf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::beta_impl(x, y);
}

inline BKSGE_CXX14_CONSTEXPR long double
betal(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::beta_impl(x, y);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_BETA_HPP
