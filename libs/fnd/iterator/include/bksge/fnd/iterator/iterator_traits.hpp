﻿/**
 *	@file	iterator_traits.hpp
 *
 *	@brief	iterator_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITERATOR_TRAITS_HPP
#define BKSGE_FND_ITERATOR_ITERATOR_TRAITS_HPP

#include <bksge/fnd/iterator/concepts/detail/iterator_traits_base.hpp>
#include <bksge/fnd/iterator/concepts/detail/is_iterator_traits_specialized.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

// primary template
template <typename Iterator>
struct iterator_traits
	: public detail::iterator_traits_base<Iterator> {};

namespace detail
{

template <typename T, typename>
using enable_iterator_traits_helper = T;

}	// namespace detail

template <typename T>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires bksge::is_object<T>::value
#endif
struct iterator_traits<
	detail::enable_iterator_traits_helper<
		T*,
		bksge::enable_if_t<bksge::is_object<T>::value>>>
{
	using iterator_concept  = bksge::contiguous_iterator_tag;
	using iterator_category = bksge::random_access_iterator_tag;
	using value_type	    = bksge::remove_cv_t<T>;
	using difference_type   = bksge::ptrdiff_t;
	using pointer	        = T*;
	using reference	        = T&;
};

namespace detail
{

template <typename T>
struct is_iterator_traits_specialized<
	detail::enable_iterator_traits_helper<
		T*,
		bksge::enable_if_t<bksge::is_object<T>::value>>>
{
	static const bool value = true;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITERATOR_TRAITS_HPP
