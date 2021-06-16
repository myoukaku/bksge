/**
 *	@file	chunk_insertion_sort.hpp
 *
 *	@brief	chunk_insertion_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_CHUNK_INSERTION_SORT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_CHUNK_INSERTION_SORT_HPP

#include <bksge/fnd/algorithm/detail/insertion_sort.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename RandomAccessIterator,
	typename Distance,
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR void
chunk_insertion_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Distance chunk_size,
	Compare comp)
{
	while (last - first >= chunk_size)
	{
		detail::insertion_sort(first, first + chunk_size, comp);
		first += chunk_size;
	}
	detail::insertion_sort(first, last, comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_CHUNK_INSERTION_SORT_HPP
