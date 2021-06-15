/**
 *	@file	angular_velocity.hpp
 *
 *	@brief	angular_velocity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ANGULAR_VELOCITY_HPP
#define BKSGE_FND_UNITS_ANGULAR_VELOCITY_HPP

#include <bksge/fnd/units/radian.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ラジアン毎秒(角速度の単位)
template <typename T> using radian_per_second  = decltype(radian<T>() / second<T>());
template <typename T> using radians_per_second = radian_per_second<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ANGULAR_VELOCITY_HPP
