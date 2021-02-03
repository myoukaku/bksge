/**
 *	@file	unit_test_system_error_error_code.cpp
 *
 *	@brief	error_code のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/system_error.hpp>
#include <bksge/fnd/sstream.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/ios/io_errc.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace bksge_system_error_test
{
namespace error_code_test
{

enum testing
{
	zero, one, two
};

}	// namespace error_code_test
}	// namespace bksge_system_error_test

namespace BKSGE_IS_ERROR_CODE_ENUM_NAMESPACE
{

template <>
struct is_error_code_enum<bksge_system_error_test::error_code_test::testing>
	: public bksge::true_type {};

}	// namespace BKSGE_IS_ERROR_CODE_ENUM_NAMESPACE

namespace bksge_system_error_test
{
namespace error_code_test
{

bksge::error_code
make_error_code(testing x)
{
	return bksge::error_code(static_cast<int>(x), bksge::generic_category());
}

GTEST_TEST(ErrorCodeTest, DefaultCtorTest)
{
	bksge::error_code ec;
	EXPECT_TRUE(ec.value() == 0);
	EXPECT_TRUE(ec.category() == bksge::system_category());
}

GTEST_TEST(ErrorCodeTest, EnumCtorTest)
{
	bksge::error_code ec(two);
	EXPECT_TRUE(ec.value() == 2);
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorCodeTest, IntCtorTest)
{
	{
		bksge::error_code ec(6, bksge::system_category());
		EXPECT_TRUE(ec.value() == 6);
		EXPECT_TRUE(ec.category() == bksge::system_category());
	}
	{
		bksge::error_code ec(8, bksge::generic_category());
		EXPECT_TRUE(ec.value() == 8);
		EXPECT_TRUE(ec.category() == bksge::generic_category());
	}
}

GTEST_TEST(ErrorCodeTest, AssignTest)
{
	{
		bksge::error_code ec;
		ec.assign(6, bksge::system_category());
		EXPECT_TRUE(ec.value() == 6);
		EXPECT_TRUE(ec.category() == bksge::system_category());
	}
	{
		bksge::error_code ec;
		ec.assign(8, bksge::generic_category());
		EXPECT_TRUE(ec.value() == 8);
		EXPECT_TRUE(ec.category() == bksge::generic_category());
	}
}

GTEST_TEST(ErrorCodeTest, AssignEnumTest)
{
	bksge::error_code ec;
	ec = two;
	EXPECT_TRUE(ec.value() == 2);
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorCodeTest, ClearTest)
{
	bksge::error_code ec;
	ec.assign(6, bksge::generic_category());
	EXPECT_TRUE(ec.value() == 6);
	EXPECT_TRUE(ec.category() == bksge::generic_category());
	ec.clear();
	EXPECT_TRUE(ec.value() == 0);
	EXPECT_TRUE(ec.category() == bksge::system_category());
}

GTEST_TEST(ErrorCodeTest, MakeErrorCodeTest)
{
	bksge::error_code ec = bksge::make_error_code(bksge::errc::operation_canceled);
	EXPECT_TRUE(ec.value() == static_cast<int>(bksge::errc::operation_canceled));
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorCodeTest, StreamInserterTest)
{
	bksge::ostringstream out;
	out << bksge::error_code(bksge::io_errc::stream);
	EXPECT_TRUE(out.str() == "iostream:1");
}

GTEST_TEST(ErrorCodeTest, BoolTest)
{
	{
		const bksge::error_code ec(6, bksge::generic_category());
		EXPECT_TRUE(static_cast<bool>(ec));
	}
	{
		const bksge::error_code ec(0, bksge::generic_category());
		EXPECT_TRUE(!static_cast<bool>(ec));
	}
}

GTEST_TEST(ErrorCodeTest, CategoryTest)
{
	const bksge::error_code ec(6, bksge::generic_category());
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorCodeTest, DefaultErrorConditionTest)
{
	{
		const bksge::error_code ec(6, bksge::generic_category());
		bksge::error_condition e_cond = ec.default_error_condition();
		EXPECT_TRUE(e_cond == ec);
	}
	{
		const bksge::error_code ec(6, bksge::system_category());
		bksge::error_condition e_cond = ec.default_error_condition();
		EXPECT_TRUE(e_cond == ec);
	}
}

GTEST_TEST(ErrorCodeTest, MessageTest)
{
	const bksge::error_code ec(6, bksge::generic_category());
	EXPECT_TRUE(ec.message() == bksge::generic_category().message(6));
}

GTEST_TEST(ErrorCodeTest, ValueTest)
{
	const bksge::error_code ec(6, bksge::system_category());
	EXPECT_TRUE(ec.value() == 6);
}

GTEST_TEST(ErrorCodeTest, LtTest)
{
	const bksge::error_code ec1(6, bksge::generic_category());
	const bksge::error_code ec2(7, bksge::generic_category());
	EXPECT_TRUE (ec1 < ec2);
	EXPECT_FALSE(ec2 < ec1);
}

GTEST_TEST(ErrorCodeTest, CompareTest)
{
	bksge::error_code e_code1(5, bksge::generic_category());
	bksge::error_code e_code2(5, bksge::system_category());
	bksge::error_code e_code3(6, bksge::generic_category());
	bksge::error_code e_code4(6, bksge::system_category());
	bksge::error_condition e_condition1(5, bksge::generic_category());
	bksge::error_condition e_condition2(5, bksge::system_category());
	bksge::error_condition e_condition3(6, bksge::generic_category());
	bksge::error_condition e_condition4(6, bksge::system_category());

	EXPECT_TRUE (e_code1 == e_code1);
	EXPECT_FALSE(e_code1 == e_code2);
	EXPECT_FALSE(e_code1 == e_code3);
	EXPECT_FALSE(e_code1 == e_code4);
	EXPECT_TRUE (e_code1 == e_condition1);
	EXPECT_FALSE(e_code1 == e_condition2);
	EXPECT_FALSE(e_code1 == e_condition3);
	EXPECT_FALSE(e_code1 == e_condition4);

	EXPECT_FALSE(e_code1 != e_code1);
	EXPECT_TRUE (e_code1 != e_code2);
	EXPECT_TRUE (e_code1 != e_code3);
	EXPECT_TRUE (e_code1 != e_code4);
	EXPECT_FALSE(e_code1 != e_condition1);
	EXPECT_TRUE (e_code1 != e_condition2);
	EXPECT_TRUE (e_code1 != e_condition3);
	EXPECT_TRUE (e_code1 != e_condition4);

	EXPECT_FALSE(e_code2 == e_code1);
	EXPECT_TRUE (e_code2 == e_code2);
	EXPECT_FALSE(e_code2 == e_code3);
	EXPECT_FALSE(e_code2 == e_code4);
	EXPECT_FALSE(e_code2 == e_condition1);
	EXPECT_TRUE (e_code2 == e_condition2);
	EXPECT_FALSE(e_code2 == e_condition3);
	EXPECT_FALSE(e_code2 == e_condition4);

	EXPECT_TRUE (e_code2 != e_code1);
	EXPECT_FALSE(e_code2 != e_code2);
	EXPECT_TRUE (e_code2 != e_code3);
	EXPECT_TRUE (e_code2 != e_code4);
	EXPECT_TRUE (e_code2 != e_condition1);
	EXPECT_FALSE(e_code2 != e_condition2);
	EXPECT_TRUE (e_code2 != e_condition3);
	EXPECT_TRUE (e_code2 != e_condition4);

	EXPECT_FALSE(e_code3 == e_code1);
	EXPECT_FALSE(e_code3 == e_code2);
	EXPECT_TRUE (e_code3 == e_code3);
	EXPECT_FALSE(e_code3 == e_code4);
	EXPECT_FALSE(e_code3 == e_condition1);
	EXPECT_FALSE(e_code3 == e_condition2);
	EXPECT_TRUE (e_code3 == e_condition3);
	EXPECT_FALSE(e_code3 == e_condition4);

	EXPECT_TRUE (e_code3 != e_code1);
	EXPECT_TRUE (e_code3 != e_code2);
	EXPECT_FALSE(e_code3 != e_code3);
	EXPECT_TRUE (e_code3 != e_code4);
	EXPECT_TRUE (e_code3 != e_condition1);
	EXPECT_TRUE (e_code3 != e_condition2);
	EXPECT_FALSE(e_code3 != e_condition3);
	EXPECT_TRUE (e_code3 != e_condition4);

	EXPECT_FALSE(e_code4 == e_code1);
	EXPECT_FALSE(e_code4 == e_code2);
	EXPECT_FALSE(e_code4 == e_code3);
	EXPECT_TRUE (e_code4 == e_code4);
	EXPECT_FALSE(e_code4 == e_condition1);
	EXPECT_FALSE(e_code4 == e_condition2);
	EXPECT_FALSE(e_code4 == e_condition3);
	EXPECT_TRUE (e_code4 == e_condition4);

	EXPECT_TRUE (e_code4 != e_code1);
	EXPECT_TRUE (e_code4 != e_code2);
	EXPECT_TRUE (e_code4 != e_code3);
	EXPECT_FALSE(e_code4 != e_code4);
	EXPECT_TRUE (e_code4 != e_condition1);
	EXPECT_TRUE (e_code4 != e_condition2);
	EXPECT_TRUE (e_code4 != e_condition3);
	EXPECT_FALSE(e_code4 != e_condition4);

	EXPECT_TRUE (e_condition1 == e_code1);
	EXPECT_FALSE(e_condition1 == e_code2);
	EXPECT_TRUE (e_condition1 != e_code3);
	EXPECT_TRUE (e_condition1 != e_code4);
	EXPECT_TRUE (e_condition1 == e_condition1);
	EXPECT_TRUE (e_condition1 != e_condition2);
	EXPECT_TRUE (e_condition1 != e_condition3);
	EXPECT_TRUE (e_condition1 != e_condition4);

	EXPECT_TRUE(e_condition2 != e_code1);
	EXPECT_TRUE(e_condition2 == e_code2);
	EXPECT_TRUE(e_condition2 != e_code3);
	EXPECT_TRUE(e_condition2 != e_code4);
	EXPECT_TRUE(e_condition2 != e_condition1);
	EXPECT_TRUE(e_condition2 == e_condition2);
	EXPECT_TRUE(e_condition2 != e_condition3);
	EXPECT_TRUE(e_condition2 != e_condition4);

	EXPECT_TRUE (e_condition3 != e_code1);
	EXPECT_TRUE (e_condition3 != e_code2);
	EXPECT_TRUE (e_condition3 == e_code3);
	EXPECT_FALSE(e_condition3 == e_code4);
	EXPECT_TRUE (e_condition3 != e_condition1);
	EXPECT_TRUE (e_condition3 != e_condition2);
	EXPECT_TRUE (e_condition3 == e_condition3);
	EXPECT_TRUE (e_condition3 != e_condition4);

	EXPECT_TRUE(e_condition4 != e_code1);
	EXPECT_TRUE(e_condition4 != e_code2);
	EXPECT_TRUE(e_condition4 != e_code3);
	EXPECT_TRUE(e_condition4 == e_code4);
	EXPECT_TRUE(e_condition4 != e_condition1);
	EXPECT_TRUE(e_condition4 != e_condition2);
	EXPECT_TRUE(e_condition4 != e_condition3);
	EXPECT_TRUE(e_condition4 == e_condition4);
}

inline void hash_test(int i)
{
	typedef bksge::error_code T;
	typedef bksge::hash<T> H;
	H h;
	T ec(i, bksge::system_category());
	const bksge::size_t result = h(ec);
	EXPECT_TRUE(result == static_cast<bksge::size_t>(i));
	((void)result); // Prevent unused warning
}

GTEST_TEST(ErrorCodeTest, HashTest)
{
	hash_test(0);
	hash_test(2);
	hash_test(10);
}

}	// namespace error_code_test
}	// namespace bksge_system_error_test
