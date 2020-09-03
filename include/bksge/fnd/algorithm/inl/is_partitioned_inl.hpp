/**
 *	@file	is_partitioned_inl.hpp
 *
 *	@brief	is_partitioned の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_IS_PARTITIONED_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_IS_PARTITIONED_INL_HPP

#include <bksge/fnd/algorithm/is_partitioned.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR bool
is_partitioned(
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

	if (first == last)
	{
		return true;
	}

	++first;
	
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			return false;
		}
	}

	return true;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_IS_PARTITIONED_INL_HPP
