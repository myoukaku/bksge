/**
 *	@file	shift_left.hpp
 *
 *	@brief	shift_left の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SHIFT_LEFT_HPP
#define BKSGE_FND_ALGORITHM_SHIFT_LEFT_HPP

#include <algorithm>

#if defined(__cpp_lib_shift) && (__cpp_lib_shift >= 201806)

namespace bksge
{

using std::shift_left;

}	// namespace bksge

#else

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

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

	return bksge::move(std::move(mid), std::move(last), std::move(first));
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ALGORITHM_SHIFT_LEFT_HPP
