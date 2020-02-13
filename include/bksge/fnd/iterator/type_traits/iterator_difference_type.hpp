/**
 *	@file	iterator_difference_type.hpp
 *
 *	@brief	iterator_difference_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_DIFFERENCE_TYPE_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_DIFFERENCE_TYPE_HPP

#include <iterator>

namespace bksge
{

template <typename Iterator>
using iterator_difference_type =
	typename std::iterator_traits<Iterator>::difference_type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_DIFFERENCE_TYPE_HPP
