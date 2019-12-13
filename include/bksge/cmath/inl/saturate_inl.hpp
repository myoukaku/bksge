/**
 *	@file	saturate_inl.hpp
 *
 *	@brief	saturate 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_SATURATE_INL_HPP
#define BKSGE_CMATH_INL_SATURATE_INL_HPP

#include <bksge/cmath/saturate.hpp>
#include <bksge/cmath/clamp.hpp>
#include <bksge/type_traits/float_promote.hpp>
#include <bksge/config.hpp>

namespace bksge
{

namespace cmath
{

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
saturate(ArithmeticType x) BKSGE_NOEXCEPT
{
	return bksge::cmath::clamp(x, ArithmeticType(0), ArithmeticType(1));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_SATURATE_INL_HPP
