/**
 *	@file	saturate.hpp
 *
 *	@brief	saturate 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SATURATE_HPP
#define BKSGE_FND_CMATH_SATURATE_HPP

#include <bksge/fnd/cmath/detail/saturate_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	値を0以上1以下の範囲に丸めます
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	x < 0なら0, x > 1なら1, さもなくばx
 *
 *	x が NaN の場合、NaN を返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic>
saturate(Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::saturate_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SATURATE_HPP
