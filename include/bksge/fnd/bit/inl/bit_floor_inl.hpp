/**
 *	@file	bit_floor_inl.hpp
 *
 *	@brief	bit_floor 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_BIT_FLOOR_INL_HPP
#define BKSGE_FND_BIT_INL_BIT_FLOOR_INL_HPP

#include <bksge/fnd/bit/bit_floor.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

// このアルゴリズムに関する詳細は
// Hacker's Delight (ハッカーのたのしみ) ヘンリー・S・ウォーレン、ジュニア著
// http://www.hackersdelight.org/
// を参照してください。
//
//	元々のコードは
//	uint64_t bit_floor(uint64_t x)
//	{
//		x = x | (x >> 1);
//		x = x | (x >> 2);
//		x = x | (x >> 4);
//		x = x | (x >> 8);
//		x = x | (x >>16);
//		x = x | (x >>32);
//		return x - (x >> 1);
//	}
//
//	これを任意のビット数に拡張しています。

template <typename T, std::size_t N>
struct bit_floor_impl
{
	static BKSGE_CONSTEXPR T invoke(T x) BKSGE_NOEXCEPT
	{
		return bit_floor_impl<T, N / 2>::invoke(x | (x >> N));
	}
};

template <typename T>
struct bit_floor_impl<T, 0>
{
	static BKSGE_CONSTEXPR T invoke(T x) BKSGE_NOEXCEPT
	{
		return x - (x >> 1);
	}
};

}	// namespace detail

template <typename T, typename>
inline BKSGE_CONSTEXPR T
bit_floor(T x) BKSGE_NOEXCEPT
{
	return detail::bit_floor_impl<T, bitsof(x) / 2>::invoke(x);
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_BIT_FLOOR_INL_HPP
