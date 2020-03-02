/**
 *	@file	gcd.hpp
 *
 *	@brief	gcd の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_GCD_HPP
#define BKSGE_FND_NUMERIC_GCD_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace numeric
{

/**
 *	@brief		最大公約数を得る
 *
 *	@tparam		M	整数型
 *	@tparam		N	整数型
 *
 *	@param		m	整数値
 *	@param		n	整数値
 *
 *	@return		m と n の両方が 0 の場合、 0 を返す。
 *				そうでない場合、 |m| と |n| の最大公約数を返す。
 */
template <
	typename M,
	typename N,
	typename = bksge::enable_if_t<
		bksge::is_integral<M>::value &&
		bksge::is_integral<N>::value
	>
>
inline BKSGE_CONSTEXPR bksge::common_type_t<M, N>
gcd(M m, N n)
BKSGE_NOEXCEPT
{
	return
		m == 0 ? bksge::abs(n) :
		n == 0 ? bksge::abs(m) :
		bksge::numeric::gcd(n, m % n);
}

}	// namespace numeric

using numeric::gcd;

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_GCD_HPP
