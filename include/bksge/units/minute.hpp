/**
 *	@file	minute.hpp
 *
 *	@brief	minute の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_MINUTE_HPP
#define BKSGE_UNITS_MINUTE_HPP

#include <bksge/units/second.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 分
template <typename T> using minute  = decltype(second<T>() * std::ratio<60>());
template <typename T> using minutes = minute<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_MINUTE_HPP
