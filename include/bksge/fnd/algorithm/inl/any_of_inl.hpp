/**
 *	@file	any_of_inl.hpp
 *
 *	@brief	any_of の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_ANY_OF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_ANY_OF_INL_HPP

#include <bksge/fnd/algorithm/any_of.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Predicate, typename>
inline BKSGE_CXX14_CONSTEXPR bool
any_of(InputIterator first, InputIterator last, Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			return true;
		}
	}

	return false;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_ANY_OF_INL_HPP
