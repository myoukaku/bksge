/**
 *	@file	countr_zero.hpp
 *
 *	@brief	countr_zero 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_COUNTR_ZERO_HPP
#define BKSGE_FND_BIT_COUNTR_ZERO_HPP

#include <bksge/fnd/bit/config.hpp>

#if defined(BKSGE_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace bksge
{

using std::countr_zero;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>

namespace bksge
{

/**
 *	@brief	最下位から0のビットが連続でいくつあるかを返す。(Count Trailing Zeros)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最下位ビットから0が何ビット続くかを返す。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR int
countr_zero(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/countr_zero_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_COUNTR_ZERO_HPP
