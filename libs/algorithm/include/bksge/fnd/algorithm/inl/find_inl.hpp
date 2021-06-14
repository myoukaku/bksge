/**
 *	@file	find_inl.hpp
 *
 *	@brief	find の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FIND_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FIND_INL_HPP

#include <bksge/fnd/algorithm/find.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR InputIterator
find(
	InputIterator first,
	InputIterator last,
	T const& value)
{
	for (; first != last; ++first)
	{
		if (*first == value)
		{
			break;
		}
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FIND_INL_HPP
