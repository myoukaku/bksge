/**
 *	@file	remove_copy_if_inl.hpp
 *
 *	@brief	remove_copy_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REMOVE_COPY_IF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REMOVE_COPY_IF_INL_HPP

#include <bksge/fnd/algorithm/remove_copy_if.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename Predicate
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
remove_copy_if(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			*result++ = *first;
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REMOVE_COPY_IF_INL_HPP
