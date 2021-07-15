/**
 *	@file	incrementable_traits.hpp
 *
 *	@brief	incrementable_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_INCREMENTABLE_TRAITS_HPP
#define BKSGE_FND_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include <bksge/fnd/iterator/concepts/detail/has_difference_type.hpp>
#include <bksge/fnd/iterator/concepts/detail/is_void_pointer.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/make_signed.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

// (1) Primary template
template <typename, typename = void, typename = void>
struct incrementable_traits {};

// (2) Specialization for pointers
template <typename T>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires bksge::is_object<T>::value
#endif
struct incrementable_traits<T*
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, bksge::enable_if_t<bksge::is_object<T>::value>
#endif
>
{
	using difference_type = std::ptrdiff_t;
};

// (3) Specialization for const-qualified types
template <typename Iter>
struct incrementable_traits<Iter const>
	: public incrementable_traits<Iter> {};

// (4) Specialization for types that define a public and accessible member type difference_type
template <typename T>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires requires { typename T::difference_type; }
#endif
struct incrementable_traits<T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, bksge::enable_if_t<
		!bksge::is_const<T>::value &&
		!bksge::is_pointer<T>::value &&
		detail::has_difference_type<T>::value
	>
#endif
>
{
	using difference_type = typename T::difference_type;
};

// GCC 10 だと 下の
// { a - b } -> bksge::integral;
// の行で error: invalid use of ‘void’
// のエラーになってしまうのでそれを回避する
#if defined(__GNUC__) && (__GNUC__ == 10)
#define BKSGE_GCC_10	1
#else
#define BKSGE_GCC_10	0
#endif

// (5) Specialization for types that do not define a public and accessible member type difference_type
//     but do support subtraction
template <typename T>
#if defined(BKSGE_HAS_CXX20_CONCEPTS) && !BKSGE_GCC_10
requires (
	!requires { typename T::difference_type; } &&
	requires(T const& a, T const& b)
	{
		{ a - b } -> bksge::integral;
	})
#endif
struct incrementable_traits<T
#if !(defined(BKSGE_HAS_CXX20_CONCEPTS) && !BKSGE_GCC_10)
	, bksge::enable_if_t<
		!bksge::is_const<T>::value &&
		!bksge::is_pointer<T>::value &&
		!detail::has_difference_type<T>::value
	>
	, bksge::enable_if_t<
		bksge::is_integral<decltype(bksge::declval<T>() - bksge::declval<T>())>::value
	>
#endif
>
{
	using difference_type = bksge::make_signed_t<decltype(bksge::declval<T>() - bksge::declval<T>())>;
};

#undef BKSGE_GCC_10

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_INCREMENTABLE_TRAITS_HPP
