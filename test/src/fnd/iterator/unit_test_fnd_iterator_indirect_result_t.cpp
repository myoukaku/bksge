/**
 *	@file	unit_test_fnd_iterator_indirect_result_t.cpp
 *
 *	@brief	indirect_result_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/indirect_result_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <vector>

namespace bksge_iterator_test
{

namespace indirect_result_t_test
{

static_assert(bksge::is_same<bksge::indirect_result_t<int(int), int*>, int>::value, "");
static_assert(bksge::is_same<bksge::indirect_result_t<int(int), int const*>, int>::value, "");
static_assert(bksge::is_same<bksge::indirect_result_t<int(int), std::vector<int>::iterator>, int>::value, "");
static_assert(bksge::is_same<bksge::indirect_result_t<int(int), std::vector<int>::const_iterator>, int>::value, "");
static_assert(bksge::is_same<bksge::indirect_result_t<float(int, int), int*, int*>, float>::value, "");
static_assert(bksge::is_same<bksge::indirect_result_t<float(int, int), int const*, int const*>, float>::value, "");
static_assert(bksge::is_same<bksge::indirect_result_t<float(int, int), int*, std::vector<int>::iterator>, float>::value, "");
static_assert(bksge::is_same<bksge::indirect_result_t<float(int, int), int*, std::vector<int>::const_iterator>, float>::value, "");

}	// namespace indirect_result_t_test

}	// namespace bksge_iterator_test
