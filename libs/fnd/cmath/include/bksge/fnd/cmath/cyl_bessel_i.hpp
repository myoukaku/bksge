/**
 *	@file	cyl_bessel_i.hpp
 *
 *	@brief	cyl_bessel_i 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_CYL_BESSEL_I_HPP
#define BKSGE_FND_CMATH_CYL_BESSEL_I_HPP

#include <bksge/fnd/cmath/detail/cyl_bessel_i_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	第一種変形ベッセル関数 (modified Bessel functions of the first kind) を計算する。
 *
 *	@param	nu
 *	@param	x
 *
 *	@return	引数 nu, x の第一種変形ベッセル関数を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	nu >= 128 のとき、振る舞いは実装定義
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
cyl_bessel_i(Arithmetic1 nu, Arithmetic2 x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::cyl_bessel_i_impl(static_cast<type>(nu), static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
cyl_bessel_if(float nu, float x) BKSGE_NOEXCEPT
{
	return detail::cyl_bessel_i_impl(nu, x);
}

inline BKSGE_CXX14_CONSTEXPR long double
cyl_bessel_il(long double nu, long double x) BKSGE_NOEXCEPT
{
	return detail::cyl_bessel_i_impl(nu, x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_CYL_BESSEL_I_HPP
