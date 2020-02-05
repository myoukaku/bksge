/**
 *	@file	advance_inl.hpp
 *
 *	@brief	advance 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INL_ADVANCE_INL_HPP
#define BKSGE_FND_ITERATOR_INL_ADVANCE_INL_HPP

#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/assert.hpp>
#include <iterator>

namespace bksge
{

namespace detail
{

template <typename InputIterator, typename Distance>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl(InputIterator& it, Distance n, std::input_iterator_tag*)
{
	BKSGE_ASSERT(n >= 0);
	for (; 0 < n; --n)
	{
		++it;
	}
}

template <typename BidirectionalIterator, typename Distance>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl(BidirectionalIterator& it, Distance n, std::bidirectional_iterator_tag*)
{
	if (n > 0)
	{
		for (; 0 < n; --n)
		{
			++it;
		}
	}
	else
	{
		for (; n < 0; ++n)
		{
			--it;
		}
	}
}

template <typename RandomAccessIterator, typename Distance>
inline BKSGE_CXX14_CONSTEXPR void
advance_impl(RandomAccessIterator& it, Distance n, std::random_access_iterator_tag*)
{
	it += n;
}

}	// namespace detail

template <typename InputIterator, typename Distance, typename>
inline BKSGE_CXX14_CONSTEXPR void
advance(InputIterator& it, Distance n)
{
	using Category = typename std::iterator_traits<InputIterator>::iterator_category*;
	bksge::detail::advance_impl(it, n, Category());
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INL_ADVANCE_INL_HPP
