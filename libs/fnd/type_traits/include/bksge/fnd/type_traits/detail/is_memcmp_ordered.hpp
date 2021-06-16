/**
 *	@file	is_memcmp_ordered.hpp
 *
 *	@brief	is_memcmp_ordered の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_MEMCMP_ORDERED_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_MEMCMP_ORDERED_HPP

#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/type_traits/detail/is_byte.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

// Whether memcmp can be used to determine ordering for a type
// e.g. in std::lexicographical_compare or three-way comparisons.
// True for unsigned integer-like types where comparing each byte in turn
// as an unsigned char yields the right result. This is true for all
// unsigned integers on big endian targets, but only unsigned narrow
// character types (and std::byte) on little endian targets.
template <typename T, bool TreatAsBytes =
#if defined(BKSGE_BIG_ENDIAN)
	bksge::is_integral<T>::value
#else
	bksge::detail::is_byte<T>::value
#endif
>
struct is_memcmp_ordered
{
	static const bool value = T(-1) > T(1); // is unsigned
};

template <typename T>
struct is_memcmp_ordered<T, false>
{
	static const bool value = false;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_MEMCMP_ORDERED_HPP
