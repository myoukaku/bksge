/**
 *	@file	radian.hpp
 *
 *	@brief	radian の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_RADIAN_HPP
#define BKSGE_FND_UNITS_RADIAN_HPP

#include <bksge/fnd/units/base_dimensions/angle.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/tan.hpp>

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
	return bksge::sin(r.value());
}

/**
 *	@brief	cosのオーバーロード
 */
template <typename T>
inline T cos(radians<T> const& r)
{
	return bksge::cos(r.value());
}

/**
 *	@brief	tanのオーバーロード
 */
template <typename T>
inline T tan(radians<T> const& r)
{
	return bksge::tan(r.value());
}

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_RADIAN_HPP
