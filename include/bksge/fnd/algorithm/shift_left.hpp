/**
 *	@file	shift_left.hpp
 *
 *	@brief	shift_left の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SHIFT_LEFT_HPP
#define BKSGE_FND_ALGORITHM_SHIFT_LEFT_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename ForwardIterator>
BKSGE_CXX14_CONSTEXPR ForwardIterator
shift_left(ForwardIterator first, ForwardIterator last,
	typename bksge::iterator_traits<ForwardIterator>::difference_type n)
{
	if (n <= 0)
	{
		return last;
	}

	auto mid = ranges::next(first, n, last);
	if (mid == last)
	{
		return first;
	}

	return bksge::move(bksge::move(mid), bksge::move(last), bksge::move(first));
}

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_SHIFT_LEFT_HPP
