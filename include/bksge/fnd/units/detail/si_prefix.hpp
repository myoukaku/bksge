/**
 *	@file	si_prefix.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_SI_PREFIX_HPP
#define BKSGE_FND_UNITS_DETAIL_SI_PREFIX_HPP

#include <cstdint>	// INTMAX_MAX
#include <ratio>

#define BKSGE_UNITS_SI_PREFIX_2(Name, Ratio) \
	template <typename T> using Ratio ## Name = decltype(Name<T>() * std::Ratio())

#if (INTMAX_MAX / 1000000000) >= 1000000000000		// INTMAX_MAX >= (1000000000000000000000)
#define BKSGE_UNITS_SI_PREFIX_ZEPTO(Name)	BKSGE_UNITS_SI_PREFIX_2(Name, zepto)
#define BKSGE_UNITS_SI_PREFIX_ZETTA(Name)	BKSGE_UNITS_SI_PREFIX_2(Name, zetta)
#else
#define BKSGE_UNITS_SI_PREFIX_ZEPTO(Name)
#define BKSGE_UNITS_SI_PREFIX_ZETTA(Name)
#endif

#if (INTMAX_MAX / 1000000000) >= 1000000000000000	// INTMAX_MAX >= (1000000000000000000000000)
#define BKSGE_UNITS_SI_PREFIX_YOCTO(Name)	BKSGE_UNITS_SI_PREFIX_2(Name, yocto)
#define BKSGE_UNITS_SI_PREFIX_YOTTA(Name)	BKSGE_UNITS_SI_PREFIX_2(Name, yotta)
#else
#define BKSGE_UNITS_SI_PREFIX_YOCTO(Name)
#define BKSGE_UNITS_SI_PREFIX_YOTTA(Name)
#endif

/**
 *	@brief	SI接頭辞
 */
#define BKSGE_UNITS_SI_PREFIX(Name)       \
	BKSGE_UNITS_SI_PREFIX_YOCTO(Name);    \
	BKSGE_UNITS_SI_PREFIX_ZEPTO(Name);    \
	BKSGE_UNITS_SI_PREFIX_2(Name, atto);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, femto); \
	BKSGE_UNITS_SI_PREFIX_2(Name, pico);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, nano);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, micro); \
	BKSGE_UNITS_SI_PREFIX_2(Name, milli); \
	BKSGE_UNITS_SI_PREFIX_2(Name, centi); \
	BKSGE_UNITS_SI_PREFIX_2(Name, deci);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, deca);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, hecto); \
	BKSGE_UNITS_SI_PREFIX_2(Name, kilo);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, mega);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, giga);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, tera);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, peta);  \
	BKSGE_UNITS_SI_PREFIX_2(Name, exa);   \
	BKSGE_UNITS_SI_PREFIX_ZETTA(Name);    \
	BKSGE_UNITS_SI_PREFIX_YOTTA(Name)

#endif // BKSGE_FND_UNITS_DETAIL_SI_PREFIX_HPP
