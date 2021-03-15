/**
 *	@file	convert_radix.hpp
 *
 *	@brief	convert_radix 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_CONVERT_RADIX_HPP
#define BKSGE_FND_BIGINT_DETAIL_CONVERT_RADIX_HPP

#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bigint/detail/div_mod.hpp>
#include <bksge/fnd/bigint/detail/is_zero.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <
	std::size_t DstRadix,
	typename VectorType,
	typename ElementType = bksge::ranges::range_value_t<VectorType>
>
inline BKSGE_CXX14_CONSTEXPR bksge::vector<ElementType>
convert_radix(VectorType value)
{
	using ResultType = bksge::vector<ElementType>;

	auto const base = bigint_algo::construct_from_integral<VectorType>(DstRadix);
	ResultType result;
	do
	{
		VectorType rem;
		VectorType quo = bigint_algo::div_mod(value, base, &rem);
		result.push_back(rem[0]);
		value = quo;
	}
	while (!bigint_algo::is_zero(value));

	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_CONVERT_RADIX_HPP
