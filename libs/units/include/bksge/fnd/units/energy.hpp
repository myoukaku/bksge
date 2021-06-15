/**
 *	@file	energy.hpp
 *
 *	@brief	energy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ENERGY_HPP
#define BKSGE_FND_UNITS_ENERGY_HPP

#include <bksge/fnd/units/joule.hpp>
#include <bksge/fnd/units/erg.hpp>
#include <bksge/fnd/units/foot_poundal.hpp>
#include <bksge/fnd/units/calorie.hpp>
#include <bksge/fnd/units/watt.hpp>
#include <bksge/fnd/units/second.hpp>
#include <bksge/fnd/units/minute.hpp>
#include <bksge/fnd/units/hour.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ワット秒、キロワット時
#define BKSGE_UNITS_DECLARE_ENERGY_1(Name, Time) \
	template <typename T> using Name ## _ ## Time = decltype(Name<T>() * Time<T>());	\
	BKSGE_UNITS_SI_PREFIX(Name ## _ ## Time)

#define BKSGE_UNITS_DECLARE_ENERGY_2(Name)      \
	BKSGE_UNITS_DECLARE_ENERGY_1(Name, second);	\
	BKSGE_UNITS_DECLARE_ENERGY_1(Name, minute);	\
	BKSGE_UNITS_DECLARE_ENERGY_1(Name, hour)

BKSGE_UNITS_DECLARE_ENERGY_2(watt);
BKSGE_UNITS_DECLARE_ENERGY_2(watts);

#undef BKSGE_UNITS_DECLARE_ENERGY_1
#undef BKSGE_UNITS_DECLARE_ENERGY_2

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ENERGY_HPP
