/**
 *	@file	unit_test_fnd_iterator_concepts_permutable.cpp
 *
 *	@brief	permutable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/deque.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <streambuf>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_PERMUTABLE_TEST(B, ...)	\
	static_assert(B == bksge::permutable<__VA_ARGS__>, "")
#else
#  define BKSGE_PERMUTABLE_TEST(B, ...)	\
	static_assert(B == bksge::permutable<__VA_ARGS__>::value, "")
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
BKSGE_PERMUTABLE_TEST(true,  bksge::deque<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::deque<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  bksge::forward_list<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::forward_list<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  bksge::list<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::list<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  bksge::string::iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::string::const_iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::string_view::iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::string_view::const_iterator);
BKSGE_PERMUTABLE_TEST(true,  bksge::vector<int>::iterator);
BKSGE_PERMUTABLE_TEST(false, bksge::vector<int>::const_iterator);
BKSGE_PERMUTABLE_TEST(false, std::istreambuf_iterator<char>);
BKSGE_PERMUTABLE_TEST(false, std::ostreambuf_iterator<char>);
BKSGE_PERMUTABLE_TEST(false, bksge::shared_ptr<int>);
BKSGE_PERMUTABLE_TEST(false, bksge::unique_ptr<int>);

}	// namespace permutable_test

}	// namespace bksge_iterator_test

#undef BKSGE_PERMUTABLE_TEST
