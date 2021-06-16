/**
 *	@file	energy_density.hpp
 *
 *	@brief	energy_density の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ENERGY_DENSITY_HPP
#define BKSGE_FND_UNITS_ENERGY_DENSITY_HPP

#include <bksge/fnd/units/joule.hpp>
#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// ジュール毎立方メートル(エネルギー密度の単位)
template <typename T> using joule_per_cubic_metre  = decltype(joule<T>() / metre<T>() / metre<T>() / metre<T>());
template <typename T> using joules_per_cubic_metre = joule_per_cubic_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ENERGY_DENSITY_HPP
