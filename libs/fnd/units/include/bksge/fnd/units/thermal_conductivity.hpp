/**
 *	@file	thermal_conductivity.hpp
 *
 *	@brief	thermal_conductivity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_THERMAL_CONDUCTIVITY_HPP
#define BKSGE_FND_UNITS_THERMAL_CONDUCTIVITY_HPP

#include <bksge/fnd/units/watt.hpp>
#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/kelvin.hpp>

namespace bksge
{

namespace units
{

// ワット毎メートル毎ケルビン(熱伝導率の単位)
template <typename T> using watt_per_metre_kelvin  = decltype(watt<T>() / metre<T>() / kelvin<T>());
template <typename T> using watt_per_meter_kelvin  = watt_per_metre_kelvin<T>;
template <typename T> using watts_per_metre_kelvin = watt_per_metre_kelvin<T>;
template <typename T> using watts_per_meter_kelvin = watt_per_metre_kelvin<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_THERMAL_CONDUCTIVITY_HPP
