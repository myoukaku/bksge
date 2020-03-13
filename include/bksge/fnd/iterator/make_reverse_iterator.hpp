/**
 *	@file	make_reverse_iterator.hpp
 *
 *	@brief	make_reverse_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_MAKE_REVERSE_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_MAKE_REVERSE_ITERATOR_HPP

#include <iterator>

#if defined(__cpp_lib_make_reverse_iterator) && (__cpp_lib_make_reverse_iterator >= 201402)

namespace bksge
{

using std::make_reverse_iterator;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <iterator>

namespace bksge
{

// make_reverse_iterator
template <typename Iterator>
inline BKSGE_CONSTEXPR std::reverse_iterator<Iterator>
make_reverse_iterator(Iterator it)
{
	return std::reverse_iterator<Iterator>(it);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_MAKE_REVERSE_ITERATOR_HPP
