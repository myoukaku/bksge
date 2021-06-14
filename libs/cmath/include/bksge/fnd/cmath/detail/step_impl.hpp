/**
 *	@file	step_impl.hpp
 *
 *	@brief	step 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_STEP_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_STEP_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
step_impl(FloatType a, FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(a) || bksge::isnan(x) ?
			FloatType(0) :
		x >= a ?
			FloatType(1) :
		FloatType(0);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_STEP_IMPL_HPP
