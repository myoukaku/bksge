/**
 *	@file	prev.hpp
 *
 *	@brief	prev 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_PREV_HPP
#define BKSGE_FND_ITERATOR_PREV_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/iterator/type_traits/is_bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	
 */
template <
	typename BidirectionalIterator,
	typename Distance = bksge::iterator_difference_type<BidirectionalIterator>,
	typename = bksge::enable_if_t<
		bksge::is_bidirectional_iterator<BidirectionalIterator>::value
	>
>
BKSGE_CONSTEXPR BidirectionalIterator
prev(BidirectionalIterator const& it, Distance n = 1);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/prev_inl.hpp>

#include <bksge/fnd/iterator/ranges/prev.hpp>

#endif // BKSGE_FND_ITERATOR_PREV_HPP
