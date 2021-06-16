/**
 *	@file	heat_capacity.hpp
 *
 *	@brief	heat_capacity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_HEAT_CAPACITY_HPP
#define BKSGE_FND_UNITS_HEAT_CAPACITY_HPP

#include <bksge/fnd/units/joule.hpp>
#include <bksge/fnd/units/kelvin.hpp>

namespace bksge
{

namespace units
{

// ジュール毎ケルビン(熱容量の単位)
template <typename T> using joule_per_kelvin  = decltype(joule<T>() / kelvin<T>());
template <typename T> using joules_per_kelvin = joule_per_kelvin<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_HEAT_CAPACITY_HPP
