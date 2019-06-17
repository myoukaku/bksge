/**
 *	@file	watt.hpp
 *
 *	@brief	watt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_WATT_HPP
#define BKSGE_UNITS_WATT_HPP

#include <bksge/units/detail/si_prefix.hpp>
#include <bksge/units/joule.hpp>
#include <bksge/units/second.hpp>

namespace bksge
{

namespace units
{

// ワット(J/s)
template <typename T> using watt  = decltype(joule<T>() / second<T>());
template <typename T> using watts = watt<T>;
BKSGE_UNITS_SI_PREFIX(watt);
BKSGE_UNITS_SI_PREFIX(watts);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_WATT_HPP
