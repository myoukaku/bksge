/**
 *	@file	replace_copy_inl.hpp
 *
 *	@brief	replace_copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REPLACE_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REPLACE_COPY_INL_HPP

#include <bksge/fnd/algorithm/replace_copy.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename T,
	typename
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator 
replace_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	T const& old_value,
	T const& new_value)
{
	for (; first != last; ++first)
	{
		*result++ = (*first == old_value ? new_value : *first);
	}
	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REPLACE_COPY_INL_HPP
