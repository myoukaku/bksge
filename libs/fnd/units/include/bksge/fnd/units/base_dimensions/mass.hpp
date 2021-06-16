/**
 *	@file	mass.hpp
 *
 *	@brief	mass_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_BASE_DIMENSIONS_MASS_HPP
#define BKSGE_FND_UNITS_BASE_DIMENSIONS_MASS_HPP

#include <bksge/fnd/units/detail/base_dimension_traits.hpp>
#include <bksge/fnd/units/detail/derived_dimension.hpp>
#include <bksge/fnd/config.hpp>

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

#endif // BKSGE_FND_UNITS_BASE_DIMENSIONS_MASS_HPP
