/**
 *	@file	length.hpp
 *
 *	@brief	length_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_LENGTH_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_LENGTH_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct length_base_dimension;

template <>
struct base_dimension_traits<length_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 1;
};

/**
 *	@brief	長さ: L
 */
using length_dimension =
	derived_dimension<
		dimension_holder<length_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_LENGTH_HPP
