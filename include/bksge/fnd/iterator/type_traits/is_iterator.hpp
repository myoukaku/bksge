/**
 *	@file	is_iterator.hpp
 *
 *	@brief	is_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/detail/has_iterator_category.hpp>
#include <iterator>

namespace bksge
{

template <typename Iterator>
struct is_iterator
	: public detail::has_iterator_category<
		std::iterator_traits<Iterator>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP
