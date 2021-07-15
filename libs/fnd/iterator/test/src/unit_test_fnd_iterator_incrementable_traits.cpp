/**
 *	@file	unit_test_fnd_iterator_incrementable_traits.cpp
 *
 *	@brief	incrementable_traits のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/make_signed.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace incrementable_traits_test
{

template <typename, typename = bksge::void_t<>>
struct has_difference_type
	: public bksge::false_type {};
 
template <typename T>
struct has_difference_type<T, bksge::void_t<typename T::difference_type>>
	: public bksge::true_type {};

template <typename T>
struct X 
{
	using difference_type = T;
};

struct Y
{
	friend auto operator-(Y const&, Y const&) -> char
	{
		return 0;
	}
};

struct Z 
{
};

using T = int;

using vec_iterator = bksge::vector<T>::iterator;
using vec_const_iterator = bksge::vector<T>::const_iterator;

static_assert(bksge::is_same<bksge::incrementable_traits<T                          >::difference_type, bksge::make_signed_t<T>>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T      *                   >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T const*                   >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T      * const             >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T const* const             >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T[3]                       >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T const[3]                 >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T[]                        >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<T const[]                  >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<vec_iterator               >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<vec_iterator const         >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<vec_const_iterator         >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<vec_const_iterator const   >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<bksge::vector<T>           >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<bksge::vector<T> const     >::difference_type, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<X<T      >      >::difference_type, T>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<X<T const>      >::difference_type, T const>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<X<T      > const>::difference_type, T>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<X<T const> const>::difference_type, T const>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<Y      >::difference_type, signed char>::value, "");
static_assert(bksge::is_same<bksge::incrementable_traits<Y const>::difference_type, signed char>::value, "");

static_assert( has_difference_type<bksge::incrementable_traits<X<T>>>::value, "");
static_assert( has_difference_type<bksge::incrementable_traits<Y>>::value, "");
static_assert(!has_difference_type<bksge::incrementable_traits<Z>>::value, "");

}	// namespace incrementable_traits_test

}	// namespace bksge_iterator_test
