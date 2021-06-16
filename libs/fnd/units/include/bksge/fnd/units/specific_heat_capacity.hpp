/**
 *	@file	specific_heat_capacity.hpp
 *
 *	@brief	specific_heat_capacity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_SPECIFIC_HEAT_CAPACITY_HPP
#define BKSGE_FND_UNITS_SPECIFIC_HEAT_CAPACITY_HPP

#include <bksge/fnd/units/joule.hpp>
#include <bksge/fnd/units/gram.hpp>
#include <bksge/fnd/units/kelvin.hpp>

namespace bksge
{

namespace units
{

// ジュール毎キログラム毎ケルビン(比熱容量の単位)
template <typename T> using joule_per_kilogram_kelvin  = decltype(joule<T>() / kilogram<T>() / kelvin<T>());
template <typename T> using joules_per_kilogram_kelvin = joule_per_kilogram_kelvin<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_SPECIFIC_HEAT_CAPACITY_HPP
