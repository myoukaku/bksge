﻿/**
 *	@file	is_random_access_iterator.hpp
 *
 *	@brief	is_random_access_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_RANDOM_ACCESS_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_RANDOM_ACCESS_ITERATOR_HPP

#include <bksge/fnd/iterator/type_traits/detail/has_iterator_category_convertible_to.hpp>
#include <bksge/fnd/iterator/tag.hpp>

namespace bksge
{

template <typename Iterator>
struct is_random_access_iterator
	: public detail::has_iterator_category_convertible_to<
		Iterator, bksge::random_access_iterator_tag
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_IS_RANDOM_ACCESS_ITERATOR_HPP
