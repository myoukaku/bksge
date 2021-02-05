/**
 *	@file	ellint_2.hpp
 *
 *	@brief	ellint_2 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ELLINT_2_HPP
#define BKSGE_FND_CMATH_ELLINT_2_HPP

#include <bksge/fnd/cmath/detail/ellint_2_impl.hpp>
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
 *	|k| > 1 のとき、NaN を返す(std::ellint_2 と違い、例外を投げない)
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
ellint_2(Arithmetic1 k, Arithmetic2 phi_) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::ellint_2_impl(static_cast<type>(k), static_cast<type>(phi_));
}

inline BKSGE_CXX14_CONSTEXPR float
ellint_2f(float k, float phi_) BKSGE_NOEXCEPT
{
	return detail::ellint_2_impl(k, phi_);
}

inline BKSGE_CXX14_CONSTEXPR long double
ellint_2l(long double k, long double phi_) BKSGE_NOEXCEPT
{
	return detail::ellint_2_impl(k, phi_);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ELLINT_2_HPP
