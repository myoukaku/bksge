/**
 *	@file	ceil2_inl.hpp
 *
 *	@brief	ceil2 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_INL_CEIL2_INL_HPP
#define BKSGE_FND_BIT_INL_CEIL2_INL_HPP

#include <bksge/fnd/bit/ceil2.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

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
//	uint64_t ceil2(uint64_t x)
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

template <typename T, std::size_t N>
struct ceil2_impl
{
	static BKSGE_CONSTEXPR T invoke(T x) BKSGE_NOEXCEPT
	{
		return ceil2_impl<T, N / 2>::invoke(x | (x >> N));
	}
};

template <typename T>
struct ceil2_impl<T, 0>
{
	static BKSGE_CONSTEXPR T invoke(T x) BKSGE_NOEXCEPT
	{
		return x + 1;
	}
};

}	// namespace detail

template <typename T, typename>
inline BKSGE_CONSTEXPR T
ceil2(T x) BKSGE_NOEXCEPT
{
	return detail::ceil2_impl<T, bitsof(x) / 2>::invoke(x - 1);
}

}	// namespace bksge

#endif // BKSGE_FND_BIT_INL_CEIL2_INL_HPP
