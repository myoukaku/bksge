/**
 *	@file	amount.hpp
 *
 *	@brief	amount_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_BASE_DIMENSIONS_AMOUNT_HPP
#define BKSGE_UNITS_BASE_DIMENSIONS_AMOUNT_HPP

#include <bksge/units/detail/base_dimension_traits.hpp>
#include <bksge/units/detail/derived_dimension.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace units
{

struct amount_base_dimension;

template <>
struct base_dimension_traits<amount_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 6;
};

/**
 *	@brief	物質量: N
 */
using amount_dimension =
	derived_dimension<
		dimension_holder<amount_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_BASE_DIMENSIONS_AMOUNT_HPP
