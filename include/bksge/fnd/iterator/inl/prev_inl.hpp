/**
 *	@file	prev_inl.hpp
 *
 *	@brief	prev 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INL_PREV_INL_HPP
#define BKSGE_FND_ITERATOR_INL_PREV_INL_HPP

#include <bksge/fnd/iterator/prev.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>

namespace bksge
{

namespace detail
{

template <typename BidirectionalIterator, typename Distance>
inline BKSGE_CXX14_CONSTEXPR BidirectionalIterator
prev_impl(BidirectionalIterator it, Distance n, std::bidirectional_iterator_tag*)
{
	bksge::advance(it, -n);
	return it;
}

template <typename RandomAccessIterator, typename Distance>
inline BKSGE_CONSTEXPR RandomAccessIterator
prev_impl(RandomAccessIterator const& it, Distance n, std::random_access_iterator_tag*)
{
	return it - n;
}

}	// namespace detail

template <typename BidirectionalIterator, typename Distance, typename>
inline BKSGE_CONSTEXPR BidirectionalIterator
prev(BidirectionalIterator const& it, Distance n)
{
	using Category = typename std::iterator_traits<BidirectionalIterator>::iterator_category*;
	return detail::prev_impl(it, n, Category());
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INL_PREV_INL_HPP
