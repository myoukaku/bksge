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
#include <utility>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename Predicate, typename>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
remove_if(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred)
{
	auto result = first;

	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			*result++ = std::move(*first);
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REMOVE_IF_INL_HPP
