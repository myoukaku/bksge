/**
 *	@file	unguarded_linear_insert.hpp
 *
 *	@brief	unguarded_linear_insert の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_LINEAR_INSERT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_LINEAR_INSERT_HPP

#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
unguarded_linear_insert(RandomAccessIterator last, Compare comp)
{
	using value_t = bksge::iter_value_t<RandomAccessIterator>;
	value_t val = std::move(*last);
	auto next_it = last;
	--next_it;

	while (comp(val, *next_it))
	{
		*last = std::move(*next_it);
		last = next_it;
		--next_it;
	}

	*last = std::move(val);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_LINEAR_INSERT_HPP
