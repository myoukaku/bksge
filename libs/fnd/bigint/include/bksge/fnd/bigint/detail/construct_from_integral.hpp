/**
 *	@file	construct_from_integral.hpp
 *
 *	@brief	construct_from_integral 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_INTEGRAL_HPP
#define BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_INTEGRAL_HPP

#include <bksge/fnd/bigint/detail/construct_from_size.hpp>
#include <bksge/fnd/bigint/detail/lo.hpp>
#include <bksge/fnd/bigint/detail/hi.hpp>
#include <bksge/fnd/bigint/detail/remove_leading_zeros.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

namespace construct_from_integral_detail
{

template <
	typename VectorType,
	typename ElementType,
	typename Integral,
	std::size_t N = sizeof(Integral) / sizeof(ElementType),
	typename = bksge::enable_if_t<N != 0>
>
inline BKSGE_CXX14_CONSTEXPR VectorType
construct_from_integral_impl(Integral value, bksge::detail::overload_priority<1>)
{
	auto ret = bigint_algo::construct_from_size<VectorType>(N);
	auto const size = bksge::ranges::size(ret);
	for (std::size_t i = 0; i < size && value != 0; ++i)
	{
		ret[i] = bigint_algo::lo<ElementType>(value);
		value  = bigint_algo::hi<ElementType>(value);
	}
	bigint_algo::remove_leading_zeros(ret);
	return ret;
}

template <
	typename VectorType,
	typename ElementType,
	typename Integral
>
inline BKSGE_CXX14_CONSTEXPR VectorType
construct_from_integral_impl(Integral value, bksge::detail::overload_priority<0>)
{
	return {static_cast<ElementType>(value)};
}

}	// namespace construct_from_integral_detail

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR VectorType
construct_from_integral(Integral value)
{
	return construct_from_integral_detail::construct_from_integral_impl<
		VectorType,
		bksge::ranges::range_value_t<VectorType>
	>(value, bksge::detail::overload_priority<1>{});
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_INTEGRAL_HPP
