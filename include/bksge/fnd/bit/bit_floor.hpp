/**
 *	@file	bit_floor.hpp
 *
 *	@brief	bit_floor 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_BIT_FLOOR_HPP
#define BKSGE_FND_BIT_BIT_FLOOR_HPP

#include <bksge/fnd/bit/config.hpp>

#if defined(BKSGE_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace bksge
{

using std::bit_floor;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>

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
		bksge::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR T
bit_floor(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/bit_floor_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_BIT_FLOOR_HPP
