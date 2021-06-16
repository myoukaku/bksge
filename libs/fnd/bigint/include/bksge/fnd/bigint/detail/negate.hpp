/**
 *	@file	negate.hpp
 *
 *	@brief	negate 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_NEGATE_HPP
#define BKSGE_FND_BIGINT_DETAIL_NEGATE_HPP

#include <bksge/fnd/bigint/detail/bit_not.hpp>
#include <bksge/fnd/bigint/detail/add.hpp>
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
negate(VectorType const& value) noexcept
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;

	auto result = bigint_algo::bit_not(value);
	bigint_algo::add(result, element_type(1));
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_NEGATE_HPP
