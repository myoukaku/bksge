/**
 *	@file	alloc_on_copy.hpp
 *
 *	@brief	alloc_on_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_ALLOC_ON_COPY_HPP
#define BKSGE_FND_STRING_DETAIL_ALLOC_ON_COPY_HPP

#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/memory/allocator_traits.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename Alloc,
	typename Traits = bksge::allocator_traits<Alloc>,
	typename = bksge::enable_if_t<
		Traits::propagate_on_container_copy_assignment::value
	>
>
inline BKSGE_CXX14_CONSTEXPR void
alloc_on_copy_impl(Alloc& one, Alloc const& two, bksge::detail::overload_priority<1>)
{
	one = two;
}

template <typename Alloc>
inline BKSGE_CXX14_CONSTEXPR void
alloc_on_copy_impl(Alloc&, Alloc const&, bksge::detail::overload_priority<0>)
{
}

template <typename Alloc>
inline BKSGE_CXX14_CONSTEXPR void
alloc_on_copy(Alloc& one, Alloc const& two)
{
	alloc_on_copy_impl(one, two, bksge::detail::overload_priority<1>{});
}

//template <typename Alloc>
//inline BKSGE_CXX14_CONSTEXPR Alloc
//alloc_on_copy(Alloc const& a)
//{
//	using traits = bksge::allocator_traits<Alloc>;
//	return traits::select_on_container_copy_construction(a);
//}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_ALLOC_ON_COPY_HPP
