/**
 *	@file	mass.hpp
 *
 *	@brief	mass_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_MASS_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_MASS_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct mass_base_dimension;

template <>
struct base_dimension_traits<mass_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 2;
};

/**
 *	@brief	質量: M
 */
using mass_dimension =
	derived_dimension<
		dimension_holder<mass_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_MASS_HPP
