/**
 *	@file	comp_ellint_2.hpp
 *
 *	@brief	comp_ellint_2 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_COMP_ELLINT_2_HPP
#define BKSGE_FND_CMATH_COMP_ELLINT_2_HPP

#include <bksge/fnd/cmath/detail/comp_ellint_2_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	第二種完全楕円積分 (complete elliptic integral of the second kind) を計算する。
 *
 *	@param	k
 *
 *	@return	引数 k の第二種完全楕円積分を返す
 *
 *	引数 k が NaN のとき、NaN を返す
 *	|k| > 1 のとき、NaN を返す(std::comp_ellint_2 と違い、例外を投げない)
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
comp_ellint_2(Arithmetic k) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::comp_ellint_2_impl(static_cast<type>(k));
}

inline BKSGE_CXX14_CONSTEXPR float
comp_ellint_2f(float k) BKSGE_NOEXCEPT
{
	return detail::comp_ellint_2_impl(k);
}

inline BKSGE_CXX14_CONSTEXPR long double
comp_ellint_2l(long double k) BKSGE_NOEXCEPT
{
	return detail::comp_ellint_2_impl(k);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_COMP_ELLINT_2_HPP
