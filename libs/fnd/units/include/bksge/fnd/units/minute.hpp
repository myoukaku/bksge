/**
 *	@file	minute.hpp
 *
 *	@brief	minute の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MINUTE_HPP
#define BKSGE_FND_UNITS_MINUTE_HPP

#include <bksge/fnd/units/second.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// 分
template <typename T> using minute  = decltype(second<T>() * bksge::ratio<60>());
template <typename T> using minutes = minute<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MINUTE_HPP
