/**
 *	@file	ellint_3.hpp
 *
 *	@brief	ellint_3 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ELLINT_3_HPP
#define BKSGE_FND_CMATH_ELLINT_3_HPP

#include <bksge/fnd/cmath/detail/ellint_3_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	第二種不完全楕円積分 (incomplete elliptic integral of the second kind) を計算する。
 *
 *	@param	k
 *	@param	phi_
 *
 *	@return	引数 k, phi_ の第二種不完全楕円積分を返す
 *
 *	引数がどれか1つでも NaN のとき、NaN を返す
 *	|k| > 1 のとき、NaN を返す(std::ellint_3 と違い、例外を投げない)
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic3)
>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
ellint_3(Arithmetic1 k, Arithmetic2 nu, Arithmetic3 phi_) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return detail::ellint_3_impl(
		static_cast<type>(k), static_cast<type>(nu), static_cast<type>(phi_));
}

inline BKSGE_CXX14_CONSTEXPR float
ellint_3f(float k, float nu, float phi_) BKSGE_NOEXCEPT
{
	return detail::ellint_3_impl(k, nu, phi_);
}

inline BKSGE_CXX14_CONSTEXPR long double
ellint_3l(long double k, long double nu, long double phi_) BKSGE_NOEXCEPT
{
	return detail::ellint_3_impl(k, nu, phi_);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ELLINT_3_HPP
