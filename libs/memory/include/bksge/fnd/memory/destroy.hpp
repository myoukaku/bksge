/**
 *	@file	destroy.hpp
 *
 *	@brief	destroy を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_DESTROY_HPP
#define BKSGE_FND_MEMORY_DESTROY_HPP

#include <bksge/fnd/memory/destroy_at.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <bool>
struct destroy_impl
{
	template <typename ForwardIterator>
	static BKSGE_CXX14_CONSTEXPR void
	destroy(ForwardIterator first, ForwardIterator last)
	{
		for (; first != last; ++first)
		{
			bksge::destroy_at(bksge::addressof(*first));
		}
	}
};

template <>
struct destroy_impl<true>
{
	template <typename ForwardIterator>
	static BKSGE_CXX14_CONSTEXPR void
	destroy(ForwardIterator, ForwardIterator)
	{
	}
};

}	// namespace detail

template <typename ForwardIterator>
inline BKSGE_CXX14_CONSTEXPR void
destroy(ForwardIterator first, ForwardIterator last)
{
	using value_t = bksge::iter_value_t<ForwardIterator>;
	detail::destroy_impl<
		bksge::is_trivially_destructible<value_t>::value
	>::destroy(first, last);
}

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_DESTROY_HPP
