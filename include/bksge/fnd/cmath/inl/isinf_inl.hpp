/**
 *	@file	isinf_inl.hpp
 *
 *	@brief	isinf 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ISINF_INL_HPP
#define BKSGE_FND_CMATH_INL_ISINF_INL_HPP

#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
isinf_impl(FloatType x) BKSGE_NOEXCEPT
{
#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isinf(x);
#else
	return
		x ==  bksge::numeric_limits<FloatType>::infinity() ||
		x == -bksge::numeric_limits<FloatType>::infinity();
#endif
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bool
isinf(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::isinf_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ISINF_INL_HPP
