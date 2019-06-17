/**
 *	@file	angle.hpp
 *
 *	@brief	angle_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_ANGLE_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_ANGLE_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct angle_base_dimension;

template <>
struct base_dimension_traits<angle_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 8;
};

/**
 *	@brief	平面角
 */
using angle_dimension =
	derived_dimension<
		dimension_holder<angle_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_ANGLE_HPP
