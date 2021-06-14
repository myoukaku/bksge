/**
 *	@file	step.hpp
 *
 *	@brief	step 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_STEP_HPP
#define BKSGE_FND_CMATH_STEP_HPP

#include <bksge/fnd/cmath/detail/step_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	step
 *
 *	@tparam		Arithmetic1	算術型
 *	@tparam		Arithmetic2	算術型
 *
 *	@param	a
 *	@param	x
 *
 *	@return	x < a の場合は0。x >= a の場合は1。
 *
 *	a と x の少なくともどちらかが NaN の場合、0 を返す。
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
step(Arithmetic1 a, Arithmetic2 x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::step_impl(static_cast<type>(a), static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_STEP_HPP
