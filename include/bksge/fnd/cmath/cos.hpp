/**
 *	@file	cos.hpp
 *
 *	@brief	cos 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_COS_HPP
#define BKSGE_FND_CMATH_COS_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	余弦（コサイン）を取得する
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、xのコサインを返す
 *
 *	x が ±0  の場合、1を返す。
 *	x が ±∞ の場合、NaNを返す。
 *	x が NaN  の場合、NaNを返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
cos(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/cos_inl.hpp>

#endif // BKSGE_FND_CMATH_COS_HPP
