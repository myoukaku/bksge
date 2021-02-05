/**
 *	@file	comp_ellint_3.hpp
 *
 *	@brief	comp_ellint_3 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_COMP_ELLINT_3_HPP
#define BKSGE_FND_CMATH_COMP_ELLINT_3_HPP

#include <bksge/fnd/cmath/detail/comp_ellint_3_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	第三種完全楕円積分 (complete elliptic integral of the third kind) を計算する。
 *
 *	@param	k
 *	@param	nu
 *
 *	@return	引数 k, nu の第三種完全楕円積分を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	|k| > 1 のとき、NaN を返す(std::comp_ellint_3 と違い、例外を投げない)
 *	|k| = 1 のとき、inf を返す
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
comp_ellint_3(Arithmetic1 k, Arithmetic2 nu) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::comp_ellint_3_impl(static_cast<type>(k), static_cast<type>(nu));
}

inline BKSGE_CXX14_CONSTEXPR float
comp_ellint_3f(float k, float nu) BKSGE_NOEXCEPT
{
	return detail::comp_ellint_3_impl(k, nu);
}

inline BKSGE_CXX14_CONSTEXPR long double
comp_ellint_3l(long double k, long double nu) BKSGE_NOEXCEPT
{
	return detail::comp_ellint_3_impl(k, nu);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_COMP_ELLINT_3_HPP
