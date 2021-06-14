/**
 *	@file	bit_ceil.hpp
 *
 *	@brief	bit_ceil 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_BIT_CEIL_HPP
#define BKSGE_FND_BIT_BIT_CEIL_HPP

#include <bksge/fnd/bit/config.hpp>

#if defined(BKSGE_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace bksge
{

using std::bit_ceil;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>

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
		bksge::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
bit_ceil(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/bit_ceil_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_BIT_CEIL_HPP
