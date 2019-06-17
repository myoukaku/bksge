/**
 *	@file	luminous_intensity.hpp
 *
 *	@brief	luminous_intensity_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct luminous_intensity_base_dimension;

template <>
struct base_dimension_traits<luminous_intensity_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 7;
};

/**
 *	@brief	光度: J
 */
using luminous_intensity_dimension =
	derived_dimension<
		dimension_holder<luminous_intensity_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP
