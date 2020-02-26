/**
 *	@file	is_bidirectional_iterator.hpp
 *
 *	@brief	is_bidirectional_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_BIDIRECTIONAL_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_BIDIRECTIONAL_ITERATOR_HPP

#include <bksge/fnd/iterator/type_traits/detail/has_iterator_category_convertible_to.hpp>
#include <iterator>

namespace bksge
{

template <typename Iterator>
struct is_bidirectional_iterator
	: public detail::has_iterator_category_convertible_to<
		Iterator, std::bidirectional_iterator_tag
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_BIDIRECTIONAL_ITERATOR_HPP
