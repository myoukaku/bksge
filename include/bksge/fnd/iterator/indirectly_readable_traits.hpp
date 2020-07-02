/**
 *	@file	indirectly_readable_traits.hpp
 *
 *	@brief	indirectly_readable_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP
#define BKSGE_FND_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/remove_extent.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bool = bksge::is_object<T>::value>
struct cond_value_type {};

template <typename T>
struct cond_value_type<T, true>
{
	using value_type = bksge::remove_cv_t<T>;
};

template <typename, typename = bksge::void_t<>>
struct has_value_type
	: public bksge::false_type {};
 
template <typename T>
struct has_value_type<T, bksge::void_t<typename T::value_type>>
	: public bksge::true_type {};

template <typename, typename = bksge::void_t<>>
struct has_element_type
	: public bksge::false_type {};
 
template <typename T>
struct has_element_type<T, bksge::void_t<typename T::element_type>>
	: public bksge::true_type {};

}	// namespace detail

// (1) Primary template
template <typename I, typename = void>
struct indirectly_readable_traits {};

// (2) Specialization for pointers
template <typename T>
struct indirectly_readable_traits<T*>
	: public detail::cond_value_type<T> {};

// (3) Specialization for array types
template <typename T>
struct indirectly_readable_traits<T, bksge::enable_if_t<!bksge::is_const<T>::value && bksge::is_array<T>::value>>
{
	using value_type = bksge::remove_cv_t<bksge::remove_extent_t<T>>;
};

// (4) Specialization for const-qualified types
template <typename I>
struct indirectly_readable_traits<const I>
	: public indirectly_readable_traits<I> {};

// (5) Specialization for types that define a public and accessible member type value_type
template <typename T>
struct indirectly_readable_traits<T, bksge::enable_if_t<!bksge::is_const<T>::value && detail::has_value_type<T>::value>>
	: public detail::cond_value_type<typename T::value_type> {};

// (6) Specialization for types that define a public and accessible member type element_type
template <typename T>
struct indirectly_readable_traits<T, bksge::enable_if_t<!bksge::is_const<T>::value && detail::has_element_type<T>::value>>
	: public detail::cond_value_type<typename T::element_type> {};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP
