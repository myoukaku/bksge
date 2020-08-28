/**
 *	@file	min_element_inl.hpp
 *
 *	@brief	min_element の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MIN_ELEMENT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MIN_ELEMENT_INL_HPP

#include <bksge/fnd/algorithm/min_element.hpp>
#include <bksge/fnd/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
min_element(
	ForwardIterator first,
	ForwardIterator last)
{
	return bksge::algorithm::min_element(
		first, last, bksge::less<>());
}

template <typename ForwardIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
min_element(
	ForwardIterator first,
	ForwardIterator last,
	Compare comp)
{
	if (first == last)
	{
		return first;
	}

	auto result = first++;

	for (; first != last; ++first)
	{
		if (comp(*first, *result))
		{
			result = first;
		}
	}
	
	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MIN_ELEMENT_INL_HPP
