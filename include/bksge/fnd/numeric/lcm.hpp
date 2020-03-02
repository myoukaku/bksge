/**
 *	@file	lcm.hpp
 *
 *	@brief	lcm の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_LCM_HPP
#define BKSGE_FND_NUMERIC_LCM_HPP

#include <bksge/fnd/numeric/gcd.hpp>
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
 *	@brief		最小公倍数を得る
 *
 *	@tparam		M	整数型
 *	@tparam		N	整数型
 *
 *	@param		m	整数値
 *	@param		n	整数値
 *
 *	@return		m と n のどちらかが 0 の場合、 0 を返す。
 *				そうでない場合、 |m| と |n| の最小公倍数を返す。
 */
template <
	typename M,
	typename N,
	typename = bksge::enable_if_t<
		bksge::is_integral<M>::value &&
		bksge::is_integral<N>::value
	>
>
BKSGE_CONSTEXPR bksge::common_type_t<M, N>
lcm(M m, N n)
BKSGE_NOEXCEPT
{
	return
		(m == 0 || n == 0) ?
			0 :
		(bksge::abs(m) / bksge::gcd(m, n)) * bksge::abs(n);
}

}	// namespace numeric

using numeric::lcm;

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_LCM_HPP
