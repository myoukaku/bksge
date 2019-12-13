/**
 *	@file	information.hpp
 *
 *	@brief	information_base_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_BASE_DIMENSIONS_INFORMATION_HPP
#define BKSGE_FND_UNITS_BASE_DIMENSIONS_INFORMATION_HPP

#include <bksge/fnd/units/detail/base_dimension_traits.hpp>
#include <bksge/fnd/units/detail/derived_dimension.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace units
{

struct information_base_dimension;

template <>
struct base_dimension_traits<information_base_dimension>
{
	BKSGE_STATIC_CONSTEXPR int order = 10;
};

/**
 *	@brief	情報量
 */
using information_dimension =
	derived_dimension<
		dimension_holder<information_base_dimension>
	>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_BASE_DIMENSIONS_INFORMATION_HPP
