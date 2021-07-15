/**
 *	@file	to_arithmetic.hpp
 *
 *	@brief	to_arithmetic 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_TO_ARITHMETIC_HPP
#define BKSGE_FND_BIGINT_DETAIL_TO_ARITHMETIC_HPP

#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/rbegin.hpp>
#include <bksge/fnd/ranges/rend.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

namespace to_arithmetic_detail
{

template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral), typename VectorType>
inline BKSGE_CXX14_CONSTEXPR Integral
to_arithmetic_impl(VectorType const& value, bksge::detail::overload_priority<1>)
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;

	std::uintmax_t r = 0;
	for (auto it = ranges::rbegin(value); it != ranges::rend(value); ++it)
	{
		r = (r << bksge::bitsof<element_type>()) + *it;
	}

	return static_cast<Integral>(r);
}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4056);	// overflow in floating-point constant arithmetic

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float), typename VectorType>
inline BKSGE_CXX14_CONSTEXPR Float
to_arithmetic_impl(VectorType const& value, bksge::detail::overload_priority<0>)
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;

	auto const multiplier = static_cast<Float>(1ULL << bksge::bitsof<element_type>());
	Float r = 0;
	for (auto it = ranges::rbegin(value); it != ranges::rend(value); ++it)
	{
		r = (r * multiplier) + *it;
	}

	return r;
}

BKSGE_WARNING_POP();

}	// namespace to_arithmetic_detail

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic), typename VectorType>
inline BKSGE_CXX14_CONSTEXPR Arithmetic
to_arithmetic(VectorType const& value)
{
	return to_arithmetic_detail::to_arithmetic_impl<Arithmetic>(
		value, bksge::detail::overload_priority<1>{});
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_TO_ARITHMETIC_HPP
