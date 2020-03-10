/**
 *	@file	unit_test_fnd_sstream_ostringstream.cpp
 *
 *	@brief	ostringstream のテスト
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

namespace ostringstream_test
{

GTEST_TEST(OStringStreamTest, CtorDefaultTest)
{
	{
		bksge::ostringstream ss;
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == "");
	}
	{
		bksge::ostringstream ss(std::ios_base::out);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == "");
	}
	{
		bksge::wostringstream ss;
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L"");
	}
	{
		bksge::wostringstream ss(std::ios_base::out);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L"");
	}
}

GTEST_TEST(OStringStreamTest, CtorMoveTest)
{
	{
		bksge::ostringstream ss0(" 123 456");
		bksge::ostringstream ss(bksge::move(ss0));
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == "234 5676");
	}
	{
		bksge::wostringstream ss0(L" 123 456");
		bksge::wostringstream ss(bksge::move(ss0));
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == L"234 5676");
	}
}

GTEST_TEST(OStringStreamTest, CtorStringTest)
{
	{
		bksge::ostringstream ss(" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == "234 5676");
	}
	{
		bksge::ostringstream ss(" 123 456", std::ios_base::in);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == "234 5676");
	}
	{
		bksge::wostringstream ss(L" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == L"234 5676");
	}
	{
		bksge::wostringstream ss(L" 123 456", std::ios_base::in);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == L"234 5676");
	}
}

GTEST_TEST(OStringStreamTest, MoveAssignTest)
{
	{
		bksge::ostringstream ss0(" 123 456");
		bksge::ostringstream ss;
		ss = bksge::move(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == "234 5676");
	}
	{
		bksge::wostringstream ss0(L" 123 456");
		bksge::wostringstream ss;
		ss = bksge::move(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == L"234 5676");
	}
}

GTEST_TEST(OStringStreamTest, SwapTest)
{
	{
		bksge::ostringstream ss0(" 123 456");
		bksge::ostringstream ss;
		ss.swap(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == "234 5676");
		ss0 << i << ' ' << 567;
		EXPECT_TRUE(ss0.str() == "234 567");
	}
	{
		bksge::wostringstream ss0(L" 123 456");
		bksge::wostringstream ss;
		ss.swap(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == L"234 5676");
		ss0 << i << ' ' << 567;
		EXPECT_TRUE(ss0.str() == L"234 567");
	}
	{
		bksge::ostringstream ss0(" 123 456");
		bksge::ostringstream ss;
		swap(ss, ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == "234 5676");
		ss0 << i << ' ' << 567;
		EXPECT_TRUE(ss0.str() == "234 567");
	}
	{
		bksge::wostringstream ss0(L" 123 456");
		bksge::wostringstream ss;
		swap(ss, ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 234;
		ss << i << ' ' << 567;
		EXPECT_TRUE(ss.str() == L"234 5676");
		ss0 << i << ' ' << 567;
		EXPECT_TRUE(ss0.str() == L"234 567");
	}
}

GTEST_TEST(OStringStreamTest, StrTest)
{
	{
		bksge::ostringstream ss(" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456");
		int i = 0;
		ss << i;
		EXPECT_TRUE(ss.str() == "0123 456");
		ss << 456;
		EXPECT_TRUE(ss.str() == "0456 456");
		ss.str(" 789");
		EXPECT_TRUE(ss.str() == " 789");
		ss << "abc";
		EXPECT_TRUE(ss.str() == "abc9");
	}
	{
		bksge::wostringstream ss(L" 123 456");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456");
		int i = 0;
		ss << i;
		EXPECT_TRUE(ss.str() == L"0123 456");
		ss << 456;
		EXPECT_TRUE(ss.str() == L"0456 456");
		ss.str(L" 789");
		EXPECT_TRUE(ss.str() == L" 789");
		ss << L"abc";
		EXPECT_TRUE(ss.str() == L"abc9");
	}
}

GTEST_TEST(OStringStreamTest, TypesTest)
{
	static_assert((bksge::is_base_of<std::basic_ostream<char>, bksge::basic_ostringstream<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_ostringstream<char>::char_type, char>::value), "");
	static_assert((bksge::is_same<bksge::basic_ostringstream<char>::traits_type, std::char_traits<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_ostringstream<char>::int_type, std::char_traits<char>::int_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_ostringstream<char>::pos_type, std::char_traits<char>::pos_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_ostringstream<char>::off_type, std::char_traits<char>::off_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_ostringstream<char>::allocator_type, bksge::allocator<char>>::value), "");
}

}	// namespace ostringstream_test

}	// namespace bksge_sstream_test
