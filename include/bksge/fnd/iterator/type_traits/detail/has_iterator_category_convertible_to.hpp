/**
 *	@file	has_iterator_category_convertible_to.hpp
 *
 *	@brief	has_iterator_category_convertible_to の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO_HPP

#include <bksge/fnd/iterator/type_traits/detail/has_iterator_category.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <iterator>		// iterator_traits
#include <type_traits>	// is_convertible

namespace bksge
{

namespace detail
{

template <
	typename Iterator,
	typename Category,
	bool = has_iterator_category<std::iterator_traits<Iterator>>::value
>
struct has_iterator_category_convertible_to
	: public bksge::bool_constant<
		std::is_convertible<
			typename std::iterator_traits<Iterator>::iterator_category,
			Category
		>::value
	>
{};

template <typename Iterator, typename Category>
struct has_iterator_category_convertible_to<Iterator, Category, false>
	: public bksge::false_type
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO_HPP
