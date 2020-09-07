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

#if 0//(BKSGE_CXX_STANDARD >= 20)

#include <iterator>

namespace bksge
{

using std::distance;

}	// namespace bksge

#else

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	
 */
template <typename InputIterator>
BKSGE_CONSTEXPR bksge::iter_difference_t<InputIterator>
distance(InputIterator first, InputIterator last);

}	// namespace bksge

#include <bksge/fnd/iterator/inl/distance_inl.hpp>

#endif

#endif // BKSGE_FND_ITERATOR_DISTANCE_HPP
