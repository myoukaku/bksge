/**
 *	@file	iterator_category.hpp
 *
 *	@brief	iterator_category の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITERATOR_CATEGORY_HPP
#define BKSGE_FND_ITERATOR_ITERATOR_CATEGORY_HPP

#include <bksge/fnd/iterator/iterator_traits.hpp>

namespace bksge
{

template <typename Iterator>
using iterator_category =
	typename bksge::iterator_traits<Iterator>::iterator_category;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITERATOR_CATEGORY_HPP
