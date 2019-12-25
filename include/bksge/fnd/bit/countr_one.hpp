/**
 *	@file	countr_one.hpp
 *
 *	@brief	countr_one 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_COUNTR_ONE_HPP
#define BKSGE_FND_BIT_COUNTR_ONE_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>)
#include <bit>

namespace bksge
{

using std::countr_one;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	最下位から1のビットが連続でいくつあるかを返す。(Count Trailing Ones)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最下位ビットから1が何ビット続くかを返す。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		std::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR int
countr_one(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/countr_one_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_COUNTR_ONE_HPP
