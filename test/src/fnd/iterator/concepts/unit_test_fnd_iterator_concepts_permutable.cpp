/**
 *	@file	unit_test_fnd_iterator_concepts_permutable.cpp
 *
 *	@brief	permutable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <vector>
#include <streambuf>
#include <memory>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_PERMUTABLE_TEST(B, ...)	\
	static_assert(B == bksge::permutable<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::permutable_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_PERMUTABLE_TEST(B, ...)	\
	static_assert(B == bksge::permutable_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_iterator_test
{

namespace permutable_test
{

BKSGE_PERMUTABLE_TEST(true,  int      *);
BKSGE_PERMUTABLE_TEST(false, int const*);
BKSGE_PERMUTABLE_TEST(false, int      * const);
BKSGE_PERMUTABLE_TEST(false, int const* const);
BKSGE_PERMUTABLE_TEST(false, void*);
BKSGE_PERMUTABLE_TEST(false, void* const);

BKSGE_PERMUTABLE_TEST(true,  std::array<int, 1>::iterator);
BKSGE_PERMUTABLE_TEST(false, std::array<int, 1>::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  std::deque<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, std::deque<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  std::forward_list<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, std::forward_list<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  std::list<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, std::list<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  std::string::iterator);
BKSGE_PERMUTABLE_TEST(false, std::string::const_iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::string_view::iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::string_view::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  std::vector<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, std::vector<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(false, std::istreambuf_iterator<char>);
BKSGE_PERMUTABLE_TEST(false, std::ostreambuf_iterator<char>);
BKSGE_PERMUTABLE_TEST(false, std::shared_ptr<int>);
BKSGE_PERMUTABLE_TEST(false, std::unique_ptr<int>);

}	// namespace permutable_test

}	// namespace bksge_iterator_test

#undef BKSGE_PERMUTABLE_TEST
