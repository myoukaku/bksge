/**
 *	@file	derived_dimension.hpp
 *
 *	@brief	derived_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_DETAIL_DERIVED_DIMENSION_HPP
#define BKSGE_UNITS_DETAIL_DERIVED_DIMENSION_HPP

#include <bksge/units/detail/derived_dimension_fwd.hpp>
#include <bksge/type_traits/nth.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

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

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename... Types>
struct tuple_size<bksge::units::derived_dimension<Types...>>
	: public std::integral_constant<std::size_t, sizeof...(Types)>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename... Types>
struct tuple_element<I, bksge::units::derived_dimension<Types...>>
{
public:
	using type = bksge::nth_t<I, Types...>;
};

}	// namespace std

#endif // BKSGE_UNITS_DETAIL_DERIVED_DIMENSION_HPP
