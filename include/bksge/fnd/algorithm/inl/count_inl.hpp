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
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename T, typename>
inline BKSGE_CXX14_CONSTEXPR bksge::iterator_difference_type<InputIterator>
count(InputIterator first, InputIterator last, T const& value)
{
	bksge::iterator_difference_type<InputIterator> ret = 0;

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
