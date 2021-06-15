/**
 *	@file	angular_acceleration.hpp
 *
 *	@brief	angular_acceleration の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ANGULAR_ACCELERATION_HPP
#define BKSGE_FND_UNITS_ANGULAR_ACCELERATION_HPP

#include <bksge/fnd/units/radian.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ラジアン毎秒毎秒(角加速度の単位)
template <typename T> using radian_per_second_squared  = decltype(radian<T>() / second<T>() / second<T>());
template <typename T> using radians_per_second_squared = radian_per_second_squared<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ANGULAR_ACCELERATION_HPP
