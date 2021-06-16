/**
 *	@file	dimension_inverse.hpp
 *
 *	@brief	dimension_inverse の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_DIMENSION_INVERSE_HPP
#define BKSGE_FND_UNITS_DETAIL_DIMENSION_INVERSE_HPP

#include <bksge/fnd/units/detail/derived_dimension_fwd.hpp>
#include <bksge/fnd/units/detail/make_derived_dimension.hpp>

namespace bksge
{

namespace units
{

namespace detail
{

// VisualStudio2013 でのコンパイラ内部エラーを避けるために必要
template <typename DimensionHolder>
struct dimension_inverse_helper
{
	using type = dimension_holder<typename DimensionHolder::type, -DimensionHolder::power>;
};


template <typename D>
struct dimension_inverse;

template <typename... D>
struct dimension_inverse<derived_dimension<D...>>
	: public make_derived_dimension<
		typename dimension_inverse_helper<D>::type...
	>
{};

}	// namespace detail

/**
 *	@brief	derived_dimensionの逆数を得る
 */
template <typename D>
using dimension_inverse = typename detail::dimension_inverse<D>::type;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DETAIL_DIMENSION_INVERSE_HPP
