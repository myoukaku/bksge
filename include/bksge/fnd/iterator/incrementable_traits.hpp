/**
 *	@file	incrementable_traits.hpp
 *
 *	@brief	incrementable_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INCREMENTABLE_TRAITS_HPP
#define BKSGE_FND_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
//#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/make_signed.hpp>
//#include <bksge/fnd/type_traits/remove_cv.hpp>
//#include <bksge/fnd/type_traits/remove_extent.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

template <typename, typename = bksge::void_t<>>
struct has_difference_type
	: public bksge::false_type {};
 
template <typename T>
struct has_difference_type<T, bksge::void_t<typename T::difference_type>>
	: public bksge::true_type {};

template <typename, typename = bksge::void_t<>>
struct is_subtractable
	: public bksge::false_type {};
 
template <typename T>
struct is_subtractable<T, bksge::void_t<decltype(bksge::declval<T>() - bksge::declval<T>())>>
	: public bksge::true_type {};


}	// namespace detail

// (1) Primary template
template <typename, typename = void>
struct incrementable_traits {};

// (2) Specialization for pointers
template <typename T>
struct incrementable_traits<T*, bksge::enable_if_t<bksge::is_object<T>::value>>
{
	using difference_type = std::ptrdiff_t;
};

// (3) Specialization for const-qualified types
template <typename I>
struct incrementable_traits<I const>
	: public incrementable_traits<I> {};

// (4) Specialization for types that define a public and accessible member type difference_type
template <typename T>
struct incrementable_traits<
	T,
	bksge::enable_if_t<
		!bksge::is_const<T>::value &&
		detail::has_difference_type<T>::value
	>
>
{
	using difference_type = typename T::difference_type;
};

// (5) Specialization for types that do not define a public and accessible member type difference_type
//     but do support subtraction
template <typename T>
struct incrementable_traits<
	T,
	bksge::enable_if_t<
		!bksge::is_const<T>::value &&
		!bksge::is_pointer<T>::value &&
		!detail::has_difference_type<T>::value &&
		detail::is_subtractable<T>::value
	>
>
{
	using difference_type = bksge::make_signed_t<decltype(bksge::declval<T>() - bksge::declval<T>())>;
};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INCREMENTABLE_TRAITS_HPP
