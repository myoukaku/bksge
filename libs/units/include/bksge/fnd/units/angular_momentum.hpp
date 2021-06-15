/**
 *	@file	angular_momentum.hpp
 *
 *	@brief	angular_momentum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_ANGULAR_MOMENTUM_HPP
#define BKSGE_FND_UNITS_ANGULAR_MOMENTUM_HPP

#include <bksge/fnd/units/newton.hpp>
#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ニュートンメートル秒(角運動量の単位)
template <typename T> using newton_metre_second  = decltype(newton<T>() * metre<T>() * second<T>());
template <typename T> using newton_metre_seconds = newton_metre_second<T>;
template <typename T> using newton_meter_second  = newton_metre_second<T>;
template <typename T> using newton_meter_seconds = newton_metre_second<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_ANGULAR_MOMENTUM_HPP
