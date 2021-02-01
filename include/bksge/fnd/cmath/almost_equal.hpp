/**
 *	@file	almost_equal.hpp
 *
 *	@brief	almost_equal 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ALMOST_EQUAL_HPP
#define BKSGE_FND_CMATH_ALMOST_EQUAL_HPP

#include <bksge/fnd/cmath/detail/almost_equal_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/arithmetic_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	2つの値がほぼ同じかどうかを調べる
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	xとyがほぼ同じ値ならtrue
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bool
almost_equal(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::arithmetic_promote_t<Arithmetic1, Arithmetic2>;
	return detail::almost_equal_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ALMOST_EQUAL_HPP
