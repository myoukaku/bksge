﻿/**
 *	@file	unit_test_fnd_iterator_iter_value_t.cpp
 *
 *	@brief	iter_value_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/vector.hpp>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace iter_value_t_test
{

template <typename T>
struct have_value
{
	using value_type = T;
};

template <typename T>
struct have_element
{
	using element_type = T;
};

using T = int;

using vec_iterator = bksge::vector<T>::iterator;
using vec_const_iterator = bksge::vector<T>::const_iterator;

static_assert(bksge::is_same<bksge::iter_value_t<T               *          >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const         *          >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T       volatile*          >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const volatile*          >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T               * const    >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const         * const    >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T       volatile* const    >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const volatile* const    >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T               * volatile >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const         * volatile >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T       volatile* volatile >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const volatile* volatile >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T[3]                       >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const[3]                 >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T[]                        >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<T const[]                  >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<vec_iterator               >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<vec_iterator const         >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<vec_const_iterator         >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<vec_const_iterator const   >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<bksge::vector<T>           >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<bksge::vector<T> const     >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_value<T      >        >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_value<T const>        >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_value<T      > const  >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_value<T const> const  >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_element<T      >      >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_element<T const>      >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_element<T      > const>, T>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<have_element<T const> const>, T>::value, "");

}	// namespace iter_value_t_test

}	// namespace bksge_iterator_test
