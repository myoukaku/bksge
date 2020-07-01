/**
 *	@file	make_move_iterator.hpp
 *
 *	@brief	make_move_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_MAKE_MOVE_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_MAKE_MOVE_ITERATOR_HPP

#include <bksge/fnd/iterator/move_iterator.hpp>
#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17)

#include <iterator>

namespace bksge
{

using std::make_move_iterator;

}	// namespace bksge

#else

namespace bksge
{

template <typename Iterator>
inline BKSGE_CXX14_CONSTEXPR bksge::move_iterator<Iterator>
make_move_iterator(Iterator it)
{
    return bksge::move_iterator<Iterator>(it);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_MAKE_MOVE_ITERATOR_HPP
