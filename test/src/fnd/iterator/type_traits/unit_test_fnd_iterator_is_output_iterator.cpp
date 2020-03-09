/**
 *	@file	unit_test_fnd_iterator_is_output_iterator.cpp
 *
 *	@brief	is_output_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/type_traits/is_output_iterator.hpp>
#include <iterator>
#include <array>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <deque>
#include <string>
#include <regex>
#include <gtest/gtest.h>

namespace bksge_iterator_test
{

namespace is_output_iterator_test
{

enum enum_UDT{ one, two, three };

struct UDT {};

GTEST_TEST(IteratorTest, IsOutputIteratorTest)
{
	static_assert(bksge::is_output_iterator<               int>::value == false, "");
	static_assert(bksge::is_output_iterator<const          int>::value == false, "");
	static_assert(bksge::is_output_iterator<      volatile int>::value == false, "");
	static_assert(bksge::is_output_iterator<const volatile int>::value == false, "");
	static_assert(bksge::is_output_iterator<float>::value              == false, "");
	static_assert(bksge::is_output_iterator<UDT>::value                == false, "");
	static_assert(bksge::is_output_iterator<enum_UDT>::value           == false, "");

#if 0
	// forward_iterator_tag は output_iterator_tag を継承するとは限らない
	static_assert(bksge::is_output_iterator<               int*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<const          int*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<      volatile int*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<const volatile int*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<               char*>::value                       == true, "");
	static_assert(bksge::is_output_iterator<const          char*>::value                       == true, "");
	static_assert(bksge::is_output_iterator<      volatile char*>::value                       == true, "");
	static_assert(bksge::is_output_iterator<const volatile char*>::value                       == true, "");
	static_assert(bksge::is_output_iterator<               UDT*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<const          UDT*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<      volatile UDT*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<const volatile UDT*>::value                        == true, "");
	static_assert(bksge::is_output_iterator<bksge::vector<int>::iterator>::value                 == true, "");
	static_assert(bksge::is_output_iterator<bksge::vector<int>::const_iterator>::value           == true, "");
	static_assert(bksge::is_output_iterator<bksge::vector<int>::reverse_iterator>::value         == true, "");
	static_assert(bksge::is_output_iterator<bksge::vector<int>::const_reverse_iterator>::value   == true, "");
	static_assert(bksge::is_output_iterator<std::deque<UDT>::iterator>::value                  == true, "");
	static_assert(bksge::is_output_iterator<std::deque<UDT>::const_iterator>::value            == true, "");
	static_assert(bksge::is_output_iterator<std::deque<UDT>::reverse_iterator>::value          == true, "");
	static_assert(bksge::is_output_iterator<std::deque<UDT>::const_reverse_iterator>::value    == true, "");
	static_assert(bksge::is_output_iterator<std::list<float>::iterator>::value                 == true, "");
	static_assert(bksge::is_output_iterator<std::list<float>::const_iterator>::value           == true, "");
	static_assert(bksge::is_output_iterator<std::list<float>::reverse_iterator>::value         == true, "");
	static_assert(bksge::is_output_iterator<std::list<float>::const_reverse_iterator>::value   == true, "");
	static_assert(bksge::is_output_iterator<std::string::iterator>::value                      == true, "");
	static_assert(bksge::is_output_iterator<std::string::const_iterator>::value                == true, "");
	static_assert(bksge::is_output_iterator<std::string::reverse_iterator>::value              == true, "");
	static_assert(bksge::is_output_iterator<std::string::const_reverse_iterator>::value        == true, "");
	static_assert(bksge::is_output_iterator<std::array<int, 3>::iterator>::value               == true, "");
	static_assert(bksge::is_output_iterator<std::array<int, 3>::const_iterator>::value         == true, "");
	static_assert(bksge::is_output_iterator<std::array<int, 3>::reverse_iterator>::value       == true, "");
	static_assert(bksge::is_output_iterator<std::array<int, 3>::const_reverse_iterator>::value == true, "");
	static_assert(bksge::is_output_iterator<std::regex_iterator<std::string::iterator>>::value == true, "");
#endif

	static_assert(bksge::is_output_iterator<std::istream_iterator<int>>::value                   == false, "");
	static_assert(bksge::is_output_iterator<std::ostream_iterator<int>>::value                   == true, "");
	static_assert(bksge::is_output_iterator<std::back_insert_iterator<bksge::vector<int>>>::value  == true, "");
	static_assert(bksge::is_output_iterator<std::front_insert_iterator<bksge::vector<int>>>::value == true, "");
	static_assert(bksge::is_output_iterator<std::insert_iterator<bksge::vector<int>>>::value       == true, "");
}

}	// namespace is_output_iterator_test

}	// namespace bksge_iterator_test
