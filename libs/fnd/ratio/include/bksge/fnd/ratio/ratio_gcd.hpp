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
#include <cstdint>

namespace bksge
{

/**
 *	@brief	ratio_gcd
 */
template <typename R1, typename R2>
using ratio_gcd = typename bksge::ratio<
	bksge::tmp::gcd<std::intmax_t, R1::num, R2::num>::value,
	bksge::tmp::lcm<std::intmax_t, R1::den, R2::den>::value
>::type;

}	// namespace bksge

#endif // BKSGE_FND_RATIO_RATIO_GCD_HPP
