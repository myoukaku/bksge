/**
 *	@file	foot_poundal.hpp
 *
 *	@brief	foot_poundal の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_FOOT_POUNDAL_HPP
#define BKSGE_FND_UNITS_FOOT_POUNDAL_HPP

#include <bksge/fnd/units/poundal.hpp>
#include <bksge/fnd/units/foot.hpp>

namespace bksge
{

namespace units
{

// フィート・パウンダル
template <typename T> using foot_poundal = decltype(poundal<T>() * foot<T>());
template <typename T> using feet_poundal = foot_poundal<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_FOOT_POUNDAL_HPP
