/**
 *	@file	unit_test_fnd_iterator_is_bidirectional_iterator.cpp
 *
 *	@brief	is_bidirectional_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/type_traits/is_bidirectional_iterator.hpp>
#include <iterator>
#include <array>
#include <vector>
#include <bksge/fnd/list.hpp>
#include <deque>
#include <string>
#include <regex>
#include <gtest/gtest.h>

namespace bksge_iterator_test
{

namespace is_bidirectional_iterator_test
{

enum enum_UDT{ one, two, three };

struct UDT {};

GTEST_TEST(IteratorTest, IsBidirectionalIteratorTest)
{
	static_assert(bksge::is_bidirectional_iterator<               int>::value == false, "");
	static_assert(bksge::is_bidirectional_iterator<const          int>::value == false, "");
	static_assert(bksge::is_bidirectional_iterator<      volatile int>::value == false, "");
	static_assert(bksge::is_bidirectional_iterator<const volatile int>::value == false, "");
	static_assert(bksge::is_bidirectional_iterator<float>::value              == false, "");
	static_assert(bksge::is_bidirectional_iterator<UDT>::value                == false, "");
	static_assert(bksge::is_bidirectional_iterator<enum_UDT>::value           == false, "");

	static_assert(bksge::is_bidirectional_iterator<               int*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<const          int*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<      volatile int*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<const volatile int*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<               char*>::value                         == true, "");
	static_assert(bksge::is_bidirectional_iterator<const          char*>::value                         == true, "");
	static_assert(bksge::is_bidirectional_iterator<      volatile char*>::value                         == true, "");
	static_assert(bksge::is_bidirectional_iterator<const volatile char*>::value                         == true, "");
	static_assert(bksge::is_bidirectional_iterator<               UDT*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<const          UDT*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<      volatile UDT*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<const volatile UDT*>::value                          == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::vector<int>::iterator>::value                   == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::vector<int>::const_iterator>::value             == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::vector<int>::reverse_iterator>::value           == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::vector<int>::const_reverse_iterator>::value     == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::deque<UDT>::iterator>::value                    == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::deque<UDT>::const_iterator>::value              == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::deque<UDT>::reverse_iterator>::value            == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::deque<UDT>::const_reverse_iterator>::value      == true, "");
	static_assert(bksge::is_bidirectional_iterator<bksge::list<float>::iterator>::value                   == true, "");
	static_assert(bksge::is_bidirectional_iterator<bksge::list<float>::const_iterator>::value             == true, "");
	static_assert(bksge::is_bidirectional_iterator<bksge::list<float>::reverse_iterator>::value           == true, "");
	static_assert(bksge::is_bidirectional_iterator<bksge::list<float>::const_reverse_iterator>::value     == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::string::iterator>::value                        == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::string::const_iterator>::value                  == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::string::reverse_iterator>::value                == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::string::const_reverse_iterator>::value          == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::array<int, 3>::iterator>::value                 == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::array<int, 3>::const_iterator>::value           == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::array<int, 3>::reverse_iterator>::value         == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::array<int, 3>::const_reverse_iterator>::value   == true, "");
	static_assert(bksge::is_bidirectional_iterator<std::istream_iterator<int>>::value                   == false, "");
	static_assert(bksge::is_bidirectional_iterator<std::ostream_iterator<int>>::value                   == false, "");
	static_assert(bksge::is_bidirectional_iterator<std::back_insert_iterator<std::vector<int>>>::value  == false, "");
	static_assert(bksge::is_bidirectional_iterator<std::front_insert_iterator<std::vector<int>>>::value == false, "");
	static_assert(bksge::is_bidirectional_iterator<std::insert_iterator<std::vector<int>>>::value       == false, "");
	static_assert(bksge::is_bidirectional_iterator<std::regex_iterator<std::string::iterator>>::value   == false, "");
}

}	// namespace is_bidirectional_iterator_test

}	// namespace bksge_iterator_test
