/**
 *	@file	ratio_gcd.hpp
 *
 *	@brief	ratio_gcdの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RATIO_RATIO_GCD_HPP
#define BKSGE_FND_RATIO_RATIO_GCD_HPP

#include <bksge/fnd/ratio/ratio.hpp>
#include <bksge/fnd/tmp/gcd.hpp>
#include <bksge/fnd/tmp/lcm.hpp>
#include <bksge/fnd/cstdint/intmax_t.hpp>

namespace bksge
{

/**
 *	@brief	ratio_gcd
 */
template <typename R1, typename R2>
using ratio_gcd = typename bksge::ratio<
	bksge::tmp::gcd<bksge::intmax_t, R1::num, R2::num>::value,
	bksge::tmp::lcm<bksge::intmax_t, R1::den, R2::den>::value
>::type;

}	// namespace bksge

#endif // BKSGE_FND_RATIO_RATIO_GCD_HPP
