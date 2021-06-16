/**
 *	@file	find_if_not_n.hpp
 *
 *	@brief	find_if_not_n の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_FIND_IF_NOT_N_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_FIND_IF_NOT_N_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename InputIterator, typename Predicate, typename Distance>
inline BKSGE_CXX14_CONSTEXPR InputIterator
find_if_not_n(InputIterator first, Distance& len, Predicate pred)
{
	for (; len; --len, (void) ++first)
	{
		if (!pred(*first))
		{
			break;
		}
	}

	return first;
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_FIND_IF_NOT_N_HPP
