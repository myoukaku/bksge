/**
 *	@file	saturate_inl.hpp
 *
 *	@brief	saturate 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_SATURATE_INL_HPP
#define BKSGE_FND_CMATH_INL_SATURATE_INL_HPP

#include <bksge/fnd/cmath/saturate.hpp>
#include <bksge/fnd/cmath/clamp.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

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

#endif // BKSGE_FND_CMATH_INL_SATURATE_INL_HPP
