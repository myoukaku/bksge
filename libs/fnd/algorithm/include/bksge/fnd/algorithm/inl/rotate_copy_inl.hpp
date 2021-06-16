/**
 *	@file	rotate_copy_inl.hpp
 *
 *	@brief	rotate_copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_ROTATE_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_ROTATE_COPY_INL_HPP

#include <bksge/fnd/algorithm/rotate_copy.hpp>
#include <bksge/fnd/algorithm/copy.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename OutputIterator>
inline OutputIterator
rotate_copy(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last,
	OutputIterator result)
{
	return bksge::algorithm::copy(
		first,
		middle,
		bksge::algorithm::copy(
			middle,
			last,
			result
		)
	);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_ROTATE_COPY_INL_HPP
