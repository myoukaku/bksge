/**
 *	@file	to_unsigned.hpp
 *
 *	@brief	to_unsigned の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_DETAIL_TO_UNSIGNED_HPP
#define BKSGE_FND_RANGES_CONCEPTS_DETAIL_TO_UNSIGNED_HPP

#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::integral T
#else
	typename T,
	typename = bksge::enable_if_t<bksge::integral<T>::value>
#endif
>
BKSGE_CONSTEXPR bksge::make_unsigned_t<T>
to_unsigned(T t) BKSGE_NOEXCEPT
{
	return t;
}

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_DETAIL_TO_UNSIGNED_HPP
