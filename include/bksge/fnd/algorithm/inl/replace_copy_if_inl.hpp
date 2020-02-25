/**
 *	@file	replace_copy_if_inl.hpp
 *
 *	@brief	replace_copy_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REPLACE_COPY_IF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REPLACE_COPY_IF_INL_HPP

#include <bksge/fnd/algorithm/replace_copy_if.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename Predicate,
	typename T,
	typename
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
replace_copy_if(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	Predicate pred,
	T const& new_value)
{
	for (; first != last; ++first)
	{
		*result++ = (pred(*first) ? new_value : *first);
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REPLACE_COPY_IF_INL_HPP
