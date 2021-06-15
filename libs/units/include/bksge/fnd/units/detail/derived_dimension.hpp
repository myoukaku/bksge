/**
 *	@file	derived_dimension.hpp
 *
 *	@brief	derived_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_DERIVED_DIMENSION_HPP
#define BKSGE_FND_UNITS_DETAIL_DERIVED_DIMENSION_HPP

#include <bksge/fnd/units/detail/derived_dimension_fwd.hpp>
#include <bksge/fnd/type_traits/nth.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace units
{

template <typename Dimension, int Power>
struct dimension_holder
{
	using type = Dimension;
	BKSGE_STATIC_CONSTEXPR int power = Power;
};

template <typename... BaseDimensions>
struct derived_dimension
{
//	using type = typename make_derived_dimension<BaseDimensions...>::type;
};

}	// namespace units

}	// namespace bksge

namespace BKSGE_TUPLE_NAMESPACE
{

/**
 *	@brief	tuple_size
 */
template <typename... Types>
struct tuple_size<bksge::units::derived_dimension<Types...>>
	: public bksge::integral_constant<bksge::size_t, sizeof...(Types)>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename... Types>
struct tuple_element<I, bksge::units::derived_dimension<Types...>>
{
public:
	using type = bksge::nth_t<I, Types...>;
};

}	// namespace BKSGE_TUPLE_NAMESPACE

#endif // BKSGE_FND_UNITS_DETAIL_DERIVED_DIMENSION_HPP
