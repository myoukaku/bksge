/**
 *	@file	kelvin.hpp
 *
 *	@brief	kelvin の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_KELVIN_HPP
#define BKSGE_UNITS_KELVIN_HPP

#include <bksge/units/base_dimensions/temperature.hpp>
#include <bksge/units/detail/quantity.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ケルビン
template <typename T> using kelvin  = quantity<T, temperature_dimension>;
template <typename T> using kelvins = kelvin<T>;
BKSGE_UNITS_SI_PREFIX(kelvin);
BKSGE_UNITS_SI_PREFIX(kelvins);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_KELVIN_HPP
