/**
 *	@file	surface_density.hpp
 *
 *	@brief	surface_density の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_SURFACE_DENSITY_HPP
#define BKSGE_UNITS_SURFACE_DENSITY_HPP

#include <bksge/units/mass.hpp>
#include <bksge/units/area.hpp>

namespace bksge
{

namespace units
{

#define BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, Area) \
	template <typename T> using Mass ## _per_ ## Area = decltype(Mass<T>() / Area<T>())

#define BKSGE_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX(Mass, C, Length) \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## atto  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## femto ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## pico  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## nano  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## micro ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## milli ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## centi ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## deci  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## Length);            \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## deca  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## hecto ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## kilo  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## mega  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## giga  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## tera  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## peta  ## Length);   \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## exa   ## Length)

#define BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(Mass)                      \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX(Mass, square_, metre); \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX(Mass, square_, meter); \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_inch);              \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_foot);              \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_chain);             \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_furlong);           \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_yard);              \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_mile);              \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, are);                      \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, hectare);                  \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY(Mass, acre)

#define BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX(Mass) \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(atto  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(femto ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(pico  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(nano  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(micro ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(milli ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(centi ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(deci  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(Mass);              \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(deca  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(hecto ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(kilo  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(mega  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(giga  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(tera  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(peta  ## Mass);     \
	BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(exa   ## Mass)

BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX(gram);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX(grams);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(tonne);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(tonnes);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(pound);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(pounds);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(ounce);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(ounces);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(grain);
BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2(grains);

#undef BKSGE_UNITS_DECLARE_SURFACE_DENSITY
#undef BKSGE_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX
#undef BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2
#undef BKSGE_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_SURFACE_DENSITY_HPP
