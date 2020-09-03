/**
 *	@file	advance.hpp
 *
 *	@brief	advance 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ADVANCE_HPP
#define BKSGE_FND_ITERATOR_ADVANCE_HPP

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
BKSGE_CXX14_CONSTEXPR void
advance(InputIterator& it, Distance n = 1);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/advance_inl.hpp>

#endif // BKSGE_FND_ITERATOR_ADVANCE_HPP
