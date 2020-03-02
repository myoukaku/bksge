/**
 *	@file	rotl.hpp
 *
 *	@brief	rotl 関数テンプレートを定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_ROTL_HPP
#define BKSGE_FND_BIT_ROTL_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>) && !defined(BKSGE_APPLE_CLANG)
#include <bit>

namespace bksge
{

using std::rotl;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>

namespace bksge
{

/**
 *	@brief	環状左シフト(キャリーなし左ローテート)
 *
 *	@tparam	T		xの型(符号なし整数型)
 *
 *	@param	x		シフトされる値
 *	@param	shift	シフトするビット数
 *
 *	xをshiftビットだけ環状左シフト(キャリーなし左ローテート)した値を返します。
 *	shiftがxのビット数以上の場合でも正しく計算します。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
rotl(T x, unsigned int shift) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/rotl_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_ROTL_HPP
