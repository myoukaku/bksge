/**
 *	@file	count_if_inl.hpp
 *
 *	@brief	count_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_COUNT_IF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_COUNT_IF_INL_HPP

#include <bksge/fnd/algorithm/count_if.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Predicate, typename>
inline BKSGE_CXX14_CONSTEXPR bksge::iterator_difference_type<InputIterator>
count_if(InputIterator first, InputIterator last, Predicate pred)
{
	bksge::iterator_difference_type<InputIterator> ret = 0;

	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			ret++;
		}
	}

	return ret;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_COUNT_IF_INL_HPP
