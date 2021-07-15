/**
 *	@file	unit_test_fnd_iterator_projected.cpp
 *
 *	@brief	projected のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_rvalue_reference_t.hpp>
#include <bksge/fnd/iterator/iter_common_reference_t.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstddef>

namespace bksge_iterator_test
{

namespace projected_test
{

using vec_iterator = bksge::vector<int>::iterator;
using vecitr_proj = bksge::projected<vec_iterator, bksge::identity>;

static_assert(bksge::is_indirectly_readable<vecitr_proj>::value, "");
static_assert(bksge::is_same<vecitr_proj::value_type, int>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<vecitr_proj>, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<vecitr_proj>, int>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<vecitr_proj>, int&>::value, "");
static_assert(bksge::is_same<bksge::iter_rvalue_reference_t<vecitr_proj>, int&&>::value, "");
static_assert(bksge::is_same<bksge::iter_common_reference_t<vecitr_proj>, int&>::value, "");

struct Proj
{
	double operator()(int) const { return 0.0; }
};
using vecitr_proj2 = bksge::projected<vec_iterator, Proj>;

static_assert(bksge::is_indirectly_readable<vecitr_proj2>::value, "");
static_assert(bksge::is_same<vecitr_proj2::value_type, double>::value, "");
static_assert(bksge::is_same<bksge::iter_difference_t<vecitr_proj2>, std::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iter_value_t<vecitr_proj2>, double>::value, "");
static_assert(bksge::is_same<bksge::iter_reference_t<vecitr_proj2>, double>::value, "");
static_assert(bksge::is_same<bksge::iter_rvalue_reference_t<vecitr_proj2>, double>::value, "");
static_assert(bksge::is_same<bksge::iter_common_reference_t<vecitr_proj2>, double>::value, "");

}	// namespace projected_test

}	// namespace bksge_iterator_test
