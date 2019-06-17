/**
 *	@file	dimension_multiply.hpp
 *
 *	@brief	dimension_multiply の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_DETAIL_DIMENSION_MULTIPLY_HPP
#define BKSGE_UNITS_DETAIL_DIMENSION_MULTIPLY_HPP

#include <bksge/units/detail/derived_dimension_fwd.hpp>
#include <bksge/units/detail/make_derived_dimension.hpp>

namespace bksge
{

namespace units
{

namespace detail
{

template <typename D1, typename D2>
struct dimension_multiply;

template <typename... D1, typename... D2>
struct dimension_multiply<derived_dimension<D1...>, derived_dimension<D2...>>
	: public make_derived_dimension<D1..., D2...>
{};

}	// namespace detail

/**
 *	@brief	derived_dimension同士を乗算して新しいderived_dimensionを得る
 */
template <typename D1, typename D2>
using dimension_multiply = typename detail::dimension_multiply<D1, D2>::type;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_DETAIL_DIMENSION_MULTIPLY_HPP
