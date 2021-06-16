/**
 *	@file	find_if_inl.hpp
 *
 *	@brief	find_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FIND_IF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FIND_IF_INL_HPP

#include <bksge/fnd/algorithm/find_if.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR InputIterator
find_if(
	InputIterator first,
	InputIterator last,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			break;
		}
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FIND_IF_INL_HPP
