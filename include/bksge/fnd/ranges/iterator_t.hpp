/**
 *	@file	iterator_t.hpp
 *
 *	@brief	ranges::iterator_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_ITERATOR_T_HPP
#define BKSGE_FND_RANGES_ITERATOR_T_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace ranges
{

template <typename T>
using iterator_t = decltype(ranges::begin(bksge::declval<T&>()));

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_ITERATOR_T_HPP
