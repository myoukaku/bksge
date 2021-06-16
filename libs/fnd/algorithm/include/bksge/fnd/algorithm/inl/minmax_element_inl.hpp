/**
 *	@file	minmax_element_inl.hpp
 *
 *	@brief	minmax_element の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MINMAX_ELEMENT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MINMAX_ELEMENT_INL_HPP

#include <bksge/fnd/algorithm/minmax_element.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/utility/pair.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator>
inline BKSGE_CXX14_CONSTEXPR bksge::pair<ForwardIterator, ForwardIterator>
minmax_element(
	ForwardIterator first,
	ForwardIterator last)
{
	return bksge::algorithm::minmax_element(first, last, bksge::less<>());
}

template <typename ForwardIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR bksge::pair<ForwardIterator, ForwardIterator>
minmax_element(
	ForwardIterator first,
	ForwardIterator last,
	Compare comp)
{
	bksge::pair<ForwardIterator, ForwardIterator> result(first, first);

	if (first == last)
	{
		return result;
	}

	if (++first == last)
	{
		return result;
	}

	if (comp(*first, *result.first))
	{
		result.first = first;
	}
	else
	{
		result.second = first;
	}

	while (++first != last)
	{
		auto i = first;
		if (++first == last)
		{
			if (comp(*i, *result.first))
			{
				result.first = i;
			}
			else if (!(comp(*i, *result.second)))
			{
				result.second = i;
			}

			break;
		}
		else
		{
			if (comp(*first, *i))
			{
				if (comp(*first, *result.first))
				{
					result.first = first;
				}

				if (!(comp(*i, *result.second)))
				{
					result.second = i;
				}
			}
			else
			{
				if (comp(*i, *result.first))
				{
					result.first = i;
				}

				if (!(comp(*first, *result.second)))
				{
					result.second = first;
				}
			}
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MINMAX_ELEMENT_INL_HPP
