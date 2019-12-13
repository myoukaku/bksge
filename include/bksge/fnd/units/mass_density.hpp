/**
 *	@file	mass_density.hpp
 *
 *	@brief	mass_density の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MASS_DENSITY_HPP
#define BKSGE_FND_UNITS_MASS_DENSITY_HPP

#include <bksge/fnd/units/mass.hpp>
#include <bksge/fnd/units/volume.hpp>

namespace bksge
{

namespace units
{

#define BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, Volume) \
	template <typename T> using Mass ## _per_ ## Volume = decltype(Mass<T>() / Volume<T>())

#define BKSGE_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, C, Length) \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## atto  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## femto ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## pico  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## nano  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## micro ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## milli ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## centi ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## deci  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## Length);            \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## deca  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## hecto ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## kilo  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## mega  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## giga  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## tera  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## peta  ## Length);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, C ## exa   ## Length)

#define BKSGE_UNITS_DECLARE_MASS_DENSITY_2(Mass)                     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, cubic_, metre); \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, cubic_, meter); \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_inch);              \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_foot);              \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_chain);             \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_furlong);           \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_yard);              \
	BKSGE_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_mile);              \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, /**/, litre);   \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, /**/, liter)

#define BKSGE_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX(Mass) \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(atto  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(femto ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(pico  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(nano  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(micro ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(milli ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(centi ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(deci  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(Mass);              \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(deca  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(hecto ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(kilo  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(mega  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(giga  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(tera  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(peta  ## Mass);     \
	BKSGE_UNITS_DECLARE_MASS_DENSITY_2(exa   ## Mass)

BKSGE_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX(gram);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX(grams);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(tonne);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(tonnes);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(pound);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(pounds);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(ounce);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(ounces);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(grain);
BKSGE_UNITS_DECLARE_MASS_DENSITY_2(grains);

#undef BKSGE_UNITS_DECLARE_MASS_DENSITY
#undef BKSGE_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX
#undef BKSGE_UNITS_DECLARE_MASS_DENSITY_2
#undef BKSGE_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MASS_DENSITY_HPP
