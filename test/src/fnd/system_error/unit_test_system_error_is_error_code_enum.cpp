/**
 *	@file	unit_test_system_error_is_error_code_enum.cpp
 *
 *	@brief	is_error_code_enum のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/system_error.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/string.hpp>
#include <gtest/gtest.h>

namespace bksge_system_error_test
{
namespace is_error_code_enum_test
{

class A
{
	A();
	operator bksge::error_code () const { return bksge::error_code(); }
};

}	// namespace is_error_code_enum_test
}	// namespace bksge_system_error_test

namespace BKSGE_IS_ERROR_CODE_ENUM_NAMESPACE
{

template <>
struct is_error_code_enum<bksge_system_error_test::is_error_code_enum_test::A>
	: public bksge::true_type {};

}	// namespace BKSGE_IS_ERROR_CODE_ENUM_NAMESPACE

GTEST_TEST(SystemErrorTest, IsErrorCodeEnumTest)
{
	static_assert((bksge::is_error_code_enum<void>::value == false), "");
	static_assert((bksge::is_error_code_enum<int>::value == false), "");
	static_assert((bksge::is_error_code_enum<bksge::nullptr_t>::value == false), "");
	static_assert((bksge::is_error_code_enum<bksge::string>::value == false), "");

	using namespace bksge_system_error_test::is_error_code_enum_test;
	static_assert((bksge::is_error_code_enum<A>::value == true), "");
}
