/**
 *	@file	solid_angle.hpp
 *
 *	@brief	solid_angle_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_SOLID_ANGLE_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_SOLID_ANGLE_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct solid_angle_base_dimension;

template <>
struct base_dimension_traits<solid_angle_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 9;
};

/**
 *	@brief	立体角
 */
using solid_angle_dimension =
	derived_dimension<
		dimension_holder<solid_angle_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_SOLID_ANGLE_HPP
