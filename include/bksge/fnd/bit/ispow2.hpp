/**
 *	@file	ispow2.hpp
 *
 *	@brief	ispow2 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_ISPOW2_HPP
#define BKSGE_FND_BIT_ISPOW2_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<bit>) && !defined(BKSGE_APPLE_CLANG)
#include <bit>

namespace bksge
{

using std::ispow2;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	2の累乗かどうか取得する.
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	取得する対象となる値
 *
 *	@return	xが2の累乗ならtrueを返す。
 */
template <
	typename T,
	typename = bksge::enable_if_t<
		std::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR bool
ispow2(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/ispow2_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_ISPOW2_HPP
