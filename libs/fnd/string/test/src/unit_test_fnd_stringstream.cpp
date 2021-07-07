/**
 *	@file	unit_test_fnd_stringstream.cpp
 *
 *	@brief	stringstream のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace bksge_string_test
{

namespace stringstream_test
{

template <typename CharT>
struct StringTestHelper;

template <>
struct StringTestHelper<char>
{
	BKSGE_CONSTEXPR static const char* multi_line_str() { return "abc\nbcd\ncd"; }
	BKSGE_CONSTEXPR static const char* csv_str() { return "abc,bcd,cd"; }
	BKSGE_CONSTEXPR static char comma_char() { return ','; }
	BKSGE_CONSTEXPR static const char* aababc() { return "aababc"; }
	BKSGE_CONSTEXPR static const char* abc() { return "abc"; }
	BKSGE_CONSTEXPR static const char* bcd() { return "bcd"; }
	BKSGE_CONSTEXPR static const char* cd() { return "cd"; }
};

template <>
struct StringTestHelper<wchar_t>
{
	BKSGE_CONSTEXPR static const wchar_t* multi_line_str() { return L"abc\nbcd\ncd"; }
	BKSGE_CONSTEXPR static const wchar_t* csv_str() { return L"abc,bcd,cd"; }
	BKSGE_CONSTEXPR static wchar_t comma_char() { return L','; }
	BKSGE_CONSTEXPR static const wchar_t* aababc() { return L"aababc"; }
	BKSGE_CONSTEXPR static const wchar_t* abc() { return L"abc"; }
	BKSGE_CONSTEXPR static const wchar_t* bcd() { return L"bcd"; }
	BKSGE_CONSTEXPR static const wchar_t* cd() { return L"cd"; }
};

template <typename CharT>
void OutputStreamTest()
{
	using string = bksge::basic_string<CharT>;
	using stringstream = std::basic_stringstream<CharT>;
	using Helper = StringTestHelper<CharT>;

	string s = Helper::aababc();
	stringstream ss;
	ss << s;
	EXPECT_TRUE(ss.str() == Helper::aababc());
}

template <typename CharT>
void InputStreamTest()
{
	using string = bksge::basic_string<CharT>;
	using stringstream = std::basic_stringstream<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		stringstream ss;
		ss << Helper::multi_line_str();

		string s;
		bksge::getline(ss, s);
		EXPECT_TRUE(s == Helper::abc());
		bksge::getline(ss, s);
		EXPECT_TRUE(s == Helper::bcd());
		bksge::getline(bksge::move(ss), s);
		EXPECT_TRUE(s == Helper::cd());
	}
	{
		stringstream ss;
		ss << Helper::csv_str();

		string s;
		bksge::getline(ss, s, Helper::comma_char());
		EXPECT_TRUE(s == Helper::abc());
		bksge::getline(ss, s, Helper::comma_char());
		EXPECT_TRUE(s == Helper::bcd());
		bksge::getline(bksge::move(ss), s, Helper::comma_char());
		EXPECT_TRUE(s == Helper::cd());
	}
}

template <typename CharT>
void GetLineTest()
{
	using string = bksge::basic_string<CharT>;
	using stringstream = std::basic_stringstream<CharT>;
	using Helper = StringTestHelper<CharT>;

	stringstream ss;
	ss << Helper::aababc();

	string s;
	ss >> s;
	EXPECT_TRUE(s == Helper::aababc());
}

GTEST_TEST(StringTest, stringstreamTest)
{
	OutputStreamTest<char>();
	InputStreamTest<char>();
	GetLineTest<char>();
}

}	// namespace stringstream_test

}	// namespace bksge_string_test
