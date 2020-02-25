/**
 *	@file	replace_inl.hpp
 *
 *	@brief	replace の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REPLACE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REPLACE_INL_HPP

#include <bksge/fnd/algorithm/replace.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename T, typename>
inline BKSGE_CXX14_CONSTEXPR void
replace(
	ForwardIterator first,
	ForwardIterator last,
	T const& old_value,
	T const& new_value)
{
	for (; first != last; ++first)
	{
		if (*first == old_value)
		{
			*first = new_value;
		}
	}
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REPLACE_INL_HPP
