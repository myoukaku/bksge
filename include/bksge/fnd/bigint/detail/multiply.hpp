/**
 *	@file	multiply.hpp
 *
 *	@brief	multiply 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MULTIPLY_HPP
#define BKSGE_FND_BIGINT_DETAIL_MULTIPLY_HPP

#include <bksge/fnd/bigint/detail/make_sized_unsigned.hpp>
#include <bksge/fnd/bigint/detail/get_digits.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bigint/detail/add.hpp>
#include <bksge/fnd/bigint/detail/shift_left.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR VectorType
multiply(VectorType const& lhs, VectorType const& rhs)
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;
	using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

	auto const NA = bigint_algo::get_digits(lhs);
	if (NA == 0)
	{
		return {0};
	}

	auto const NB = bigint_algo::get_digits(rhs);
	if (NB == 0)
	{
		return {0};
	}

	VectorType result {0};

	for (bksge::size_t i = 0; i < NA; ++i)
	{
		for (bksge::size_t j = 0; j < NB; ++j)
		{
			auto t = (double_element_type(lhs[i]) * rhs[j]);
			auto tmp = bigint_algo::construct_from_integral<VectorType>(t);
			bigint_algo::add(result, bigint_algo::shift_left(tmp, i+j));
		}
	}

	return result;
}

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR VectorType
multiply(VectorType const& lhs, Integral rhs)
{
	return multiply(lhs, bigint_algo::construct_from_integral<VectorType>(rhs));
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MULTIPLY_HPP
