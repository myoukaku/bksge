/**
 *	@file	fill_n_inl.hpp
 *
 *	@brief	fill_n の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FILL_N_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FILL_N_INL_HPP

#include <bksge/fnd/algorithm/fill_n.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename OutputIterator,
	typename Size,
	typename T,
	typename
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
fill_n(OutputIterator first, Size n, T const& value)
{
	while (n-- > 0)
	{
		*first++ = value;
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FILL_N_INL_HPP
