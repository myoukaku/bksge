/**
 *	@file	remove_inl.hpp
 *
 *	@brief	remove の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REMOVE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REMOVE_INL_HPP

#include <bksge/fnd/algorithm/remove.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename T, typename>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
remove(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	auto result = first;

	for (; first != last; ++first)
	{
		if (!(*first == value))
		{
			*result++ = std::move(*first);
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REMOVE_INL_HPP
