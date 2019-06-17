/**
 *	@file	heat_capacity.hpp
 *
 *	@brief	heat_capacity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_HEAT_CAPACITY_HPP
#define BKSGE_UNITS_HEAT_CAPACITY_HPP

#include <bksge/units/joule.hpp>
#include <bksge/units/kelvin.hpp>

namespace bksge
{

namespace units
{

// ジュール毎ケルビン(熱容量の単位)
template <typename T> using joule_per_kelvin  = decltype(joule<T>() / kelvin<T>());
template <typename T> using joules_per_kelvin = joule_per_kelvin<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_HEAT_CAPACITY_HPP
