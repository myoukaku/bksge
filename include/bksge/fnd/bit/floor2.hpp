/**
 *	@file	floor2.hpp
 *
 *	@brief	floor2 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_FLOOR2_HPP
#define BKSGE_FND_BIT_FLOOR2_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>) && !defined(BKSGE_APPLE_CLANG)
#include <bit>

namespace bksge
{

using std::floor2;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	2の累乗への切り下げ
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return xが0のときは0を返す。
 *          そうでない場合、x 以下の最大の2の累乗を返す。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		std::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
floor2(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/floor2_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_FLOOR2_HPP
