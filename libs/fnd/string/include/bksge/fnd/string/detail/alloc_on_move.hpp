/**
 *	@file	alloc_on_move.hpp
 *
 *	@brief	alloc_on_move の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_ALLOC_ON_MOVE_HPP
#define BKSGE_FND_STRING_DETAIL_ALLOC_ON_MOVE_HPP

#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/memory/allocator_traits.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

template <typename Alloc,
	typename Traits = bksge::allocator_traits<Alloc>,
	typename = bksge::enable_if_t<
		Traits::propagate_on_container_move_assignment::value
	>
>
inline BKSGE_CXX14_CONSTEXPR void
alloc_on_move_impl(Alloc& one, Alloc& two, bksge::detail::overload_priority<1>)
{
	one = std::move(two);
}

template <typename Alloc>
inline BKSGE_CXX14_CONSTEXPR void
alloc_on_move_impl(Alloc&, Alloc&, bksge::detail::overload_priority<0>)
{
}

template <typename Alloc>
inline BKSGE_CXX14_CONSTEXPR void
alloc_on_move(Alloc& one, Alloc& two)
{
	alloc_on_move_impl(one, two, bksge::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_ALLOC_ON_MOVE_HPP
