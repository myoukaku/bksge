/**
 *	@file	unit_test_fnd_iterator_iter_common_reference_t.cpp
 *
 *	@brief	iter_common_reference_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/iter_common_reference_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace iter_common_reference_t_test
{

static_assert(bksge::is_same<bksge::iter_common_reference_t<int*>, int&>::value, "");
static_assert(bksge::is_same<bksge::iter_common_reference_t<char const*>, char const&>::value, "");
static_assert(bksge::is_same<bksge::iter_common_reference_t<std::vector<float>::iterator>, float&>::value, "");
static_assert(bksge::is_same<bksge::iter_common_reference_t<std::vector<float>::const_iterator>, float const&>::value, "");
static_assert(bksge::is_same<bksge::iter_common_reference_t<std::list<double>::iterator>, double&>::value, "");
static_assert(bksge::is_same<bksge::iter_common_reference_t<std::list<double>::const_iterator>, double const&>::value, "");

}	// namespace iter_common_reference_t_test

}	// namespace bksge_iterator_test
