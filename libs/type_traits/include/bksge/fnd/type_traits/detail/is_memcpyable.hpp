/**
 *	@file	is_memcpyable.hpp
 *
 *	@brief	is_memcpyable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_MEMCPYABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_MEMCPYABLE_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/detail/is_nonvolatile_trivially_copyable.hpp>

namespace bksge
{

namespace detail
{

// Whether two iterator types can be used with memcpy/memmove.
template <typename OutputIter, typename InputIter>
struct is_memcpyable : public bksge::false_type {};

template <typename T>
struct is_memcpyable<T*, T*>
	: public detail::is_nonvolatile_trivially_copyable<T>
{};

template <typename T>
struct is_memcpyable<T*, const T*>
	: public detail::is_nonvolatile_trivially_copyable<T>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_MEMCPYABLE_HPP
