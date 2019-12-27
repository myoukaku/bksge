/**
 *	@file	ceil2.hpp
 *
 *	@brief	ceil2 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_CEIL2_HPP
#define BKSGE_FND_BIT_CEIL2_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>) && !defined(BKSGE_APPLE_CLANG)
#include <bit>

namespace bksge
{

using std::ceil2;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	2の累乗への切り上げ
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x以上で最小の2の累乗を返す。
 *          戻り値をTとして表現できない場合、0を返す。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		std::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
ceil2(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/ceil2_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_CEIL2_HPP
