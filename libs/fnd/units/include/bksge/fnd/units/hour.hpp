/**
 *	@file	hour.hpp
 *
 *	@brief	hour の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_HOUR_HPP
#define BKSGE_FND_UNITS_HOUR_HPP

#include <bksge/fnd/units/minute.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// 時
template <typename T> using hour  = decltype(minute<T>() * bksge::ratio<60>());
template <typename T> using hours = hour<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_HOUR_HPP
