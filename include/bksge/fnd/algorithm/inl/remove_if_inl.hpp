/**
 *	@file	remove_if_inl.hpp
 *
 *	@brief	remove_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REMOVE_IF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REMOVE_IF_INL_HPP

#include <bksge/fnd/algorithm/remove_if.hpp>
#include <bksge/fnd/algorithm/find_if.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
remove_if(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred)
{
	first = bksge::find_if(first, last, pred);

	auto result = first;

	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			*result = bksge::move(*first);
			++result;
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REMOVE_IF_INL_HPP
