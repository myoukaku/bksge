/**
 *	@file	all_of_inl.hpp
 *
 *	@brief	all_of の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_ALL_OF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_ALL_OF_INL_HPP

#include <bksge/fnd/algorithm/all_of.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR bool
all_of(InputIterator first, InputIterator last, Predicate pred)
{
	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			return false;
		}
	}

	return true;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_ALL_OF_INL_HPP
