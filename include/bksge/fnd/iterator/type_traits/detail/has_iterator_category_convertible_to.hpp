﻿/**
 *	@file	has_iterator_category_convertible_to.hpp
 *
 *	@brief	has_iterator_category_convertible_to の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO_HPP

#include <bksge/fnd/iterator/type_traits/detail/has_iterator_category.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_category.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <iterator>		// iterator_traits

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
		bksge::is_convertible<
			bksge::iterator_category<Iterator>,
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
