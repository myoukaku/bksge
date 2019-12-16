/**
 *	@file	step.hpp
 *
 *	@brief	step 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_STEP_HPP
#define BKSGE_FND_CMATH_STEP_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	step
 *
 *	@tparam		ArithmeticType1	算術型
 *	@tparam		ArithmeticType2	算術型
 *
 *	@param	a
 *	@param	x
 *
 *	@return	x < a の場合は0。x >= a の場合は1。
 *
 *	a と x の少なくともどちらかが NaN の場合、0 を返す。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType1>::value &&
		std::is_arithmetic<ArithmeticType2>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
step(ArithmeticType1 a, ArithmeticType2 x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::step;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/step_inl.hpp>

#endif // BKSGE_FND_CMATH_STEP_HPP
