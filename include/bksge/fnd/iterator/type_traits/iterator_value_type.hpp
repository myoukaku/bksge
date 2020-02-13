/**
 *	@file	iterator_value_type.hpp
 *
 *	@brief	iterator_value_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_VALUE_TYPE_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_VALUE_TYPE_HPP

#include <iterator>

namespace bksge
{

template <typename Iterator>
using iterator_value_type =
	typename std::iterator_traits<Iterator>::value_type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_VALUE_TYPE_HPP
