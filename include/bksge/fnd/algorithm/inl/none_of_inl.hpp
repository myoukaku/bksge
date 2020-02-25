/**
 *	@file	none_of_inl.hpp
 *
 *	@brief	none_of の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_NONE_OF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_NONE_OF_INL_HPP

#include <bksge/fnd/algorithm/none_of.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Predicate, typename>
inline BKSGE_CXX14_CONSTEXPR bool
none_of(
	InputIterator first,
	InputIterator last,
	Predicate pred)
{
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

#endif // BKSGE_FND_ALGORITHM_INL_NONE_OF_INL_HPP
