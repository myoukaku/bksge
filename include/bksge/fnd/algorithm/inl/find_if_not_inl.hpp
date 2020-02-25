/**
 *	@file	find_if_not_inl.hpp
 *
 *	@brief	find_if_not の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FIND_IF_NOT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FIND_IF_NOT_INL_HPP

#include <bksge/fnd/algorithm/find_if_not.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Predicate, typename>
inline BKSGE_CXX14_CONSTEXPR InputIterator
find_if_not(
	InputIterator first,
	InputIterator last,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			break;
		}
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FIND_IF_NOT_INL_HPP
