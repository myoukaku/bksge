/**
 *	@file	compare.hpp
 *
 *	@brief	compare 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_COMPARE_HPP
#define BKSGE_FND_BIGINT_DETAIL_COMPARE_HPP

#include <bksge/fnd/bigint/detail/get_digits.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR int
compare(VectorType const& lhs, VectorType const& rhs) noexcept
{
	auto const NA = bigint_algo::get_digits(lhs);
	auto const NB = bigint_algo::get_digits(rhs);

	if (NA > NB) { return  1; }
	if (NA < NB) { return -1; }

	for (std::size_t i = 0; i < NA; ++i)
	{
		auto const j = NA - i - 1;
		if (lhs[j] > rhs[j]) { return  1; }
		if (lhs[j] < rhs[j]) { return -1; }
	}

	return 0;
}

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR int
compare(VectorType const& lhs, Integral rhs) noexcept
{
	return compare(lhs, bigint_algo::construct_from_integral<VectorType>(rhs));
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_COMPARE_HPP
