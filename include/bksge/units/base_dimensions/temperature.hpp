/**
 *	@file	temperature.hpp
 *
 *	@brief	temperature_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct temperature_base_dimension;

template <>
struct base_dimension_traits<temperature_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 5;
};

/**
 *	@brief	温度: Θ
 */
using temperature_dimension =
	derived_dimension<
		dimension_holder<temperature_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP
