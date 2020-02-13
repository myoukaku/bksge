/**
 *	@file	iterator_reference.hpp
 *
 *	@brief	iterator_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_REFERENCE_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_REFERENCE_HPP

#include <iterator>

namespace bksge
{

template <typename Iterator>
using iterator_reference =
	typename std::iterator_traits<Iterator>::reference;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_ITERATOR_REFERENCE_HPP
