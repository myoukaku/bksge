/**
 *	@file	year.hpp
 *
 *	@brief	year の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_YEAR_HPP
#define BKSGE_FND_UNITS_YEAR_HPP

#include <bksge/fnd/units/day.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 年　= 365.25 日	(ユリウス年)
template <typename T> using year  = decltype(day<T>() * std::ratio<36525, 100>());
template <typename T> using years = year<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_YEAR_HPP
