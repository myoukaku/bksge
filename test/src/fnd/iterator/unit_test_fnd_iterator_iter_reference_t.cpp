/**
 *	@file	unit_test_fnd_iterator_iter_reference_t.cpp
 *
 *	@brief	iter_reference_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <vector>
#include <streambuf>
#include <iterator>

namespace bksge_iterator_test
{

namespace iter_reference_t_test
{

using T = int;

using vec_iterator = std::vector<T>::iterator;
using vec_const_iterator = std::vector<T>::const_iterator;

static_assert(bksge::is_same<bksge::iter_reference_t<T      *                   >, T&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<T const*                   >, T const&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<T      * const             >, T&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<T const* const             >, T const&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<T[3]                       >, T&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<T const[3]                 >, T const&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<T[]                        >, T&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<T const[]                  >, T const&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<vec_iterator               >, T&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<vec_iterator const         >, T&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<vec_const_iterator         >, T const&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<vec_const_iterator const   >, T const&>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<std::istreambuf_iterator<T>>, T>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<std::ostreambuf_iterator<T>>, std::ostreambuf_iterator<T>&>::value, "");

}	// namespace iter_reference_t_test

}	// namespace bksge_iterator_test
