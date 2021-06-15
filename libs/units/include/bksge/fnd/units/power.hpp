/**
 *	@file	power.hpp
 *
 *	@brief	power の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_POWER_HPP
#define BKSGE_FND_UNITS_POWER_HPP

#include <bksge/fnd/units/erg.hpp>
#include <bksge/fnd/units/foot_poundal.hpp>
#include <bksge/fnd/units/second.hpp>

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

#include <bksge/fnd/units/watt.hpp>

#endif // BKSGE_FND_UNITS_POWER_HPP
