/**
 *	@file	max_element_inl.hpp
 *
 *	@brief	max_element の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MAX_ELEMENT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MAX_ELEMENT_INL_HPP

#include <bksge/fnd/algorithm/max_element.hpp>
#include <bksge/fnd/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
max_element(
	ForwardIterator first,
	ForwardIterator last)
{
	return bksge::algorithm::max_element(
		first, last, bksge::less<>());
}

template <typename ForwardIterator, typename Compare, typename>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
max_element(
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
		if (comp(*result, *first))
		{
			result = first;
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MAX_ELEMENT_INL_HPP
