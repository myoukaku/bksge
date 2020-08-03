/**
 *	@file	to_unsigned.hpp
 *
 *	@brief	to_unsigned の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_TO_UNSIGNED_HPP
#define BKSGE_FND_RANGES_DETAIL_TO_UNSIGNED_HPP

#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <BKSGE_REQUIRES_PARAM(bksge::integral, T)>
BKSGE_CONSTEXPR bksge::make_unsigned_t<T>
to_unsigned(T t) BKSGE_NOEXCEPT
{
	return t;
}

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_TO_UNSIGNED_HPP
