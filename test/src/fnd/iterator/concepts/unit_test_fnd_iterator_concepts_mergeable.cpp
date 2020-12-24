/**
 *	@file	unit_test_fnd_iterator_concepts_mergeable.cpp
 *
 *	@brief	mergeable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/mergeable.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <streambuf>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_MERGEABLE_TEST(B, ...)	\
	static_assert(B == bksge::mergeable<__VA_ARGS__>, "")
#else
#  define BKSGE_MERGEABLE_TEST(B, ...)	\
	static_assert(B == bksge::mergeable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace mergeable_test
{

BKSGE_MERGEABLE_TEST(true,  int*, int*, int*);
BKSGE_MERGEABLE_TEST(true,  int const*, int const*, int*);
BKSGE_MERGEABLE_TEST(false, int const*, int const*, int const*);
BKSGE_MERGEABLE_TEST(false, bksge::shared_ptr<int>, int*, int*);
BKSGE_MERGEABLE_TEST(false, int*, bksge::unique_ptr<int>, int*);
BKSGE_MERGEABLE_TEST(false, int*, int*, bksge::shared_ptr<int>);
BKSGE_MERGEABLE_TEST(true,  std::list<int>::iterator, std::array<int, 2>::iterator, std::vector<int>::iterator);
BKSGE_MERGEABLE_TEST(false, std::list<int>::iterator, std::array<int, 2>::iterator, std::vector<int>::const_iterator);
BKSGE_MERGEABLE_TEST(true,  std::list<int>::iterator, std::array<int, 2>::iterator, std::list<int>::iterator);
BKSGE_MERGEABLE_TEST(false, std::list<int>::iterator, std::array<int, 2>::iterator, std::list<int>::const_iterator);

}	// namespace mergeable_test

}	// namespace bksge_iterator_test

#undef BKSGE_MERGEABLE_TEST
