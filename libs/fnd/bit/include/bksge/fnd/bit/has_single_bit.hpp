/**
 *	@file	has_single_bit.hpp
 *
 *	@brief	has_single_bit 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_HAS_SINGLE_BIT_HPP
#define BKSGE_FND_BIT_HAS_SINGLE_BIT_HPP

#include <bksge/fnd/bit/config.hpp>

#if defined(BKSGE_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace bksge
{

using std::has_single_bit;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>

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
		bksge::is_unsigned<T>::value
	>
>
BKSGE_CONSTEXPR bool
has_single_bit(T x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/bit/inl/has_single_bit_inl.hpp>

#endif

#endif // BKSGE_FND_BIT_HAS_SINGLE_BIT_HPP
