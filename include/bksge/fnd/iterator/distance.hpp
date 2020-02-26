/**
 *	@file	distance.hpp
 *
 *	@brief	distance 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_DISTANCE_HPP
#define BKSGE_FND_ITERATOR_DISTANCE_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 17)

#include <iterator>

namespace bksge
{

using std::distance;

}	// namespace bksge

#else

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
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CONSTEXPR bksge::iterator_difference_type<InputIterator>
distance(InputIterator first, InputIterator last);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/distance_inl.hpp>

#endif

#endif // BKSGE_FND_ITERATOR_DISTANCE_HPP
