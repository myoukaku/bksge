/**
 *	@file	rsqrt.hpp
 *
 *	@brief	rsqrt 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_RSQRT_HPP
#define BKSGE_FND_CMATH_RSQRT_HPP

#include <bksge/fnd/cmath/detail/rsqrt_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	平方根の逆数を取得する
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの平方根の逆数を返す
 *
 *	x が 0 よりも小さい場合、NaN を返す。
 *	x が +∞ の場合、+0   を返す。
 *	x が ±0 の場合、±∞ を返す。
 *	x が NaN の場合、NaN  を返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic>
rsqrt(Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::rsqrt_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_RSQRT_HPP
