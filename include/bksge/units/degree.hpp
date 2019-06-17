/**
 *	@file	degree.hpp
 *
 *	@brief	degree の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_DEGREE_HPP
#define BKSGE_UNITS_DEGREE_HPP

#include <bksge/units/base_dimensions/angle.hpp>
#include <bksge/units/detail/quantity.hpp>
#include <bksge/units/radian.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 度数法
template <typename T> using degree  = quantity<T, angle_dimension, std::ratio<31415926535897932LL, 1800000000000000000LL>>;
template <typename T> using degrees = degree<T>;

/**
 *	@brief	sinのオーバーロード
 */
template <typename T>
inline T sin(degrees<T> const& d)
{
	return sin(radians<T>(d));
}

/**
 *	@brief	cosのオーバーロード
 */
template <typename T>
inline T cos(degrees<T> const& d)
{
	return cos(radians<T>(d));
}

/**
 *	@brief	tanのオーバーロード
 */
template <typename T>
inline T tan(degrees<T> const& d)
{
	return tan(radians<T>(d));
}

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_DEGREE_HPP
