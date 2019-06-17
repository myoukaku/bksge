/**
 *	@file	area.hpp
 *
 *	@brief	area の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_AREA_HPP
#define BKSGE_UNITS_AREA_HPP

#include <bksge/units/length.hpp>

namespace bksge
{

namespace units
{

#define BKSGE_UNITS_DECLARE_AREA(Name)	\
	template <typename T> using square_ ## Name = decltype(Name<T>() * Name<T>())

#define BKSGE_UNITS_DECLARE_AREA_SI_PREFIX(Name) \
	BKSGE_UNITS_DECLARE_AREA(atto  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(femto ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(pico  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(nano  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(micro ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(milli ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(centi ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(deci  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(Name);              \
	BKSGE_UNITS_DECLARE_AREA(deca  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(hecto ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(kilo  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(mega  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(giga  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(tera  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(peta  ## Name);     \
	BKSGE_UNITS_DECLARE_AREA(exa   ## Name)

// 平方メートル
BKSGE_UNITS_DECLARE_AREA_SI_PREFIX(metre);
BKSGE_UNITS_DECLARE_AREA_SI_PREFIX(metres);
BKSGE_UNITS_DECLARE_AREA_SI_PREFIX(meter);
BKSGE_UNITS_DECLARE_AREA_SI_PREFIX(meters);

// 平方インチ (正確に 645.16 平方ミリメートル)
BKSGE_UNITS_DECLARE_AREA(inch);
BKSGE_UNITS_DECLARE_AREA(inches);

// 平方フィート (144平方インチ = 正確に 929.0304 平方センチメートル)
BKSGE_UNITS_DECLARE_AREA(foot);
BKSGE_UNITS_DECLARE_AREA(feet);

// 平方ヤード (9 平方フィート = 正確に 0.83612736 平方メートル)
BKSGE_UNITS_DECLARE_AREA(yard);
BKSGE_UNITS_DECLARE_AREA(yards);

// 平方チェーン
BKSGE_UNITS_DECLARE_AREA(chain);
BKSGE_UNITS_DECLARE_AREA(chains);

// 平方ハロン
BKSGE_UNITS_DECLARE_AREA(furlong);
BKSGE_UNITS_DECLARE_AREA(furlongs);

// 平方マイル (27878400 平方フィート = 正確に 2.5899881103 平方キロメートル)
BKSGE_UNITS_DECLARE_AREA(mile);
BKSGE_UNITS_DECLARE_AREA(miles);

#undef BKSGE_UNITS_DECLARE_AREA
#undef BKSGE_UNITS_DECLARE_AREA_SI_PREFIX

}	// namespace units

}	// namespace bksge

#include <bksge/units/acre.hpp>
#include <bksge/units/are.hpp>
#include <bksge/units/hectare.hpp>

#endif // BKSGE_UNITS_AREA_HPP
