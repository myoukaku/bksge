/**
 *	@file	iterator_category.hpp
 *
 *	@brief	iterator_category の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_CATEGORY_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_CATEGORY_HPP

#include <iterator>

namespace bksge
{

template <typename Iterator>
using iterator_category =
	typename std::iterator_traits<Iterator>::iterator_category;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_CATEGORY_HPP
