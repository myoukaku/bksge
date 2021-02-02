/**
 *	@file	issubnormal.hpp
 *
 *	@brief	issubnormal 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISSUBNORMAL_HPP
#define BKSGE_FND_CMATH_ISSUBNORMAL_HPP

#include <bksge/fnd/cmath/detail/issubnormal_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	非正規化数かどうか調べる
 *
 *	@param	x	調べる値
 *
 *	@return	xが非正規化数ならtrue,そうでないならfalse.
 *
 *	非正規化数とは何かの説明は、長くなるのでここには書かない。
 *
 *	@note	xが整数型のときはdoubleにキャストしてから調べる。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
BKSGE_CONSTEXPR bool
issubnormal(Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::issubnormal_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISSUBNORMAL_HPP
