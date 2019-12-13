/**
 *	@file	acceleration.hpp
 *
 *	@brief	acceleration の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ACCELERATION_HPP
#define BKSGE_FND_UNITS_ACCELERATION_HPP

#include <bksge/fnd/units/length.hpp>
#include <bksge/fnd/units/second.hpp>
#include <bksge/fnd/units/minute.hpp>
#include <bksge/fnd/units/hour.hpp>
#include <bksge/fnd/units/gal.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

#define BKSGE_UNITS_DECLARE_ACCELERATION_1(Length, Time)	\
	template <typename T> using Length ## _per_ ## Time ## _squared = decltype(Length<T>() / Time<T>() / Time<T>())

#define BKSGE_UNITS_DECLARE_ACCELERATION_2(Length, Time)	\
	BKSGE_UNITS_DECLARE_ACCELERATION_1(Length, Time);	\
	BKSGE_UNITS_SI_PREFIX(Length ## _per_ ## Time ## _squared)

#define BKSGE_UNITS_DECLARE_ACCELERATION_3(F, Length)	\
	F(Length, second);	\
	F(Length, minute);	\
	F(Length, hour)

#define BKSGE_UNITS_DECLARE_ACCELERATION(Length)	\
	BKSGE_UNITS_DECLARE_ACCELERATION_3(BKSGE_UNITS_DECLARE_ACCELERATION_1, Length)

#define BKSGE_UNITS_DECLARE_ACCELERATION_SI_PREFIX(Length) \
	BKSGE_UNITS_DECLARE_ACCELERATION_3(BKSGE_UNITS_DECLARE_ACCELERATION_2, Length)

// メートル毎秒毎秒
BKSGE_UNITS_DECLARE_ACCELERATION_SI_PREFIX(metre);
BKSGE_UNITS_DECLARE_ACCELERATION_SI_PREFIX(metres);
BKSGE_UNITS_DECLARE_ACCELERATION_SI_PREFIX(meter);
BKSGE_UNITS_DECLARE_ACCELERATION_SI_PREFIX(meters);

// インチ毎秒毎秒
BKSGE_UNITS_DECLARE_ACCELERATION(inch);
BKSGE_UNITS_DECLARE_ACCELERATION(inches);

// フィート毎秒毎秒
BKSGE_UNITS_DECLARE_ACCELERATION(foot);
BKSGE_UNITS_DECLARE_ACCELERATION(feet);

// ヤード毎秒毎秒
BKSGE_UNITS_DECLARE_ACCELERATION(yard);
BKSGE_UNITS_DECLARE_ACCELERATION(yards);

// チェーン毎秒毎秒
BKSGE_UNITS_DECLARE_ACCELERATION(chain);
BKSGE_UNITS_DECLARE_ACCELERATION(chains);

// ハロン毎秒毎秒
BKSGE_UNITS_DECLARE_ACCELERATION(furlong);
BKSGE_UNITS_DECLARE_ACCELERATION(furlongs);

// マイル毎秒毎秒
BKSGE_UNITS_DECLARE_ACCELERATION(mile);
BKSGE_UNITS_DECLARE_ACCELERATION(miles);

#undef BKSGE_UNITS_DECLARE_ACCELERATION_1
#undef BKSGE_UNITS_DECLARE_ACCELERATION_2
#undef BKSGE_UNITS_DECLARE_ACCELERATION_3
#undef BKSGE_UNITS_DECLARE_ACCELERATION
#undef BKSGE_UNITS_DECLARE_ACCELERATION_SI_PREFIX

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ACCELERATION_HPP
