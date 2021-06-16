/**
 *	@file	velocity.hpp
 *
 *	@brief	velocity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_VELOCITY_HPP
#define BKSGE_FND_UNITS_VELOCITY_HPP

#include <bksge/fnd/units/length.hpp>
#include <bksge/fnd/units/time.hpp>

namespace bksge
{

namespace units
{

#define BKSGE_UNITS_DECLARE_VELOCITY_1(Length, Time)	\
	template <typename T> using Length ## _per_ ## Time = decltype(Length<T>() / Time<T>())

#define BKSGE_UNITS_DECLARE_VELOCITY(Length)	\
	BKSGE_UNITS_DECLARE_VELOCITY_1(Length, second);	\
	BKSGE_UNITS_DECLARE_VELOCITY_1(Length, minute);	\
	BKSGE_UNITS_DECLARE_VELOCITY_1(Length, hour)

#define BKSGE_UNITS_DECLARE_VELOCITY_SI_PREFIX(Length) \
	BKSGE_UNITS_DECLARE_VELOCITY(atto  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(femto ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(pico  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(nano  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(micro ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(milli ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(centi ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(deci  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(Length);              \
	BKSGE_UNITS_DECLARE_VELOCITY(deca  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(hecto ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(kilo  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(mega  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(giga  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(tera  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(peta  ## Length);     \
	BKSGE_UNITS_DECLARE_VELOCITY(exa   ## Length)

BKSGE_UNITS_DECLARE_VELOCITY_SI_PREFIX(metre);
BKSGE_UNITS_DECLARE_VELOCITY_SI_PREFIX(metres);
BKSGE_UNITS_DECLARE_VELOCITY_SI_PREFIX(meter);
BKSGE_UNITS_DECLARE_VELOCITY_SI_PREFIX(meters);
BKSGE_UNITS_DECLARE_VELOCITY(inch);
BKSGE_UNITS_DECLARE_VELOCITY(inches);
BKSGE_UNITS_DECLARE_VELOCITY(foot);
BKSGE_UNITS_DECLARE_VELOCITY(feet);
BKSGE_UNITS_DECLARE_VELOCITY(yard);
BKSGE_UNITS_DECLARE_VELOCITY(yards);
BKSGE_UNITS_DECLARE_VELOCITY(chain);
BKSGE_UNITS_DECLARE_VELOCITY(chains);
BKSGE_UNITS_DECLARE_VELOCITY(furlong);
BKSGE_UNITS_DECLARE_VELOCITY(furlongs);
BKSGE_UNITS_DECLARE_VELOCITY(mile);
BKSGE_UNITS_DECLARE_VELOCITY(miles);

#undef BKSGE_UNITS_DECLARE_VELOCITY_1
#undef BKSGE_UNITS_DECLARE_VELOCITY
#undef BKSGE_UNITS_DECLARE_VELOCITY_SI_PREFIX

}	// namespace units

}	// namespace bksge

#include <bksge/fnd/units/knot.hpp>

#endif // BKSGE_FND_UNITS_VELOCITY_HPP
