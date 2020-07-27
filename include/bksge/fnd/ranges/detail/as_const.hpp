/**
 *	@file	as_const.hpp
 *
 *	@brief	as_const の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_AS_CONST_HPP
#define BKSGE_FND_RANGES_DETAIL_AS_CONST_HPP

#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename T>
BKSGE_CONSTEXPR bksge::remove_reference_t<T> const&
as_const(T& t) BKSGE_NOEXCEPT
{
	return static_cast<bksge::remove_reference_t<T> const&>(t);
}

template <typename T>
BKSGE_CONSTEXPR T const&&
as_const(T&& t) BKSGE_NOEXCEPT
{
	return static_cast<T const&&>(t);
}

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_AS_CONST_HPP
