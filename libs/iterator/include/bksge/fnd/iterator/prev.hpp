/**
 *	@file	prev.hpp
 *
 *	@brief	prev 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_PREV_HPP
#define BKSGE_FND_ITERATOR_PREV_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	
 */
template <
	typename BidirectionalIterator,
	typename Distance = bksge::iter_difference_t<BidirectionalIterator>
>
BKSGE_CONSTEXPR BidirectionalIterator
prev(BidirectionalIterator const& it, Distance n = 1);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/prev_inl.hpp>

#endif // BKSGE_FND_ITERATOR_PREV_HPP
