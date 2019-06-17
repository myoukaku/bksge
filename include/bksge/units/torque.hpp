/**
 *	@file	torque.hpp
 *
 *	@brief	torque の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_TORQUE_HPP
#define BKSGE_UNITS_TORQUE_HPP

#include <bksge/units/newton.hpp>
#include <bksge/units/metre.hpp>

namespace bksge
{

namespace units
{

// ニュートンメートル(力のモーメント（トルク）の単位)
template <typename T> using newton_metre  = decltype(newton<T>() * metre<T>());
template <typename T> using newton_metres = newton_metre<T>;
template <typename T> using newton_meter  = newton_metre<T>;
template <typename T> using newton_meters = newton_metre<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_TORQUE_HPP
