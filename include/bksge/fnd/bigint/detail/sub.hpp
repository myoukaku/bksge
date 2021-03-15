/**
 *	@file	sub.hpp
 *
 *	@brief	sub 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_SUB_HPP
#define BKSGE_FND_BIGINT_DETAIL_SUB_HPP

#include <bksge/fnd/bigint/detail/make_sized_signed.hpp>
#include <bksge/fnd/bigint/detail/get_digits.hpp>
#include <bksge/fnd/bigint/detail/resize.hpp>
#include <bksge/fnd/bigint/detail/lo.hpp>
#include <bksge/fnd/bigint/detail/hi.hpp>
#include <bksge/fnd/bigint/detail/remove_leading_zeros.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR void
sub(VectorType& lhs, VectorType const& rhs)
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;
	using double_element_type = make_sized_signed_t<sizeof(element_type)*2>;

	auto const NA = bigint_algo::get_digits(lhs);
	auto const NB = bigint_algo::get_digits(rhs);

	bigint_algo::resize(lhs, bksge::max(NA, NB) + 0);
	auto const N = ranges::size(lhs);

	double_element_type carry = 0;
	bksge::size_t i = 0;
	for (; i < NB; ++i)
	{
		auto t = double_element_type(lhs[i]) - rhs[i] + carry;
		lhs[i] = bigint_algo::lo<element_type>(t);
		carry  = bigint_algo::hi<element_type>(t);
	}
	for (; i < N && carry != 0; ++i)
	{
		auto t = double_element_type(lhs[i]) + carry;
		lhs[i] = bigint_algo::lo<element_type>(t);
		carry  = bigint_algo::hi<element_type>(t);
	}

	bigint_algo::remove_leading_zeros(lhs);
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_SUB_HPP
