﻿/**
 *	@file	unit_test_fnd_iterator_is_iterator.cpp
 *
 *	@brief	is_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <iterator>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <regex>
#include <gtest/gtest.h>

namespace bksge_iterator_test
{

namespace is_iterator_test
{

enum enum_UDT{ one, two, three };

struct UDT {};

GTEST_TEST(IteratorTest, IsIteratorTest)
{
	static_assert(bksge::is_iterator<               int>::value == false, "");
	static_assert(bksge::is_iterator<const          int>::value == false, "");
	static_assert(bksge::is_iterator<      volatile int>::value == false, "");
	static_assert(bksge::is_iterator<const volatile int>::value == false, "");
	static_assert(bksge::is_iterator<float>::value              == false, "");
	static_assert(bksge::is_iterator<UDT>::value                == false, "");
	static_assert(bksge::is_iterator<enum_UDT>::value           == false, "");

	static_assert(bksge::is_iterator<               int*>::value                          == true, "");
	static_assert(bksge::is_iterator<const          int*>::value                          == true, "");
	static_assert(bksge::is_iterator<      volatile int*>::value                          == true, "");
	static_assert(bksge::is_iterator<const volatile int*>::value                          == true, "");
	static_assert(bksge::is_iterator<               char*>::value                         == true, "");
	static_assert(bksge::is_iterator<const          char*>::value                         == true, "");
	static_assert(bksge::is_iterator<      volatile char*>::value                         == true, "");
	static_assert(bksge::is_iterator<const volatile char*>::value                         == true, "");
	static_assert(bksge::is_iterator<               UDT*>::value                          == true, "");
	static_assert(bksge::is_iterator<const          UDT*>::value                          == true, "");
	static_assert(bksge::is_iterator<      volatile UDT*>::value                          == true, "");
	static_assert(bksge::is_iterator<const volatile UDT*>::value                          == true, "");
	static_assert(bksge::is_iterator<std::vector<int>::iterator>::value                   == true, "");
	static_assert(bksge::is_iterator<std::vector<int>::const_iterator>::value             == true, "");
	static_assert(bksge::is_iterator<std::vector<int>::reverse_iterator>::value           == true, "");
	static_assert(bksge::is_iterator<std::vector<int>::const_reverse_iterator>::value     == true, "");
	static_assert(bksge::is_iterator<std::deque<UDT>::iterator>::value                    == true, "");
	static_assert(bksge::is_iterator<std::deque<UDT>::const_iterator>::value              == true, "");
	static_assert(bksge::is_iterator<std::deque<UDT>::reverse_iterator>::value            == true, "");
	static_assert(bksge::is_iterator<std::deque<UDT>::const_reverse_iterator>::value      == true, "");
	static_assert(bksge::is_iterator<std::list<float>::iterator>::value                   == true, "");
	static_assert(bksge::is_iterator<std::list<float>::const_iterator>::value             == true, "");
	static_assert(bksge::is_iterator<std::list<float>::reverse_iterator>::value           == true, "");
	static_assert(bksge::is_iterator<std::list<float>::const_reverse_iterator>::value     == true, "");
	static_assert(bksge::is_iterator<std::string::iterator>::value                        == true, "");
	static_assert(bksge::is_iterator<std::string::const_iterator>::value                  == true, "");
	static_assert(bksge::is_iterator<std::string::reverse_iterator>::value                == true, "");
	static_assert(bksge::is_iterator<std::string::const_reverse_iterator>::value          == true, "");
	static_assert(bksge::is_iterator<std::array<int, 3>::iterator>::value                 == true, "");
	static_assert(bksge::is_iterator<std::array<int, 3>::const_iterator>::value           == true, "");
	static_assert(bksge::is_iterator<std::array<int, 3>::reverse_iterator>::value         == true, "");
	static_assert(bksge::is_iterator<std::array<int, 3>::const_reverse_iterator>::value   == true, "");
	static_assert(bksge::is_iterator<std::istream_iterator<int>>::value                   == true, "");
	static_assert(bksge::is_iterator<std::ostream_iterator<int>>::value                   == true, "");
	static_assert(bksge::is_iterator<std::back_insert_iterator<std::vector<int>>>::value  == true, "");
	static_assert(bksge::is_iterator<std::front_insert_iterator<std::vector<int>>>::value == true, "");
	static_assert(bksge::is_iterator<std::insert_iterator<std::vector<int>>>::value       == true, "");
//	static_assert(bksge::is_iterator<std::regex_iterator<std::string::iterator>>::value   == true, "");
}

}	// namespace is_iterator_test

}	// namespace bksge_iterator_test