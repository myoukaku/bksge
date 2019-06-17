/**
 *	@file	energy.hpp
 *
 *	@brief	energy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_ENERGY_HPP
#define BKSGE_UNITS_ENERGY_HPP

#include <bksge/units/joule.hpp>
#include <bksge/units/erg.hpp>
#include <bksge/units/foot_poundal.hpp>
#include <bksge/units/calorie.hpp>
#include <bksge/units/watt.hpp>
#include <bksge/units/second.hpp>
#include <bksge/units/minute.hpp>
#include <bksge/units/hour.hpp>
#include <bksge/units/detail/si_prefix.hpp>

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

#endif // BKSGE_UNITS_ENERGY_HPP
