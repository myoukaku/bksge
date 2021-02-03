/**
 *	@file	unit_test_system_error_is_error_condition_enum.cpp
 *
 *	@brief	is_error_condition_enum のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/system_error.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/string.hpp>
#include <gtest/gtest.h>

namespace bksge_system_error_test
{
namespace is_error_condition_enum_test
{

class A
{
	A();
	operator bksge::error_condition () const { return bksge::error_condition(); }
};

}	// namespace is_error_condition_enum_test
}	// namespace bksge_system_error_test

namespace BKSGE_IS_ERROR_CONDITION_ENUM_NAMESPACE
{

template <>
struct is_error_condition_enum<bksge_system_error_test::is_error_condition_enum_test::A>
	: public bksge::true_type {};

}	// namespace BKSGE_IS_ERROR_CONDITION_ENUM_NAMESPACE

GTEST_TEST(SystemErrorTest, IsErrorConditionEnumTest)
{
	static_assert((bksge::is_error_condition_enum<void>::value == false), "");
	static_assert((bksge::is_error_condition_enum<int>::value == false), "");
	static_assert((bksge::is_error_condition_enum<bksge::nullptr_t>::value == false), "");
	static_assert((bksge::is_error_condition_enum<bksge::string>::value == false), "");

	using namespace bksge_system_error_test::is_error_condition_enum_test;
	static_assert((bksge::is_error_condition_enum<A>::value == true), "");
}
