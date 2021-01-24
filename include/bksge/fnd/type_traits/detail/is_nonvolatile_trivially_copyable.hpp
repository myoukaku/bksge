/**
 *	@file	is_nonvolatile_trivially_copyable.hpp
 *
 *	@brief	is_nonvolatile_trivially_copyable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_NONVOLATILE_TRIVIALLY_COPYABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_NONVOLATILE_TRIVIALLY_COPYABLE_HPP

#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/is_volatile.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>

namespace bksge
{

namespace detail
{

// Cannot use memcpy/memmove/memcmp on volatile types even if they are
// trivially copyable, so ensure is_memcpyable<volatile int*, volatile int*>
// and similar will be false.

template <typename T>
struct is_nonvolatile_trivially_copyable
	: public bksge::conjunction<
		bksge::negation<bksge::is_volatile<T>>,
		bksge::is_trivially_copyable<T>
	>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_NONVOLATILE_TRIVIALLY_COPYABLE_HPP
