/**
 *	@file	unit_test_fnd_iterator_iter_difference_t.cpp
 *
 *	@brief	iter_difference_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace iter_difference_t_test
{

template <typename T>
struct have_difference 
{
	using difference_type = T;
};

struct can_difference
{
	friend auto operator-(can_difference const&, can_difference const&) -> char
	{
		return 0;
	}
};

using T = int;

using vec_iterator = std::vector<T>::iterator;
using vec_const_iterator = std::vector<T>::const_iterator;

static_assert(bksge::is_same<bksge::iter_difference_t<T      *                   >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<T const*                   >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<T      * const             >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<T const* const             >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<T[3]                       >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<T const[3]                 >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<T[]                        >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<T const[]                  >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<vec_iterator               >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<vec_iterator const         >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<vec_const_iterator         >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<vec_const_iterator const   >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<std::vector<T>             >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<std::vector<T> const       >, bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<have_difference <T      >      >, T>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<have_difference <T const>      >, T const>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<have_difference <T      > const>, T>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<have_difference <T const> const>, T const>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<can_difference      >, signed char>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<can_difference const>, signed char>::value, "");

}	// namespace iter_difference_t_test

}	// namespace bksge_iterator_test
