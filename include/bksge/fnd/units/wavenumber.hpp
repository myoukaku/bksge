/**
 *	@file	wavenumber.hpp
 *
 *	@brief	wavenumber の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_WAVENUMBER_HPP
#define BKSGE_FND_UNITS_WAVENUMBER_HPP

#include <bksge/fnd/units/length.hpp>

namespace bksge
{

namespace units
{

#define BKSGE_UNITS_DECLARE_WAVENUMBER(Length)	\
	template <typename T> using reciprocal_ ## Length  = decltype(T() / Length<T>())

#define BKSGE_UNITS_DECLARE_WAVENUMBER_SI_PREFIX(Name) \
	BKSGE_UNITS_DECLARE_WAVENUMBER(atto  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(femto ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(pico  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(nano  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(micro ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(milli ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(centi ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(deci  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(Name);              \
	BKSGE_UNITS_DECLARE_WAVENUMBER(deca  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(hecto ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(kilo  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(mega  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(giga  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(tera  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(peta  ## Name);     \
	BKSGE_UNITS_DECLARE_WAVENUMBER(exa   ## Name)

// 毎メートル
BKSGE_UNITS_DECLARE_WAVENUMBER_SI_PREFIX(metre);
BKSGE_UNITS_DECLARE_WAVENUMBER_SI_PREFIX(metres);
BKSGE_UNITS_DECLARE_WAVENUMBER_SI_PREFIX(meter);
BKSGE_UNITS_DECLARE_WAVENUMBER_SI_PREFIX(meters);

BKSGE_UNITS_DECLARE_WAVENUMBER(inch);
BKSGE_UNITS_DECLARE_WAVENUMBER(inches);
BKSGE_UNITS_DECLARE_WAVENUMBER(foot);
BKSGE_UNITS_DECLARE_WAVENUMBER(feet);
BKSGE_UNITS_DECLARE_WAVENUMBER(yard);
BKSGE_UNITS_DECLARE_WAVENUMBER(yards);
BKSGE_UNITS_DECLARE_WAVENUMBER(chain);
BKSGE_UNITS_DECLARE_WAVENUMBER(chains);
BKSGE_UNITS_DECLARE_WAVENUMBER(furlong);
BKSGE_UNITS_DECLARE_WAVENUMBER(furlongs);
BKSGE_UNITS_DECLARE_WAVENUMBER(mile);
BKSGE_UNITS_DECLARE_WAVENUMBER(miles);

#undef BKSGE_UNITS_DECLARE_WAVENUMBER
#undef BKSGE_UNITS_DECLARE_WAVENUMBER_SI_PREFIX

}	// namespace units

}	// namespace bksge

#include <bksge/fnd/units/kayser.hpp>

#endif // BKSGE_FND_UNITS_WAVENUMBER_HPP
