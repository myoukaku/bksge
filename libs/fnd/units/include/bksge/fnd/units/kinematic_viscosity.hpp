/**
 *	@file	kinematic_viscosity.hpp
 *
 *	@brief	kinematic_viscosity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_KINEMATIC_VISCOSITY_HPP
#define BKSGE_FND_UNITS_KINEMATIC_VISCOSITY_HPP

#include <bksge/fnd/units/metre.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// 平方メートル毎秒(動粘度の単位)
template <typename T> using square_metre_per_second  = decltype(metre<T>() * metre<T>() / second<T>());
template <typename T> using square_metres_per_second = square_metre_per_second<T>;
template <typename T> using square_meter_per_second  = square_metre_per_second<T>;
template <typename T> using square_meters_per_second = square_metre_per_second<T>;

}	// namespace units

}	// namespace bksge

#include <bksge/fnd/units/stokes.hpp>

#endif // BKSGE_FND_UNITS_KINEMATIC_VISCOSITY_HPP
