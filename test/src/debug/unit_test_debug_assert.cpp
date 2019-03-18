/**
 *	@file	unit_test_debug_assert.cpp
 *
 *	@brief	BKSGE_ASSERT のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <string>
#include <gtest/gtest.h>

#include <bksge/assert.hpp>

namespace bksge_debug_assert_test
{

static int         s_invoke_count = 0;
static std::string s_file_name;
static int         s_line_number;
static std::string s_function_name;
static std::string s_expr_str;
static std::string s_evaluated_expr_str;
static std::string s_msg;

inline int func(void) { return 1; }

GTEST_TEST(DebugAssertTest, SuccessTest)
{
	int x = 3;
	int y = 7;
	int z = 2;
	BKSGE_ASSERT(x == 3);
	BKSGE_ASSERT(3 == x);
	BKSGE_ASSERT_MSG(x != y, "x equal y");
	BKSGE_ASSERT(x < 4);
	BKSGE_ASSERT(8 > y);
	BKSGE_ASSERT_MSG(x <= 3, "x less than 3");
	BKSGE_ASSERT(8 >= y);
	BKSGE_ASSERT(x + y == 10);
	BKSGE_ASSERT(x * 2 == 6);
	BKSGE_ASSERT(x * y - z == 19);
	BKSGE_ASSERT(x / func() == 3);

	BKSGE_ASSERT(x == 3 && y == 7);
	BKSGE_ASSERT(x > 0 && y < 8 && z == 2);

	BKSGE_ASSERT(x == 3 || y == 7);
	BKSGE_ASSERT(x == 2 || y == 7);
	BKSGE_ASSERT(x == 3 || y == 6);
}

BKSGE_CXX14_CONSTEXPR int add(int x, int y)
{
	return
		BKSGE_ASSERT(x != 0),
		BKSGE_ASSERT(y != 0),
		(x + y);
}

GTEST_TEST(DebugAssertTest, ConstexprTest)
{
	BKSGE_CXX14_CONSTEXPR int x = add(2, 1);
	BKSGE_ASSERT(x == 3);
	BKSGE_ASSERT_MSG(x == 3, "foo");

	int y = add(3, 1);
	BKSGE_ASSERT(y == 4);
}

inline void MyAssertionHandler(const bksge::debug::assertion_info& info)
{
	s_invoke_count++;
	s_file_name          = info.file_name;
	s_line_number        = info.line_number;
	s_function_name      = info.function_name;
	s_expr_str           = info.expr_str;
	s_evaluated_expr_str = info.evaluated_expr_str;
	s_msg                = info.msg;
}

GTEST_TEST(DebugAssertTest, FailureTest)
{
	auto handler_old = bksge::debug::get_assertion_handler();
	bksge::debug::set_assertion_handler(MyAssertionHandler);
	s_invoke_count = 0;

	int x = 3;
	int y = 7;
	int z = 2;
	int line_num = 0;

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x == 4);
	EXPECT_EQ(1, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x == 4", s_expr_str);
	EXPECT_EQ("(3 == 4)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT_MSG(5 == x, "hoge");
	EXPECT_EQ(2, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("5 == x", s_expr_str);
	EXPECT_EQ("(5 == 3)", s_evaluated_expr_str);
	EXPECT_EQ("hoge", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT_MSG(x != 3, "foo");
	EXPECT_EQ(3, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x != 3", s_expr_str);
	EXPECT_EQ("(3 != 3)", s_evaluated_expr_str);
	EXPECT_EQ("foo", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x < 2);
	EXPECT_EQ(4, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x < 2", s_expr_str);
	EXPECT_EQ("(3 < 2)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(6 > y);
	EXPECT_EQ(5, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("6 > y", s_expr_str);
	EXPECT_EQ("(6 > 7)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x <= 1);
	EXPECT_EQ(6, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x <= 1", s_expr_str);
	EXPECT_EQ("(3 <= 1)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(5 >= y);
	EXPECT_EQ(7, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("5 >= y", s_expr_str);
	EXPECT_EQ("(5 >= 7)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x + y == 11);
	EXPECT_EQ(8, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x + y == 11", s_expr_str);
	EXPECT_EQ("((3 + 7) == 11)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x * 2 != 6);
	EXPECT_EQ(9, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x * 2 != 6", s_expr_str);
	EXPECT_EQ("((3 * 2) != 6)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT_MSG(x * y + z == 24, "bar");
	EXPECT_EQ(10, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x * y + z == 24", s_expr_str);
	EXPECT_EQ("(((3 * 7) + 2) == 24)", s_evaluated_expr_str);
	EXPECT_EQ("bar", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x + func() != 4);
	EXPECT_EQ(11, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x + func() != 4", s_expr_str);
	EXPECT_EQ("((3 + 1) != 4)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	{
		int w = add(3, 0);
		(void)w;
		EXPECT_EQ(12, s_invoke_count);
		EXPECT_EQ(__FILE__, s_file_name);
		//EXPECT_EQ(line_num, s_line_number);
		//EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
		EXPECT_EQ("y != 0", s_expr_str);
		EXPECT_EQ("(0 != 0)", s_evaluated_expr_str);
		EXPECT_EQ("", s_msg);
	}

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x == 3 && y == 8);
	EXPECT_EQ(13, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x == 3 && y == 8", s_expr_str);
	EXPECT_EQ("((3 == 3) && 0)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x == 2 && y == 7);
	EXPECT_EQ(14, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x == 2 && y == 7", s_expr_str);
	EXPECT_EQ("((3 == 2) && 1)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	line_num = __LINE__ + 1;
	BKSGE_ASSERT(x == 4 || y == 8);
	EXPECT_EQ(15, s_invoke_count);
	EXPECT_EQ(__FILE__, s_file_name);
	EXPECT_EQ(line_num, s_line_number);
	EXPECT_EQ(BKSGE_CURRENT_FUNCTION, s_function_name);
	EXPECT_EQ("x == 4 || y == 8", s_expr_str);
	EXPECT_EQ("((3 == 4) || 0)", s_evaluated_expr_str);
	EXPECT_EQ("", s_msg);

	bksge::debug::set_assertion_handler(handler_old);
}

}	// namespace bksge_debug_assert_test

#define BKSGE_DISABLE_ASSERTS
#include <bksge/assert.hpp>

namespace bksge_debug_assert_test
{

GTEST_TEST(DebugAssertTest, DisableTest)
{
	auto handler_old = bksge::debug::get_assertion_handler();
	bksge::debug::set_assertion_handler(MyAssertionHandler);
	s_invoke_count = 0;

	int x = 3;
	BKSGE_ASSERT(x == 0);
	BKSGE_ASSERT(x != 3);
	BKSGE_ASSERT_MSG(x < 0, "");
	BKSGE_ASSERT(x > 3);
	BKSGE_ASSERT(x <= 2);
	BKSGE_ASSERT(x >= 4);
	(void)x;

	EXPECT_EQ(0, s_invoke_count);

	bksge::debug::set_assertion_handler(handler_old);
}

}	// namespace bksge_debug_assert_test

#undef BKSGE_DISABLE_ASSERTS
#include <bksge/assert.hpp>

namespace bksge_debug_assert_test
{

GTEST_TEST(DebugAssertTest, EnableTest)
{
	auto handler_old = bksge::debug::get_assertion_handler();
	bksge::debug::set_assertion_handler(MyAssertionHandler);
	s_invoke_count = 0;

	int x = 3;
	BKSGE_ASSERT(x == 0);
	BKSGE_ASSERT(x != 3);
	BKSGE_ASSERT_MSG(x < 0, "");
	BKSGE_ASSERT(x > 3);
	BKSGE_ASSERT(x <= 2);
	BKSGE_ASSERT(x >= 4);
	(void)x;

	EXPECT_EQ(6, s_invoke_count);

	bksge::debug::set_assertion_handler(handler_old);
}

}	// namespace bksge_debug_assert_test
