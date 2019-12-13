/**
 *	@file	day.hpp
 *
 *	@brief	day の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DAY_HPP
#define BKSGE_FND_UNITS_DAY_HPP

#include <bksge/fnd/units/hour.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 日
template <typename T> using day  = decltype(hour<T>() * std::ratio<24>());
template <typename T> using days = day<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DAY_HPP
