/**
 *	@file	hi.hpp
 *
 *	@brief	hi 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_HI_HPP
#define BKSGE_FND_BIGINT_DETAIL_HI_HPP

#include <bksge/fnd/bit/bitsof.hpp>
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

namespace hi_detail
{

template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
inline BKSGE_CXX14_CONSTEXPR Integral
rshift(Integral value, std::size_t n) noexcept
{
	return (n >= bksge::bitsof<Integral>()) ? 0 : (value >> n);
}

}	// namespace hi_detail

template <
	typename ElementType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR Integral
hi(Integral value) noexcept
{
	return hi_detail::rshift(value, bksge::bitsof<ElementType>());
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_HI_HPP
