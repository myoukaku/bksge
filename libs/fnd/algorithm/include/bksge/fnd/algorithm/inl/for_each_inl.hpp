/**
 *	@file	for_each_inl.hpp
 *
 *	@brief	for_each の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FOR_EACH_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FOR_EACH_INL_HPP

#include <bksge/fnd/algorithm/for_each.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

template <typename InputIterator, typename Function>
inline BKSGE_CXX14_CONSTEXPR Function
for_each(
	InputIterator first,
	InputIterator last,
	Function f)
{
	for (; first != last; ++first)
	{
		f(*first);
	}

	return bksge::move(f);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FOR_EACH_INL_HPP
