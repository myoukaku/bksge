/**
 *	@file	iterator_pointer.hpp
 *
 *	@brief	iterator_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_POINTER_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_POINTER_HPP

#include <iterator>

namespace bksge
{

template <typename Iterator>
using iterator_pointer =
	typename std::iterator_traits<Iterator>::pointer;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_POINTER_HPP
