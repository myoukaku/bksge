/**
 *	@file	hour.hpp
 *
 *	@brief	hour の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_HOUR_HPP
#define BKSGE_UNITS_HOUR_HPP

#include <bksge/units/minute.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 時
template <typename T> using hour  = decltype(minute<T>() * std::ratio<60>());
template <typename T> using hours = hour<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_HOUR_HPP
