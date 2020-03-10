/**
 *	@file	unit_test_fnd_sstream_istringstream.cpp
 *
 *	@brief	istringstream のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/sstream.hpp>
//#include <bksge/fnd/string.hpp>
#include <string>
#include <bksge/fnd/ios.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/memory/allocator.hpp>
#include <gtest/gtest.h>

namespace bksge_sstream_test
{

namespace istringstream_test
{

GTEST_TEST(IStringStreamTest, CtorDefaultTest)
{
	{
		bksge::istringstream ss;
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == "");
	}
	{
		bksge::istringstream ss(std::ios_base::in);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == "");
	}
	{
		bksge::wistringstream ss;
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L"");
	}
	{
		bksge::wistringstream ss(std::ios_base::in);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L"");
	}
}

GTEST_TEST(IStringStreamTest, CtorMoveTest)
{
	{
		bksge::istringstream ss0(" 123 456");
		bksge::istringstream ss(bksge::move(ss0));
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
	{
		bksge::wistringstream ss0(L" 123 456");
		bksge::wistringstream ss(bksge::move(ss0));
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
}

GTEST_TEST(IStringStreamTest, CtorStringTest)
{
	{
		bksge::istringstream ss(" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
	{
		bksge::istringstream ss(" 123 456", std::ios_base::out);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
	{
		bksge::wistringstream ss(L" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
	{
		bksge::wistringstream ss(L" 123 456", std::ios_base::out);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
}

GTEST_TEST(IStringStreamTest, MoveAssignTest)
{
	{
		bksge::istringstream ss0(" 123 456");
		bksge::istringstream ss;
		ss = bksge::move(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
	{
		bksge::istringstream s1("Aaaaa Bbbbb Cccccccccc Dddddddddddddddddd");
		std::string s;
		s1 >> s;

		bksge::istringstream s2 = bksge::move(s1);
		s2 >> s;
		EXPECT_TRUE(s == "Bbbbb");

		bksge::istringstream s3;
		s3 = bksge::move(s2);
		s3 >> s;
		EXPECT_TRUE(s == "Cccccccccc");

		s1 = bksge::move(s3);
		s1 >> s;
		EXPECT_TRUE(s == "Dddddddddddddddddd");
	}
	{
		bksge::wistringstream ss0(L" 123 456");
		bksge::wistringstream ss;
		ss = bksge::move(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
	}
	{
		bksge::wistringstream s1(L"Aaaaa Bbbbb Cccccccccc Dddddddddddddddddd");
		std::wstring s;
		s1 >> s;

		bksge::wistringstream s2 = bksge::move(s1);
		s2 >> s;
		EXPECT_TRUE(s == L"Bbbbb");

		bksge::wistringstream s3;
		s3 = bksge::move(s2);
		s3 >> s;
		EXPECT_TRUE(s == L"Cccccccccc");

		s1 = bksge::move(s3);
		s1 >> s;
		EXPECT_TRUE(s == L"Dddddddddddddddddd");
	}
}

GTEST_TEST(IStringStreamTest, SwapTest)
{
	{
		bksge::istringstream ss0(" 123 456");
		bksge::istringstream ss(" 789 321");
		ss.swap(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss0 >> i;
		EXPECT_TRUE(i == 789);
		ss0 >> i;
		EXPECT_TRUE(i == 321);
	}
	{
		bksge::wistringstream ss0(L" 123 456");
		bksge::wistringstream ss(L" 789 321");
		ss.swap(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss0 >> i;
		EXPECT_TRUE(i == 789);
		ss0 >> i;
		EXPECT_TRUE(i == 321);
	}
	{
		bksge::istringstream ss0(" 123 456");
		bksge::istringstream ss(" 789 321");
		swap(ss, ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss0 >> i;
		EXPECT_TRUE(i == 789);
		ss0 >> i;
		EXPECT_TRUE(i == 321);
	}
	{
		bksge::wistringstream ss0(L" 123 456");
		bksge::wistringstream ss(L" 789 321");
		swap(ss, ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss0 >> i;
		EXPECT_TRUE(i == 789);
		ss0 >> i;
		EXPECT_TRUE(i == 321);
	}
}

GTEST_TEST(IStringStreamTest, StrTest)
{
	{
		bksge::istringstream ss(" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss.str(" 789");
		ss.clear();
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 789");
		ss >> i;
		EXPECT_TRUE(i == 789);
	}
	{
		bksge::wistringstream ss(L" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss.str(L" 789");
		ss.clear();
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 789");
		ss >> i;
		EXPECT_TRUE(i == 789);
	}
}

GTEST_TEST(IStringStreamTest, TypesTest)
{
	static_assert((bksge::is_base_of<std::basic_istream<char>, bksge::basic_istringstream<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_istringstream<char>::char_type, char>::value), "");
	static_assert((bksge::is_same<bksge::basic_istringstream<char>::traits_type, std::char_traits<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_istringstream<char>::int_type, std::char_traits<char>::int_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_istringstream<char>::pos_type, std::char_traits<char>::pos_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_istringstream<char>::off_type, std::char_traits<char>::off_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_istringstream<char>::allocator_type, bksge::allocator<char>>::value), "");
}

}	// namespace istringstream_test

}	// namespace bksge_sstream_test
