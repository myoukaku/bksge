/**
 *	@file	power.hpp
 *
 *	@brief	power の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_POWER_HPP
#define BKSGE_UNITS_POWER_HPP

#include <bksge/units/erg.hpp>
#include <bksge/units/foot_poundal.hpp>
#include <bksge/units/second.hpp>

namespace bksge
{

namespace units
{

// エルグ毎秒
template <typename T> using erg_per_second  = decltype(erg<T>() / second<T>());
template <typename T> using ergs_per_second = erg_per_second<T>;

// フィート・パウンダル毎秒
template <typename T> using foot_poundal_per_second = decltype(foot_poundal<T>() / second<T>());
template <typename T> using feet_poundal_per_second = foot_poundal_per_second<T>;

}	// namespace units

}	// namespace bksge

#include <bksge/units/watt.hpp>

#endif // BKSGE_UNITS_POWER_HPP
