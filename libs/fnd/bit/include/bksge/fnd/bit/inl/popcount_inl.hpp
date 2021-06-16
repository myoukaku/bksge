/**
 *	@file	popcount_inl.hpp
 *
 *	@brief	popcount 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_POPCOUNT_INL_HPP
#define BKSGE_FND_BIT_INL_POPCOUNT_INL_HPP

#include <bksge/fnd/bit/popcount.hpp>
#include <bksge/fnd/cstdint/uint64_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

// このアルゴリズムに関する詳細は
// Hacker's Delight (ハッカーのたのしみ) ヘンリー・S・ウォーレン、ジュニア著
// http://www.hackersdelight.org/
// を参照してください。

#if defined(BKSGE_HAS_CXX14_CONSTEXPR)

inline constexpr int
popcount_impl(bksge::uint64_t x) BKSGE_NOEXCEPT
{
	x = (x - ((x >> 1) & UINT64_C(0x5555555555555555)));
	x = ((x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333)));
	x = ((x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f));
	x = (x * UINT64_C(0x0101010101010101));
	return x >> 56;
}

#else

inline BKSGE_CONSTEXPR int
popcount_impl_4(bksge::uint64_t x) BKSGE_NOEXCEPT
{
	return (x * UINT64_C(0x0101010101010101)) >> 56;
}

inline BKSGE_CONSTEXPR int
popcount_impl_3(bksge::uint64_t x) BKSGE_NOEXCEPT
{
	return popcount_impl_4((x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f));
}

inline BKSGE_CONSTEXPR int
popcount_impl_2(bksge::uint64_t x) BKSGE_NOEXCEPT
{
	return popcount_impl_3((x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333)));
}

inline BKSGE_CONSTEXPR int
popcount_impl(bksge::uint64_t x) BKSGE_NOEXCEPT
{
	return popcount_impl_2(x - ((x >> 1) & UINT64_C(0x5555555555555555)));
}

#endif

}	// namespace detail

template <typename T, typename>
inline BKSGE_CONSTEXPR int
popcount(T x) BKSGE_NOEXCEPT
{
	return detail::popcount_impl(x);
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_POPCOUNT_INL_HPP
