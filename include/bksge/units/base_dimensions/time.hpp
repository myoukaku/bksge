/**
 *	@file	time.hpp
 *
 *	@brief	time_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_TIME_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_TIME_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct time_base_dimension;

template <>
struct base_dimension_traits<time_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 3;
};

/**
 *	@brief	時間: T
 */
using time_dimension =
	derived_dimension<
		dimension_holder<time_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_TIME_HPP
