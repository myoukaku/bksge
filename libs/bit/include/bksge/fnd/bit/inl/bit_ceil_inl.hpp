/**
 *	@file	bit_ceil_inl.hpp
 *
 *	@brief	bit_ceil 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_BIT_CEIL_INL_HPP
#define BKSGE_FND_BIT_INL_BIT_CEIL_INL_HPP

#include <bksge/fnd/bit/bit_ceil.hpp>
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
//	uint64_t bit_ceil(uint64_t x)
//	{
//		x = x - 1;
//		x = x | (x >> 1);
//		x = x | (x >> 2);
//		x = x | (x >> 4);
//		x = x | (x >> 8);
//		x = x | (x >>16);
//		x = x | (x >>32);
//		return x + 1;
//	}
//
//	これを任意のビット数に拡張しています。

template <typename T, bksge::size_t N>
struct bit_ceil_impl2
{
	static BKSGE_CONSTEXPR T invoke(T x) BKSGE_NOEXCEPT
	{
		return bit_ceil_impl2<T, N / 2>::invoke(x | (x >> N));
	}
};

template <typename T>
struct bit_ceil_impl2<T, 0>
{
	static BKSGE_CONSTEXPR T invoke(T x) BKSGE_NOEXCEPT
	{
		return x + 1;
	}
};

template <typename T>
inline BKSGE_CONSTEXPR T
bit_ceil_impl(T x) BKSGE_NOEXCEPT
{
	return (x == 0) ? T(1) : detail::bit_ceil_impl2<T, bitsof(x) / 2>::invoke(x - 1);
}

}	// namespace detail

template <typename T, typename>
inline BKSGE_CONSTEXPR T
bit_ceil(T x) BKSGE_NOEXCEPT
{
	return detail::bit_ceil_impl(x);
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_BIT_CEIL_INL_HPP
