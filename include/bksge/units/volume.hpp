/**
 *	@file	volume.hpp
 *
 *	@brief	volume の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_VOLUME_HPP
#define BKSGE_UNITS_VOLUME_HPP

#include <bksge/units/length.hpp>

namespace bksge
{

namespace units
{

#define BKSGE_UNITS_DECLARE_VOLUME(Name)	\
	template <typename T> using cubic_ ## Name = decltype(Name<T>() * Name<T>() * Name<T>())

#define BKSGE_UNITS_DECLARE_VOLUME_SI_PREFIX(Name) \
	BKSGE_UNITS_DECLARE_VOLUME(atto  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(femto ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(pico  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(nano  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(micro ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(milli ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(centi ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(deci  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(Name);              \
	BKSGE_UNITS_DECLARE_VOLUME(deca  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(hecto ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(kilo  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(mega  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(giga  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(tera  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(peta  ## Name);     \
	BKSGE_UNITS_DECLARE_VOLUME(exa   ## Name)

// 立方メートル
BKSGE_UNITS_DECLARE_VOLUME_SI_PREFIX(metre);
BKSGE_UNITS_DECLARE_VOLUME_SI_PREFIX(metres);
BKSGE_UNITS_DECLARE_VOLUME_SI_PREFIX(meter);
BKSGE_UNITS_DECLARE_VOLUME_SI_PREFIX(meters);

// 立方インチ
BKSGE_UNITS_DECLARE_VOLUME(inch);
BKSGE_UNITS_DECLARE_VOLUME(inches);

// 立方フィート
BKSGE_UNITS_DECLARE_VOLUME(foot);
BKSGE_UNITS_DECLARE_VOLUME(feet);

// 立方ヤード
BKSGE_UNITS_DECLARE_VOLUME(yard);
BKSGE_UNITS_DECLARE_VOLUME(yards);

// 立方チェーン
BKSGE_UNITS_DECLARE_VOLUME(chain);
BKSGE_UNITS_DECLARE_VOLUME(chains);

// 立方ハロン
BKSGE_UNITS_DECLARE_VOLUME(furlong);
BKSGE_UNITS_DECLARE_VOLUME(furlongs);

// 立方マイル
BKSGE_UNITS_DECLARE_VOLUME(mile);
BKSGE_UNITS_DECLARE_VOLUME(miles);

#undef BKSGE_UNITS_DECLARE_VOLUME
#undef BKSGE_UNITS_DECLARE_VOLUME_SI_PREFIX

}	// namespace units

}	// namespace bksge

#include <bksge/units/litre.hpp>

#endif // BKSGE_UNITS_VOLUME_HPP
