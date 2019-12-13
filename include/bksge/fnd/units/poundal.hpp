/**
 *	@file	poundal.hpp
 *
 *	@brief	poundal の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_POUNDAL_HPP
#define BKSGE_FND_UNITS_POUNDAL_HPP

#include <bksge/fnd/units/pound.hpp>
#include <bksge/fnd/units/foot.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// パウンダル(lb・ft/s^2)
template <typename T> using poundal  = decltype(pound<T>() * foot<T>() / second<T>() / second<T>());
template <typename T> using poundals = poundal<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_POUNDAL_HPP
