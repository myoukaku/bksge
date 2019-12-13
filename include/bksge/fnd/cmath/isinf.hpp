/**
 *	@file	isinf.hpp
 *
 *	@brief	isinf 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISINF_HPP
#define BKSGE_FND_CMATH_ISINF_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	∞かどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが±∞ならtrue,そうでないならfalse.
 *
 *	@note	ArithmeticTypeが整数型のときはdoubleにキャストしてから調べる。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR bool
isinf(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::isinf;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/isinf_inl.hpp>

#endif // BKSGE_FND_CMATH_ISINF_HPP
