/**
 *	@file	luminous_intensity.hpp
 *
 *	@brief	luminous_intensity_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP
#define BKSGE_FND_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP

#include <bksge/fnd/units/detail/base_dimension_traits.hpp>
#include <bksge/fnd/units/detail/derived_dimension.hpp>
#include <bksge/fnd/config.hpp>

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

#endif // BKSGE_FND_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP
