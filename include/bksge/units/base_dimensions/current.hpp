/**
 *	@file	current.hpp
 *
 *	@brief	current_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_CURRENT_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_CURRENT_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct current_base_dimension;

template <>
struct base_dimension_traits<current_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 4;
};

/**
 *	@brief	電流: I
 */
using current_dimension =
	derived_dimension<
		dimension_holder<current_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_CURRENT_HPP
