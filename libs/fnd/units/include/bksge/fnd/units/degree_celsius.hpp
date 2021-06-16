/**
 *	@file	degree_celsius.hpp
 *
 *	@brief	degree_celsius の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DEGREE_CELSIUS_HPP
#define BKSGE_FND_UNITS_DEGREE_CELSIUS_HPP

#include <bksge/fnd/units/base_dimensions/temperature.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// セルシウス度
template <typename T> using degree_celsius  = quantity<T, temperature_dimension, bksge::ratio<1>, bksge::ratio<27315, 100>>;
template <typename T> using degrees_celsius = degree_celsius<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DEGREE_CELSIUS_HPP
