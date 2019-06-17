/**
 *	@file	bar.hpp
 *
 *	@brief	bar の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BAR_HPP
#define BKSGE_UNITS_BAR_HPP

#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/pascal.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// バール = 100000 パスカル
template <typename T> using bar  = decltype(pascals<T>() * std::ratio<100000>());
template <typename T> using bars = bar<T>;
BKSGE_UNITS_SI_PREFIX(bar);
BKSGE_UNITS_SI_PREFIX(bars);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BAR_HPP
