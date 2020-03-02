/**
 *	@file	get_dimension_power.hpp
 *
 *	@brief	get_dimension_power の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_GET_DIMENSION_POWER_HPP
#define BKSGE_FND_UNITS_DETAIL_GET_DIMENSION_POWER_HPP

#include <bksge/fnd/units/detail/derived_dimension_fwd.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>

namespace bksge
{

namespace units
{

/**
 *	@brief	derived_dimensionにおける、base_dimensionの指数を得る
 */
template <typename DerivedDimension, typename BaseDimension>
struct get_dimension_power;

template <typename B0, typename... Bs, typename BaseDimension>
struct get_dimension_power<derived_dimension<B0, Bs...>, BaseDimension>
{
	BKSGE_STATIC_CONSTEXPR int value =
		bksge::is_same<typename B0::type, BaseDimension>::value ?
			B0::power :
		get_dimension_power<derived_dimension<Bs...>, BaseDimension>::value;
};

template <typename BaseDimension>
struct get_dimension_power<derived_dimension<>, BaseDimension>
{
	BKSGE_STATIC_CONSTEXPR int value = 0;
};

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DETAIL_GET_DIMENSION_POWER_HPP
