/**
 *	@file	abs_to_unsigned.hpp
 *
 *	@brief	abs_to_unsigned 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_ABS_TO_UNSIGNED_HPP
#define BKSGE_FND_BIGINT_DETAIL_ABS_TO_UNSIGNED_HPP

#include <bksge/fnd/concepts/signed_integral.hpp>
#include <bksge/fnd/concepts/unsigned_integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <BKSGE_REQUIRES_PARAM(bksge::unsigned_integral, T)>
inline BKSGE_CONSTEXPR T
abs_to_unsigned(T x) BKSGE_NOEXCEPT
{
	return x;
}

template <BKSGE_REQUIRES_PARAM(bksge::signed_integral, T)>
inline BKSGE_CONSTEXPR bksge::make_unsigned_t<T>
abs_to_unsigned(T x) BKSGE_NOEXCEPT
{
	using type = bksge::make_unsigned_t<T>;
	return x < 0 ? (~type(x)+1) : type(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_ABS_TO_UNSIGNED_HPP
