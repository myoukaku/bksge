/**
 *	@file	bit_width.hpp
 *
 *	@brief	bit_width 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_BIT_WIDTH_HPP
#define BKSGE_FND_BIT_BIT_WIDTH_HPP

#include <bksge/fnd/bit/config.hpp>

#if defined(BKSGE_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace bksge
{

using std::bit_width;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>

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
 *	関数名bit_widthのp1は1を足す (plus one) ことを示している。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
bit_width(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/bit_width_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_BIT_WIDTH_HPP
