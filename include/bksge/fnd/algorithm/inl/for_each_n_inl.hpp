/**
 *	@file	for_each_n_inl.hpp
 *
 *	@brief	for_each_n の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FOR_EACH_N_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FOR_EACH_N_INL_HPP

#include <bksge/fnd/algorithm/for_each_n.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Size, typename Function>
inline BKSGE_CXX14_CONSTEXPR InputIterator
for_each_n(InputIterator first, Size n, Function f)
{
	while (n-- > 0)
	{
		f(*first);
		++first;
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FOR_EACH_N_INL_HPP
