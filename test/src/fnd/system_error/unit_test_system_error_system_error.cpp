/**
 *	@file	unit_test_system_error_system_error.cpp
 *
 *	@brief	system_error のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/system_error.hpp>
#include <bksge/fnd/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(SystemErrorTest, ErrorCodeCtorTest)
{
	bksge::system_error se(
		static_cast<int>(bksge::errc::not_a_directory),
		bksge::generic_category(),
		"some text");
	EXPECT_TRUE(se.code() == bksge::make_error_code(bksge::errc::not_a_directory));
	bksge::string what_message(se.what());
	EXPECT_TRUE(
		what_message.contains("not a directory") ||
		what_message.contains("Not a directory"));
}

GTEST_TEST(SystemErrorTest, ErrorCodeConstCharPointerCtorTest)
{
	bksge::string what_arg("test message");
	bksge::system_error se(make_error_code(bksge::errc::not_a_directory), what_arg.c_str());
	EXPECT_TRUE(se.code() == bksge::make_error_code(bksge::errc::not_a_directory));
	bksge::string what_message(se.what());
	EXPECT_TRUE(what_message.contains(what_arg));
	EXPECT_TRUE(
		what_message.contains("not a directory") ||
		what_message.contains("Not a directory"));
}

GTEST_TEST(SystemErrorTest, ErrorCodeStringCtorTest)
{
	bksge::string what_arg("test message");
	bksge::system_error se(make_error_code(bksge::errc::not_a_directory), what_arg);
	EXPECT_TRUE(se.code() == bksge::make_error_code(bksge::errc::not_a_directory));
	bksge::string what_message(se.what());
	EXPECT_TRUE(what_message.contains(what_arg));
	EXPECT_TRUE(
		what_message.contains("not a directory") ||
		what_message.contains("Not a directory"));
}

GTEST_TEST(SystemErrorTest, IntErrorCategoryCtorTest)
{
	bksge::system_error se(
		static_cast<int>(bksge::errc::not_a_directory),
		bksge::generic_category());
	EXPECT_TRUE(se.code() == bksge::make_error_code(bksge::errc::not_a_directory));
	bksge::string what_message(se.what());
	EXPECT_TRUE(
		what_message.contains("not a directory") ||
		what_message.contains("Not a directory"));
}

GTEST_TEST(SystemErrorTest, IntErrorCategoryConstCharPtrCtorTest)
{
	bksge::string what_arg("test message");
	bksge::system_error se(
		static_cast<int>(bksge::errc::not_a_directory),
		bksge::generic_category(), what_arg.c_str());
	EXPECT_TRUE(se.code() == bksge::make_error_code(bksge::errc::not_a_directory));
	bksge::string what_message(se.what());
	EXPECT_TRUE(what_message.contains(what_arg));
	EXPECT_TRUE(
		what_message.contains("not a directory") ||
		what_message.contains("Not a directory"));
}

GTEST_TEST(SystemErrorTest, IntErrorCategoryStringCtorTest)
{
	bksge::string what_arg("test message");
	bksge::system_error se(
		static_cast<int>(bksge::errc::not_a_directory),
		bksge::generic_category(), what_arg);
	EXPECT_TRUE(se.code() == bksge::make_error_code(bksge::errc::not_a_directory));
	bksge::string what_message(se.what());
	EXPECT_TRUE(what_message.contains(what_arg));
	EXPECT_TRUE(
		what_message.contains("not a directory") ||
		what_message.contains("Not a directory"));
}
