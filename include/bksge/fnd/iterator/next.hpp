/**
 *	@file	next.hpp
 *
 *	@brief	next 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_NEXT_HPP
#define BKSGE_FND_ITERATOR_NEXT_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	
 */
template <
	typename InputIterator,
	typename Distance = bksge::iterator_difference_type<InputIterator>,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CONSTEXPR InputIterator
next(InputIterator const& it, Distance n = 1);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/next_inl.hpp>

#include <bksge/fnd/iterator/ranges/next.hpp>

#endif // BKSGE_FND_ITERATOR_NEXT_HPP
