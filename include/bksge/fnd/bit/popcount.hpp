﻿/**
 *	@file	popcount.hpp
 *
 *	@brief	popcount 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_POPCOUNT_HPP
#define BKSGE_FND_BIT_POPCOUNT_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>) && !defined(BKSGE_APPLE_CLANG)
#include <bit>

namespace bksge
{

using std::popcount;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	1になっているビットを数える。(Population Count)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、1 となるビットの個数を返す。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		std::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR int
popcount(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/popcount_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_POPCOUNT_HPP