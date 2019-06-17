/**
 *	@file	molar_heat_capacity.hpp
 *
 *	@brief	molar_heat_capacity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_MOLAR_HEAT_CAPACITY_HPP
#define BKSGE_UNITS_MOLAR_HEAT_CAPACITY_HPP

#include <bksge/units/joule.hpp>
#include <bksge/units/kelvin.hpp>
#include <bksge/units/mole.hpp>

namespace bksge
{

namespace units
{

// ジュール毎モル毎ケルビン(モルエントロピー・モル熱容量の単位)
template <typename T> using joule_per_kelvin_mole  = decltype(joule<T>() / (kelvin<T>() * mole<T>()));
template <typename T> using joules_per_kelvin_mole = joule_per_kelvin_mole<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_MOLAR_HEAT_CAPACITY_HPP
