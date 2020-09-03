/**
 *	@file	count_inl.hpp
 *
 *	@brief	count の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_COUNT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_COUNT_INL_HPP

#include <bksge/fnd/algorithm/count.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<InputIterator>
count(InputIterator first, InputIterator last, T const& value)
{
	bksge::iter_difference_t<InputIterator> ret = 0;

	for (; first != last; ++first)
	{
		if (value == *first)
		{
			ret++;
		}
	}

	return ret;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_COUNT_INL_HPP
