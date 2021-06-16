/**
 *	@file	steradian.hpp
 *
 *	@brief	steradian の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_STERADIAN_HPP
#define BKSGE_FND_UNITS_STERADIAN_HPP

#include <bksge/fnd/units/base_dimensions/solid_angle.hpp>
#include <bksge/fnd/units/detail/quantity.hpp>

namespace bksge
{

namespace units
{

// ステラジアン
template <typename T> using steradian  = quantity<T, solid_angle_dimension>;
template <typename T> using steradians = steradian<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_STERADIAN_HPP
