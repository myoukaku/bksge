/**
 *	@file	next.hpp
 *
 *	@brief	next 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_NEXT_HPP
#define BKSGE_FND_ITERATOR_NEXT_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	
 */
template <
	typename InputIterator,
	typename Distance = bksge::iter_difference_t<InputIterator>
>
BKSGE_CONSTEXPR InputIterator
next(InputIterator const& it, Distance n = 1);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/next_inl.hpp>

#endif // BKSGE_FND_ITERATOR_NEXT_HPP
