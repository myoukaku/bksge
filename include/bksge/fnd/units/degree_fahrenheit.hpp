/**
 *	@file	degree_fahrenheit.hpp
 *
 *	@brief	degree_fahrenheit の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DEGREE_FAHRENHEIT_HPP
#define BKSGE_FND_UNITS_DEGREE_FAHRENHEIT_HPP

#include <bksge/fnd/units/base_dimensions/temperature.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// ファーレンハイト度
template <typename T> using degree_fahrenheit  = quantity<T, temperature_dimension, bksge::ratio<5, 9>, bksge::ratio<45967, 100>>;
template <typename T> using degrees_fahrenheit = degree_fahrenheit<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DEGREE_FAHRENHEIT_HPP
