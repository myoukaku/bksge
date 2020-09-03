/**
 *	@file	replace_if_inl.hpp
 *
 *	@brief	replace_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REPLACE_IF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REPLACE_IF_INL_HPP

#include <bksge/fnd/algorithm/replace_if.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename ForwardIterator,
	typename Predicate,
	typename T
>
inline BKSGE_CXX14_CONSTEXPR void
replace_if(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred,
	T const& new_value)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			*first = new_value;
		}
	}
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REPLACE_IF_INL_HPP
