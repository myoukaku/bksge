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
#include <bksge/fnd/algorithm/find.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
remove(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	first = bksge::find(first, last, value);

	auto result = first;

	for (; first != last; ++first)
	{
		if (!(*first == value))
		{
			*result = std::move(*first);
			++result;
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REMOVE_INL_HPP
