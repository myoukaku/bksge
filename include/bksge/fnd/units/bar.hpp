/**
 *	@file	bar.hpp
 *
 *	@brief	bar の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_BAR_HPP
#define BKSGE_FND_UNITS_BAR_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/pascal.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// バール = 100000 パスカル
template <typename T> using bar  = decltype(pascals<T>() * bksge::ratio<100000>());
template <typename T> using bars = bar<T>;
BKSGE_UNITS_SI_PREFIX(bar);
BKSGE_UNITS_SI_PREFIX(bars);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_BAR_HPP
