/**
 *	@file	calorie.hpp
 *
 *	@brief	calorie の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_CALORIE_HPP
#define BKSGE_FND_UNITS_CALORIE_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/joule.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// カロリー(正確に4.184ジュール)
template <typename T> using calorie  = decltype(joule<T>() * std::ratio<4184, 1000>());
template <typename T> using calories = calorie<T>;
BKSGE_UNITS_SI_PREFIX(calorie);
BKSGE_UNITS_SI_PREFIX(calories);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_CALORIE_HPP
