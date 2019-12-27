/**
 *	@file	log2p1.hpp
 *
 *	@brief	log2p1 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_LOG2P1_HPP
#define BKSGE_FND_BIT_LOG2P1_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>) && !defined(BKSGE_APPLE_CLANG)
#include <bit>

namespace bksge
{

using std::log2p1;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	2を底とした整数値の対数を求めて1を足す
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x == 0である場合、0を返す。
 *			そうでない場合、2を底としてxの対数を求めて、それに1を足した値を返す。
 *			その際、小数点以下の値は破棄される。
 *
 *	戻り値に1を足す理由は、対数を求められない0を引数として許容することでnoexceptとし、
 *	かつx == 1である場合と区別するためである。
 *	関数名log2p1のp1は1を足す (plus one) ことを示している。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		std::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
log2p1(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/log2p1_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_LOG2P1_HPP
