/**
 *	@file	advance.hpp
 *
 *	@brief	advance 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ADVANCE_HPP
#define BKSGE_FND_ITERATOR_ADVANCE_HPP

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
BKSGE_CXX14_CONSTEXPR void
advance(InputIterator& it, Distance n = 1);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/advance_inl.hpp>
#include <bksge/fnd/iterator/ranges/advance.hpp>

#endif // BKSGE_FND_ITERATOR_ADVANCE_HPP
