/**
 *	@file	molar_energy.hpp
 *
 *	@brief	molar_energy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MOLAR_ENERGY_HPP
#define BKSGE_FND_UNITS_MOLAR_ENERGY_HPP

#include <bksge/fnd/units/joule.hpp>
#include <bksge/fnd/units/mole.hpp>

namespace bksge
{

namespace units
{

// ジュール毎モル(モルエネルギーの単位)
template <typename T> using joule_per_mole  = decltype(joule<T>() / mole<T>());
template <typename T> using joules_per_mole = joule_per_mole<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MOLAR_ENERGY_HPP
