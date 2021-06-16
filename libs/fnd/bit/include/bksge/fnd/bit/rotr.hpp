/**
 *	@file	rotr.hpp
 *
 *	@brief	rotr 関数テンプレートを定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_ROTR_HPP
#define BKSGE_FND_BIT_ROTR_HPP

#include <bksge/fnd/bit/config.hpp>

#if defined(BKSGE_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace bksge
{

using std::rotr;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>

namespace bksge
{

/**
 *	@brief	環状右シフト(キャリーなし右ローテート)
 *
 *	@tparam	T		xの型(符号なし整数型)
 *
 *	@param	x		シフトされる値
 *	@param	shift	シフトするビット数
 *
 *	xをshiftビットだけ環状右シフト(キャリーなし右ローテート)した値を返します。
 *	shiftがxのビット数以上の場合でも正しく計算します。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
rotr(T x, unsigned int shift) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/rotr_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_ROTR_HPP
