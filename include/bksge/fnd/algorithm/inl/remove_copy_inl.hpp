/**
 *	@file	remove_copy_inl.hpp
 *
 *	@brief	remove_copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REMOVE_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REMOVE_COPY_INL_HPP

#include <bksge/fnd/algorithm/remove_copy.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
remove_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	T const& value)
{
	for (; first != last; ++first)
	{
		if (!(*first == value))
		{
			*result++ = *first;
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REMOVE_COPY_INL_HPP
