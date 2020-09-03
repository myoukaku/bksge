/**
 *	@file	destroy_n.hpp
 *
 *	@brief	destroy_n を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_DESTROY_N_HPP
#define BKSGE_FND_MEMORY_DESTROY_N_HPP

#include <bksge/fnd/memory/destroy_at.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <bool>
struct destroy_n_impl
{
	template <typename ForwardIterator, typename Size>
	static BKSGE_CXX14_CONSTEXPR ForwardIterator
	destroy(ForwardIterator first, Size n)
	{
		for (; n > 0; (void)++first, --n)
		{
			bksge::destroy_at(bksge::addressof(*first));
		}

		return first;
	}
};

template <>
struct destroy_n_impl<true>
{
	template <typename ForwardIterator, typename Size>
	static BKSGE_CXX14_CONSTEXPR ForwardIterator
	destroy(ForwardIterator first, Size n)
	{
		bksge::advance(first, n);
		return first;
	}
};

}	// namespace detail

template <typename ForwardIterator, typename Size>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
destroy_n(ForwardIterator first, Size n)
{
	using value_t = bksge::iter_value_t<ForwardIterator>;
	return detail::destroy_n_impl<
		bksge::is_trivially_destructible<value_t>::value
	>::destroy(first, n);
}

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_DESTROY_N_HPP
