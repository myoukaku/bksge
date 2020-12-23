/**
 *	@file	countl_zero_inl.hpp
 *
 *	@brief	countl_zero 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_COUNTL_ZERO_INL_HPP
#define BKSGE_FND_BIT_INL_COUNTL_ZERO_INL_HPP

#include <bksge/fnd/bit/countl_zero.hpp>
#include <bksge/fnd/bit/popcount.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

// アルゴリズムに関する詳細は
// Hacker's Delight (ハッカーのたのしみ) ヘンリー・S・ウォーレン、ジュニア著
// http://www.hackersdelight.org/
// を参照してください。
//
//	元々のコードは
//	int countl_zero(uint64_t x)
//	{
//		x = (x | (x >>  1));
//		x = (x | (x >>  2));
//		x = (x | (x >>  4));
//		x = (x | (x >>  8));
//		x = (x | (x >> 16));
//		x = (x | (x >> 32));
//		return popcount(uint64_t(~x));
//	}
//
//	これを任意のビット数に拡張しています。

template <typename T, bksge::size_t N>
struct countl_zero_impl
{
	static BKSGE_CONSTEXPR int invoke(T x) BKSGE_NOEXCEPT
	{
		return countl_zero_impl<T, N / 2>::invoke(x | (x >> N));
	}
};

template <typename T>
struct countl_zero_impl<T, 0>
{
	static BKSGE_CONSTEXPR int invoke(T x) BKSGE_NOEXCEPT
	{
		return popcount(static_cast<T>(~x));
	}
};

}	// namespace detail

template <typename T, typename>
inline BKSGE_CONSTEXPR int
countl_zero(T x) BKSGE_NOEXCEPT
{
	return detail::countl_zero_impl<T, bitsof(x) / 2>::invoke(x);
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_COUNTL_ZERO_INL_HPP
