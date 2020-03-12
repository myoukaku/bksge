/**
 *	@file	unit_test_fnd_sstream_stringstream.cpp
 *
 *	@brief	stringstream のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/sstream.hpp>
//#include <bksge/fnd/istream.hpp>
#include <istream>
#include <bksge/fnd/ios.hpp>
#include <vector>
//#include <bksge/fnd/string.hpp>
#include <string>
#include <bksge/fnd/memory/allocator.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace bksge_sstream_test
{

namespace stringstream_test
{

GTEST_TEST(StringStreamTest, CtorDefaultTest)
{
	{
		bksge::stringstream ss;
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == "");
	}
	{
		bksge::stringstream ss(std::ios_base::in);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == "");
	}
	{
		bksge::wstringstream ss;
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L"");
	}
	{
		bksge::wstringstream ss(std::ios_base::in);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L"");
	}
}

GTEST_TEST(StringStreamTest, CtorMoveTest)
{
	{
		bksge::stringstream ss0(" 123 456 ");
		bksge::stringstream ss(bksge::move(ss0));
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == "456 1236 ");
	}
	{
		bksge::wstringstream ss0(L" 123 456 ");
		bksge::wstringstream ss(bksge::move(ss0));
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == L"456 1236 ");
	}
	{
		std::vector<bksge::istringstream> vecis;
		vecis.push_back(bksge::istringstream());
		vecis.back().str("hub started at [00 6b 8b 45 69]");
		vecis.push_back(bksge::istringstream());
		vecis.back().str("hub started at [00 6b 8b 45 69]");
		for (bksge::size_t n = 0; n < vecis.size(); n++)
		{
			EXPECT_TRUE(vecis[n].str().size() == 31);
			vecis[n].seekg(0, std::ios_base::beg);
			EXPECT_TRUE(vecis[n].str().size() == 31);
		}
	}
}

namespace ctor_string_test
{

#if 0
template <typename T>
struct NoDefaultAllocator : bksge::allocator<T>
{
	template <typename U> struct rebind { using other = NoDefaultAllocator<U>; };
	NoDefaultAllocator(int id_) : id(id_) { }
	template <typename U> NoDefaultAllocator(const NoDefaultAllocator<U>& a) : id(a.id) { }
	int id;
};
#endif

GTEST_TEST(StringStreamTest, CtorStringTest)
{
	{
		bksge::stringstream ss(" 123 456 ");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == "456 1236 ");
	}
	{
		bksge::wstringstream ss(L" 123 456 ");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == L"456 1236 ");
	}
#if 0
	{ // This is https://bugs.llvm.org/show_bug.cgi?id=33727
		using S  = std::basic_string   <char, std::char_traits<char>, NoDefaultAllocator<char>>;
		using SB = std::basic_stringbuf<char, std::char_traits<char>, NoDefaultAllocator<char>>;

		S s(NoDefaultAllocator<char>(1));
		SB sb(s);
		//  This test is not required by the standard, but *where else* could it get the allocator?
		EXPECT_TRUE(sb.str().get_allocator() == s.get_allocator());
	}
#endif
}

}	// namespace ctor_string_test

GTEST_TEST(StringStreamTest, MoveAssignTest)
{
	{
		bksge::stringstream ss0(" 123 456 ");
		bksge::stringstream ss;
		ss = bksge::move(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == "456 1236 ");
	}
	{
		bksge::wstringstream ss0(L" 123 456 ");
		bksge::wstringstream ss;
		ss = bksge::move(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == L"456 1236 ");
	}
}

GTEST_TEST(StringStreamTest, SwapTest)
{
	{
		bksge::stringstream ss0(" 123 456 ");
		bksge::stringstream ss;
		ss.swap(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == "456 1236 ");
		ss0 << i << ' ' << 123;
		EXPECT_TRUE(ss0.str() == "456 123");
	}
	{
		bksge::wstringstream ss0(L" 123 456 ");
		bksge::wstringstream ss;
		ss.swap(ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == L"456 1236 ");
		ss0 << i << ' ' << 123;
		EXPECT_TRUE(ss0.str() == L"456 123");
	}
	{
		bksge::stringstream ss0(" 123 456 ");
		bksge::stringstream ss;
		swap(ss, ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == "456 1236 ");
		ss0 << i << ' ' << 123;
		EXPECT_TRUE(ss0.str() == "456 123");
	}
	{
		bksge::wstringstream ss0(L" 123 456 ");
		bksge::wstringstream ss;
		swap(ss, ss0);
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == L"456 1236 ");
		ss0 << i << ' ' << 123;
		EXPECT_TRUE(ss0.str() == L"456 123");
	}
}

GTEST_TEST(StringStreamTest, StrTest)
{
	{
		bksge::stringstream ss(" 123 456 ");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == " 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == "456 1236 ");
		ss.str("5466 89 ");
		ss >> i;
		EXPECT_TRUE(i == 5466);
		ss >> i;
		EXPECT_TRUE(i == 89);
		ss << i << ' ' << 321;
		EXPECT_TRUE(ss.str() == "89 3219 ");
	}
	{
		bksge::wstringstream ss(L" 123 456 ");
		EXPECT_TRUE(ss.rdbuf() != 0);
		EXPECT_TRUE(ss.good());
		EXPECT_TRUE(ss.str() == L" 123 456 ");
		int i = 0;
		ss >> i;
		EXPECT_TRUE(i == 123);
		ss >> i;
		EXPECT_TRUE(i == 456);
		ss << i << ' ' << 123;
		EXPECT_TRUE(ss.str() == L"456 1236 ");
		ss.str(L"5466 89 ");
		ss >> i;
		EXPECT_TRUE(i == 5466);
		ss >> i;
		EXPECT_TRUE(i == 89);
		ss << i << ' ' << 321;
		EXPECT_TRUE(ss.str() == L"89 3219 ");
	}
}

GTEST_TEST(StringStreamTest, TypesTest)
{
	static_assert((bksge::is_base_of<std::basic_iostream<char>, bksge::basic_stringstream<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringstream<char>::char_type, char>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringstream<char>::traits_type, std::char_traits<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringstream<char>::int_type, std::char_traits<char>::int_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringstream<char>::pos_type, std::char_traits<char>::pos_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringstream<char>::off_type, std::char_traits<char>::off_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringstream<char>::allocator_type, bksge::allocator<char>>::value), "");
}

}	// namespace stringstream_test

}	// namespace bksge_sstream_test
