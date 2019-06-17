/**
 *	@file	radian.hpp
 *
 *	@brief	radian の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_RADIAN_HPP
#define BKSGE_UNITS_RADIAN_HPP

#include <bksge/units/base_dimensions/angle.hpp>
#include <bksge/units/detail/quantity.hpp>
#include <cmath>

namespace bksge
{

namespace units
{

// ラジアン
template <typename T> using radian  = quantity<T, angle_dimension>;
template <typename T> using radians = radian<T>;

/**
 *	@brief	sinのオーバーロード
 */
template <typename T>
inline T sin(radians<T> const& r)
{
	return std::sin(r.value());
}

/**
 *	@brief	cosのオーバーロード
 */
template <typename T>
inline T cos(radians<T> const& r)
{
	return std::cos(r.value());
}

/**
 *	@brief	tanのオーバーロード
 */
template <typename T>
inline T tan(radians<T> const& r)
{
	return std::tan(r.value());
}

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_RADIAN_HPP
