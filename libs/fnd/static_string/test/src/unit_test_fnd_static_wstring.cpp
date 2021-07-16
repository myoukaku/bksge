/**
 *	@file	unit_test_fnd_static_wstring.cpp
 *
 *	@brief	bksge::static_wstring のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/static_string/static_wstring.hpp>
#include <bksge/fnd/string_view/wstring_view.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <cstddef>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_static_wstring_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
c_str_test(bksge::static_wstring<N> const& s, wchar_t const* str)
{
	using traits_type = typename bksge::static_wstring<N>::traits_type;
	auto const str2 = s.c_str();
	VERIFY(traits_type::length(str2) == traits_type::length(str));
	VERIFY(traits_type::length(str2) == s.length());
	VERIFY(traits_type::compare(str2, str, s.length()) == 0);
	VERIFY(s.compare(str) == 0);
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorDefaultTest()
{
	{
		bksge::static_wstring<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));
	}
	{
		bksge::static_wstring<N> s{};
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));
	}
	{
		bksge::static_wstring<N> s={};
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCountCharTest()
{
	{
		bksge::static_wstring<N> s(0, L'a');
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));
	}
	{
		bksge::static_wstring<N> s(1, L'a');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"a"));
	}
	{
		bksge::static_wstring<N> s(4, L'c');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"cccc"));
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorOtherPosTest()
{
	{
		bksge::static_wstring<N1> const s1(L"hello");
		bksge::static_wstring<N2> const s2(s1, 1);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 4);
		VERIFY(s2.length()   == 4);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, L"ello"));
	}
	{
		bksge::static_wstring<N1> const s1(L"hello");
		bksge::static_wstring<N2> const s2{s1, 2};

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 3);
		VERIFY(s2.length()   == 3);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, L"llo"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorOtherPosCountTest()
{
	{
		bksge::static_wstring<N1> const s1(L"hello");
		bksge::static_wstring<N2> const s2(s1, 1, 3);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 3);
		VERIFY(s2.length()   == 3);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, L"ell"));
	}
	{
		bksge::static_wstring<N1> const s1(L"hello");
		bksge::static_wstring<N2> const s2{s1, 2, 2};

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 2);
		VERIFY(s2.length()   == 2);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, L"ll"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrCountTest()
{
	{
		bksge::static_wstring<N> s(L"abcde", 4);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abcd"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrTest()
{
	{
		bksge::static_wstring<N> s(L"abcde");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abcde"));
	}
	{
		bksge::static_wstring<N> s{L"hello world!"};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 12);
		VERIFY(s.length()   == 12);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"hello world!"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorIteratorTest()
{
	{
		wchar_t const buf[] = L"abcde";
		bksge::static_wstring<N> const s(buf, buf + 3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abc"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorCopyTest()
{
	{
		bksge::static_wstring<N1> const s1(L"hello world");
		bksge::static_wstring<N2> const s2(s1);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"hello world"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 11);
		VERIFY(s2.length()   == 11);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, L"hello world"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorMoveTest()
{
	{
		bksge::static_wstring<N1> s1(L"hello world");
		bksge::static_wstring<N2> const s2(std::move(s1));
		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 11);
		VERIFY(s2.length()   == 11);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, L"hello world"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorInitializerListTest()
{
	{
		bksge::static_wstring<N> s{'h', L'e', L'l', L'l', L'o'};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"hello"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringViewTest()
{
	{
		bksge::static_wstring<N> s(bksge::wstring_view{L"Hello World"});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"Hello World"));
	}
	{
		bksge::static_wstring<N> s(L"Hello World");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"Hello World"));
	}
	{
		bksge::static_wstring<N> s(bksge::wstring_view{L"Hello World"}, 2, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"llo W"));
	}
	{
		bksge::static_wstring<N> s(L"Hello World", 2, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"llo W"));
	}
	{
		bksge::static_wstring<N> s(bksge::wstring_view{L"Hello World"}, 2, 100);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 9);
		VERIFY(s.length()   == 9);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"llo World"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, CtorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCountCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCountCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCountCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosCountTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosCountTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosCountTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosCountTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosCountTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorOtherPosCountTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIteratorTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIteratorTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIteratorTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorCopyTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorCopyTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorCopyTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorCopyTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorCopyTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorCopyTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorMoveTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorMoveTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorMoveTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorMoveTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorMoveTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CtorMoveTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorInitializerListTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorInitializerListTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorInitializerListTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringTest()
{
	{
		bksge::static_wstring<N1> s1;
		VERIFY(s1.empty());

		bksge::static_wstring<N2> const s2(L"hello world");
		s1 = s2;
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"hello world"));

		bksge::static_wstring<N2> const s3(L"abc");
		s1.assign(s3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"abc"));

		bksge::static_wstring<N2> const s4(L"Hello World");
		s1.assign(s4, 3, 4);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 4);
		VERIFY(s1.length()   == 4);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"lo W"));

		s1.assign(s4, 3, 100);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"lo World"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringMoveTest()
{
	{
		bksge::static_wstring<N1> s1;
		VERIFY(s1.empty());

		bksge::static_wstring<N2> s2(L"hello world");
		s1 = std::move(s2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"hello world"));

		bksge::static_wstring<N2> s3(L"abc");
		s1.assign(std::move(s3));
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"abc"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharPtrTest()
{
	{
		bksge::static_wstring<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));

		s = L"hoge";
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"hoge"));

		s.assign(L"a");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"a"));

		s.assign(L"world", 3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"wor"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharTest()
{
	{
		bksge::static_wstring<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));

		s = 'A';
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"A"));

		s.assign(2, L'B');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 2);
		VERIFY(s.length()   == 2);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"BB"));

		s = 'C';
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"C"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignIteratorTest()
{
	{
		bksge::static_wstring<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));

		wchar_t buf[] = L"hello";

		s.assign(buf, buf+5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"hello"));

		s.assign(buf, buf+3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"hel"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignInitializerListTest()
{
	{
		bksge::static_wstring<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));

		s = {'h', L'e', L'l', L'l', L'o'};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"hello"));

		s.assign({'a', L'b', L'c', L'd'});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abcd"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringViewTest()
{
	{
		bksge::static_wstring<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L""));

		s = bksge::wstring_view{L"Hello World"};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"Hello World"));

		s.assign(bksge::wstring_view{L"abc"});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abc"));

		s.assign(bksge::wstring_view{L"Hello World"}, 1, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"ello "));

		s.assign(L"Hello World", 2, 6);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 6);
		VERIFY(s.length()   == 6);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"llo Wo"));

		s.assign(bksge::wstring_view{L"Hello World"}, 2, 100);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 9);
		VERIFY(s.length()   == 9);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"llo World"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, AssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringMoveTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringMoveTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringMoveTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringMoveTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringMoveTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AssignStringMoveTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIteratorTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIteratorTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIteratorTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignInitializerListTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignInitializerListTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignInitializerListTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringTest()
{
	{
		bksge::static_wstring<N1> s1;
		VERIFY(s1.empty());

		bksge::static_wstring<N2> const s2 = L"abc";
		s1 += s2;
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"abc"));

		bksge::static_wstring<N2> const s3 = L"hello";
		s1.append(s3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"abchello"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringPosTest()
{
	{
		bksge::static_wstring<N1> s1;
		VERIFY(s1.empty());

		bksge::static_wstring<N2> const s2 = L"abc";
		s1.append(s2, 1);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"bc"));

		bksge::static_wstring<N2> const s3 = L"hello";
		s1.append(s3, 2, 3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"bcllo"));

		bksge::static_wstring<N2> const s4 = L"world";
		s1.append(s4, 1, 10);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 9);
		VERIFY(s1.length()   == 9);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, L"bclloorld"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharPtrTest()
{
	{
		bksge::static_wstring<N> s1;
		VERIFY(s1.empty());

		s1 += L"hello";
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"hello"));

		s1.append(L" world");
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"hello world"));

		s1.append(L"ABCDE", 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 13);
		VERIFY(s1.length()   == 13);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"hello worldAB"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharTest()
{
	{
		bksge::static_wstring<N> s1;
		VERIFY(s1.empty());

		s1 += 'A';
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"A"));

		s1.append(3, L'B');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 4);
		VERIFY(s1.length()   == 4);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"ABBB"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendInitializerListTest()
{
	{
		bksge::static_wstring<N> s1;
		VERIFY(s1.empty());

		s1 += { 'A', L'B', L'C' };
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"ABC"));

		s1.append({ 'h', L'e', L'l', L'l', L'o' });
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"ABChello"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendIteratorTest()
{
	{
		bksge::static_wstring<N> s1;
		VERIFY(s1.empty());

		wchar_t buf[] = L"hello";

		s1.append(buf, buf+5);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"hello"));

		s1.append(buf+1, buf+3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 7);
		VERIFY(s1.length()   == 7);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"helloel"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringViewTest()
{
	{
		bksge::static_wstring<N> s1;
		VERIFY(s1.empty());

		s1 += bksge::wstring_view{L"Hel"};
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"Hel"));

		s1.append(bksge::wstring_view{L"lo"});
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"Hello"));

		s1.append(bksge::wstring_view{L"abcde"}, 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"Hellocde"));

		s1.append(bksge::wstring_view{L"ABCDE"}, 1, 3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"HellocdeBCD"));

		s1.append(L"ABCDE", 2, 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 13);
		VERIFY(s1.length()   == 13);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"HellocdeBCDCD"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, AppendTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringPosTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringPosTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringPosTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringPosTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringPosTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AppendStringPosTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendInitializerListTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendInitializerListTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendInitializerListTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendIteratorTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendIteratorTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendIteratorTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AppendStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringTest()
{
	{
		bksge::static_wstring<N1> s1 = L"aaa";
		bksge::static_wstring<N2> s2 = L"bbb";
		s1.insert(2, s2);
		VERIFY(c_str_test(s1, L"aabbba"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringPosTest()
{
	{
		bksge::static_wstring<N1> s1 = L"aaa";
		bksge::static_wstring<N2> s2 = L"12345";
		s1.insert(2, s2, 2, 3);
		VERIFY(c_str_test(s1, L"aa345a"));
	}
	{
		bksge::static_wstring<N1> s1 = L"aaa";
		bksge::static_wstring<N2> s2 = L"12345";
		s1.insert(3, s2, 1);
		VERIFY(c_str_test(s1, L"aaa2345"));
	}
	{
		bksge::static_wstring<N1> s1 = L"aaa";
		bksge::static_wstring<N2> s2 = L"12345";
		s1.insert(1, s2, 1, 100);
		VERIFY(c_str_test(s1, L"a2345aa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharPtrCountTest()
{
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(2, L"12345", 2);
		VERIFY(c_str_test(s1, L"aa12a"));
	}
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(2, L"12345", 0);
		VERIFY(c_str_test(s1, L"aaa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharPtrTest()
{
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(1, L"12345");
		VERIFY(c_str_test(s1, L"a12345aa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharTest()
{
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(2, 3, L'b');
		VERIFY(c_str_test(s1, L"aabbba"));
	}
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(2, 0, L'b');
		VERIFY(c_str_test(s1, L"aaa"));
	}

	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(s1.begin(), L'b');
		VERIFY(c_str_test(s1, L"baaa"));
	}
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(s1.end(), L'c');
		VERIFY(c_str_test(s1, L"aaac"));
	}

	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(s1.begin(), 2, L'b');
		VERIFY(c_str_test(s1, L"bbaaa"));
	}
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(s1.end(), 3, L'c');
		VERIFY(c_str_test(s1, L"aaaccc"));
	}
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(s1.end(), 0, L'c');
		VERIFY(c_str_test(s1, L"aaa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertIteratorTest()
{
	{
		bksge::static_wstring<N> s1 = L"aaa";
		wchar_t buf[] = L"xyz";
		s1.insert(s1.begin(), buf, buf+3);
		VERIFY(c_str_test(s1, L"xyzaaa"));
	}
	{
		bksge::static_wstring<N> s1 = L"aaa";
		wchar_t buf[] = L"xyz";
		s1.insert(s1.end(), buf, buf+3);
		VERIFY(c_str_test(s1, L"aaaxyz"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertInitializerListTest()
{
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(s1.begin()+1, {'1', L'2', L'3', L'4', L'5'});
		VERIFY(c_str_test(s1, L"a12345aa"));
	}
	{
		bksge::static_wstring<N> s1 = L"aaa";
		s1.insert(s1.end(), {'b', L'c'});
		VERIFY(c_str_test(s1, L"aaabc"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringViewTest()
{
	{
		bksge::static_wstring<N> s1 = L"abcde";
		s1.insert(0, bksge::wstring_view{L"xyz"});
		VERIFY(c_str_test(s1, L"xyzabcde"));
	}
	{
		bksge::static_wstring<N> s1 = L"abcde";
		s1.insert(1, bksge::wstring_view{L"12345"}, 1);
		VERIFY(c_str_test(s1, L"a2345bcde"));
	}
	{
		bksge::static_wstring<N> s1 = L"abcde";
		s1.insert(2, bksge::wstring_view{L"12345"}, 2, 3);
		VERIFY(c_str_test(s1, L"ab345cde"));
	}
	{
		bksge::static_wstring<N> s1 = L"abcde";
		s1.insert(2, bksge::wstring_view{L"12345"}, 2, 4);
		VERIFY(c_str_test(s1, L"ab345cde"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, InsertTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringPosTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringPosTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringPosTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringPosTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringPosTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((InsertStringPosTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharPtrCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharPtrCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharPtrCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertIteratorTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertIteratorTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertIteratorTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertInitializerListTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertInitializerListTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertInitializerListTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InsertStringViewTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ErasePosCountTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.erase(1, 2);
		VERIFY(c_str_test(s1, L"145"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.erase(2);
		VERIFY(c_str_test(s1, L"12"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.erase();
		VERIFY(c_str_test(s1, L""));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EraseIteratorTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.erase(s1.begin());
		VERIFY(c_str_test(s1, L"2345"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.erase(s1.begin()+1);
		VERIFY(c_str_test(s1, L"1345"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EraseFirstLastTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.erase(s1.begin(), s1.begin()+2);
		VERIFY(c_str_test(s1, L"345"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.erase(s1.begin()+2, s1.end());
		VERIFY(c_str_test(s1, L"12"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, EraseTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ErasePosCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ErasePosCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ErasePosCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EraseIteratorTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EraseIteratorTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EraseIteratorTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EraseFirstLastTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EraseFirstLastTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EraseFirstLastTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringTest()
{
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"abcde";
		s1.replace(1, 2, s2);
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"abcde";
		s1.replace(2, 100, s2);
		VERIFY(c_str_test(s1, L"12abcde"));
	}
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"a";
		s1.replace(1, 2, s2);
		VERIFY(c_str_test(s1, L"1a45"));
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringPosCountTest()
{
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"abcde";
		s1.replace(1, 2, s2, 2, 3);
		VERIFY(c_str_test(s1, L"1cde45"));
	}
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"abcde";
		s1.replace(2, 1, s2, 1);
		VERIFY(c_str_test(s1, L"12bcde45"));
	}
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"abcde";
		s1.replace(1, 2, s2, 2, 1);
		VERIFY(c_str_test(s1, L"1c45"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrCountTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 2, L"abcde", 3);
		VERIFY(c_str_test(s1, L"1abc45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(2, 100, L"abcde", 2);
		VERIFY(c_str_test(s1, L"12ab"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 2, L"abcde");
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(2, 100, L"abcde");
		VERIFY(c_str_test(s1, L"12abcde"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 3, L"z");
		VERIFY(c_str_test(s1, L"1z5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCountCharTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 2, 3, L'x');
		VERIFY(c_str_test(s1, L"1xxx45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(2, 100, 4, L'y');
		VERIFY(c_str_test(s1, L"12yyyy"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 3, 1, L'z');
		VERIFY(c_str_test(s1, L"1z5"));
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorStringTest()
{
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2);
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"abcde";
		s1.replace(s1.begin(), s1.end(), s2);
		VERIFY(c_str_test(s1, L"abcde"));
	}
	{
		bksge::static_wstring<N1> s1 = L"12345";
		bksge::static_wstring<N2> s2 = L"xy";
		s1.replace(s1.begin() + 1, s1.begin() + 4, s2);
		VERIFY(c_str_test(s1, L"1xy5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCharPtrCountTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, L"abcde", 3);
		VERIFY(c_str_test(s1, L"1abc45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin(), s1.end(), L"abcde", 2);
		VERIFY(c_str_test(s1, L"ab"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCharPtrTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, L"abcde");
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin(), s1.end(), L"abcde");
		VERIFY(c_str_test(s1, L"abcde"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 4, L"xy");
		VERIFY(c_str_test(s1, L"1xy5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCountCharTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, 3, L'x');
		VERIFY(c_str_test(s1, L"1xxx45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin(), s1.end(), 2, L'y');
		VERIFY(c_str_test(s1, L"yy"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorIteratorTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		bksge::static_wstring<N> s2 = L"abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2.begin(), s2.end());
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		bksge::static_wstring<N> s2 = L"abcde";
		s1.replace(s1.begin(), s1.end(), s2.begin(), s2.end());
		VERIFY(c_str_test(s1, L"abcde"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		bksge::static_wstring<N> s2 = L"abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2.begin(), s2.begin()+1);
		VERIFY(c_str_test(s1, L"1a45"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorInitializerListTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, {'a', L'b', L'c', L'd', L'e'});
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin(), s1.end(), {'a', L'b', L'c', L'd'});
		VERIFY(c_str_test(s1, L"abcd"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 2, bksge::wstring_view{L"abcde"});
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 100, bksge::wstring_view{L"abcde"});
		VERIFY(c_str_test(s1, L"1abcde"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 3, bksge::wstring_view{L"A"});
		VERIFY(c_str_test(s1, L"1A5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewPosCountTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 2, bksge::wstring_view{L"XXXabcdeYYY"}, 3, 5);
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(2, 2, bksge::wstring_view{L"XXXabcdeYYY"}, 3);
		VERIFY(c_str_test(s1, L"12abcdeYYY5"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(2, 1, L"abcde", 2, 3);
		VERIFY(c_str_test(s1, L"12cde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(1, 3, L"abcde", 2, 1);
		VERIFY(c_str_test(s1, L"1c5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorStringViewTest()
{
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, bksge::wstring_view{L"abcde"});
		VERIFY(c_str_test(s1, L"1abcde45"));
	}
	{
		bksge::static_wstring<N> s1 = L"12345";
		s1.replace(s1.begin(), s1.end(), bksge::wstring_view{L"abc"});
		VERIFY(c_str_test(s1, L"abc"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, ReplaceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringPosCountTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringPosCountTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringPosCountTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringPosCountTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringPosCountTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplacePosCountStringPosCountTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCharPtrCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCharPtrCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCharPtrCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCountCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCountCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountCountCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplaceIteratorStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplaceIteratorStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplaceIteratorStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplaceIteratorStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplaceIteratorStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ReplaceIteratorStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCharPtrCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCharPtrCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCharPtrCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCountCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCountCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorCountCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorIteratorTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorIteratorTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorIteratorTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorInitializerListTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorInitializerListTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorInitializerListTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountStringViewTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountStringViewPosCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountStringViewPosCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplacePosCountStringViewPosCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIteratorStringViewTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CopyTest()
{
	bksge::static_wstring<N> const s = L"hello";
	using traits_type = typename bksge::static_wstring<N>::traits_type;
	{
		wchar_t result[5 + 1] ={};
		auto ret = s.copy(result, 5);
		VERIFY(traits_type::compare(result, L"hello", 5) == 0);
		VERIFY(ret == 5);
	}
	{
		wchar_t result[3 + 1] ={};
		auto ret = s.copy(result, 3);
		VERIFY(traits_type::compare(result, L"hel", 3) == 0);
		VERIFY(ret == 3);
	}
	{
		wchar_t result[3 + 1] ={};
		auto ret = s.copy(result, 3, 2);
		VERIFY(traits_type::compare(result, L"llo", 3) == 0);
		VERIFY(ret == 3);
	}
	{
		wchar_t result[5 + 1] ={};
		auto ret = s.copy(result, 100, 1);
		VERIFY(traits_type::compare(result, L"ello", 4) == 0);
		VERIFY(ret == 4);
	}
	return true;
}

GTEST_TEST(StaticWStringTest, CopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool PushBackTest()
{
	{
		bksge::static_wstring<N> s1;
		VERIFY(s1.empty());

		s1.push_back('a');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"a"));

		s1.push_back('b');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"ab"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, PushBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool PopBackTest()
{
	{
		bksge::static_wstring<N> s1 = L"abc";
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"abc"));

		s1.pop_back();
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"ab"));

		s1.pop_back();
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, L"a"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, PopBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool BeginEndTest()
{
	{
		bksge::static_wstring<N> s = L"abc";
		auto it = s.begin();
		VERIFY(*it == 'a');
		*it++ = 'X';
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.end());
		++it;
		VERIFY(it == s.end());
		VERIFY(c_str_test(s, L"Xbc"));
	}
	{
		bksge::static_wstring<N> const s = L"abc";
		auto it = s.begin();
		VERIFY(*it++ == 'a');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.end());
		++it;
		VERIFY(it == s.end());
		VERIFY(c_str_test(s, L"abc"));
	}
	{
		bksge::static_wstring<N> s = L"abc";
		auto it = s.cbegin();
		VERIFY(*it++ == 'a');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.cend());
		++it;
		VERIFY(it == s.cend());
		VERIFY(c_str_test(s, L"abc"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, BeginEndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RBeginREndTest()
{
	{
		bksge::static_wstring<N> s = L"abc";
		auto it = s.rbegin();
		VERIFY(*it == 'c');
		*it++ = 'X';
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.rend());
		++it;
		VERIFY(it == s.rend());
		VERIFY(c_str_test(s, L"abX"));
	}
	{
		bksge::static_wstring<N> const s = L"abc";
		auto it = s.rbegin();
		VERIFY(*it++ == 'c');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.rend());
		++it;
		VERIFY(it == s.rend());
		VERIFY(c_str_test(s, L"abc"));
	}
	{
		bksge::static_wstring<N> s = L"abc";
		auto it = s.crbegin();
		VERIFY(*it++ == 'c');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.crend());
		++it;
		VERIFY(it == s.crend());
		VERIFY(c_str_test(s, L"abc"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, RBeginREndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ResizeTest()
{
	{
		bksge::static_wstring<N> s = L"abc";
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abc"));
		s.resize(5, L'X');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abcXX"));
		s.resize(4, L'Y');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"abcX"));
		s.resize(6);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 6);
		VERIFY(s.length()   == 6);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		//VERIFY(s.compare(L"abcX") == 0);
		s.resize(2);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 2);
		VERIFY(s.length()   == 2);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, L"ab"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, ResizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReserveTest()
{
	{
		bksge::static_wstring<N> s = L"abc";
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		s.reserve(10);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		s.reserve();
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		s.shrink_to_fit();
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
	}

	return true;
}

GTEST_TEST(StaticWStringTest, ReserveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ClearTest()
{
	{
		bksge::static_wstring<N> s = L"abc";
		VERIFY(!s.empty());
		VERIFY(c_str_test(s, L"abc"));

		s.clear();
		VERIFY(s.empty());
		VERIFY(c_str_test(s, L""));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, ClearTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool BraceTest()
{
	{
		bksge::static_wstring<N> const s = L"abc";
		VERIFY(s[0] == 'a');
		VERIFY(s[1] == 'b');
		VERIFY(s[2] == 'c');
	}
	{
		bksge::static_wstring<N> s = L"abc";
		s[1] = 'Z';
		VERIFY(c_str_test(s, L"aZc"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, BraceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	{
		bksge::static_wstring<N> const s = L"abc";
		VERIFY(s.at(0) == 'a');
		VERIFY(s.at(1) == 'b');
		VERIFY(s.at(2) == 'c');
	}
	{
		bksge::static_wstring<N> s = L"abc";
		s.at(1) = 'Z';
		VERIFY(c_str_test(s, L"aZc"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FrontBackTest()
{
	{
		bksge::static_wstring<N> const s = L"abc";
		VERIFY(s.front() == 'a');
		VERIFY(s.back()  == 'c');
	}
	{
		bksge::static_wstring<N> s = L"abc";
		s.front() = 'X';
		s.back()  = 'Y';
		VERIFY(c_str_test(s, L"XbY"));
	}

	return true;
}

GTEST_TEST(StaticWStringTest, FrontBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CompareStringTest()
{
	{
		bksge::static_wstring<N1> const s1 = L"12345";
		bksge::static_wstring<N2> const s2 = L"12345";
		bksge::static_wstring<N2> const s3 = L"123456";
		bksge::static_wstring<N2> const s4 = L"1234";
		bksge::static_wstring<N2> const s5 = L"12346";
		bksge::static_wstring<N2> const s6 = L"12344";

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) < 0);
		VERIFY(s1.compare(s4) > 0);
		VERIFY(s1.compare(s5) < 0);
		VERIFY(s1.compare(s6) > 0);
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringTest()
{
	{
		bksge::static_wstring<N1> const s1 = L"123456";
		bksge::static_wstring<N2> const s2 = L"12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", L"12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringPosCountTest()
{
	{
		bksge::static_wstring<N1> const s1 = L"12345";
		bksge::static_wstring<N2> const s2 = L"123456";

		VERIFY(s1.compare(0, 5, s2, 0, 5) == 0);	// "12345", L"12345"
		VERIFY(s1.compare(0, 6, s2, 0)    < 0);		// "12345", L"123456"
		VERIFY(s1.compare(0, 4, s2, 0, 5) < 0);		// "1234",  "12345"
		VERIFY(s1.compare(0, 4, s2, 0, 3) > 0);		// "1234",  "123"
		VERIFY(s1.compare(1, 3, s2, 1, 3) == 0);	// "234",   "234"
		VERIFY(s1.compare(1, 3, s2, 0, 3) > 0);		// "234",   "123"
		VERIFY(s1.compare(1, 4, s2, 2, 3) < 0);		// "2345",  "345"
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CompareCharPtrTest()
{
	{
		bksge::static_wstring<N> const s1 = L"12345";
		wchar_t const* s2 = L"12345";
		wchar_t const* s3 = L"123456";
		wchar_t const* s4 = L"1234";
		wchar_t const* s5 = L"12346";
		wchar_t const* s6 = L"12344";

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) < 0);
		VERIFY(s1.compare(s4) > 0);
		VERIFY(s1.compare(s5) < 0);
		VERIFY(s1.compare(s6) > 0);
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountCharPtrTest()
{
	{
		bksge::static_wstring<N> const s1 = L"123456";
		wchar_t const* s2 = L"12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", L"12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountCharPtrCountTest()
{
	{
		bksge::static_wstring<N> const s1 = L"12345";
		wchar_t const* s2 = L"123456";

		VERIFY(s1.compare(0, 5, s2, 5) == 0);	// "12345", L"12345"
		VERIFY(s1.compare(0, 5, s2, 9) < 0);	// "12345", L"123456"
		VERIFY(s1.compare(1, 4, s2, 9) > 0);	// "2345",  "123456"
		VERIFY(s1.compare(0, 4, s2, 5) < 0);	// "1234",  "12345"
		VERIFY(s1.compare(0, 4, s2, 3) > 0);	// "1234",  "123"
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CompareStringViewTest()
{
	{
		bksge::static_wstring<N> const s1 = L"12345";
		bksge::wstring_view const s2 = L"12345";
		bksge::wstring_view const s3 = L"123456";
		bksge::wstring_view const s4 = L"1234";
		bksge::wstring_view const s5 = L"12346";
		bksge::wstring_view const s6 = L"12344";

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) < 0);
		VERIFY(s1.compare(s4) > 0);
		VERIFY(s1.compare(s5) < 0);
		VERIFY(s1.compare(s6) > 0);
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringViewTest()
{
	{
		bksge::static_wstring<N> const s1 = L"123456";
		bksge::wstring_view const s2 = L"12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", L"12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringViewPosCountTest()
{
	{
		bksge::static_wstring<N> const s1 = L"12345";
		bksge::wstring_view const s2 = L"123456";

		VERIFY(s1.compare(0, 5, s2, 0, 5) == 0);	// "12345", L"12345"
		VERIFY(s1.compare(0, 6, s2, 0)    < 0);		// "12345", L"123456"
		VERIFY(s1.compare(0, 4, s2, 0, 5) < 0);		// "1234",  "12345"
		VERIFY(s1.compare(0, 4, s2, 0, 3) > 0);		// "1234",  "123"
		VERIFY(s1.compare(1, 3, s2, 1, 3) == 0);	// "234",   "234"
		VERIFY(s1.compare(1, 3, s2, 0, 3) > 0);		// "234",   "123"
		VERIFY(s1.compare(1, 4, s2, 2, 3) < 0);		// "2345",  "345"
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CompareOperatorStringTest()
{
	{
		bksge::static_wstring<N1> const s1 = L"abc";
		bksge::static_wstring<N2> const s2 = L"abc";
		bksge::static_wstring<N2> const s3 = L"abcd";
		bksge::static_wstring<N2> const s4 = L"ab";
		bksge::static_wstring<N2> const s5 = L"abe";
		bksge::static_wstring<N2> const s6 = L"aba";

		VERIFY((s1 == s1) == true);
		VERIFY((s1 == s2) == true);
		VERIFY((s1 == s3) == false);
		VERIFY((s1 == s4) == false);
		VERIFY((s1 == s5) == false);
		VERIFY((s1 == s6) == false);

		VERIFY((s1 != s1) == false);
		VERIFY((s1 != s2) == false);
		VERIFY((s1 != s3) == true);
		VERIFY((s1 != s4) == true);
		VERIFY((s1 != s5) == true);
		VERIFY((s1 != s6) == true);

		VERIFY((s1 <  s1) == false);
		VERIFY((s1 <  s2) == false);
		VERIFY((s1 <  s3) == true);
		VERIFY((s1 <  s4) == false);
		VERIFY((s1 <  s5) == true);
		VERIFY((s1 <  s6) == false);

		VERIFY((s1 >  s1) == false);
		VERIFY((s1 >  s2) == false);
		VERIFY((s1 >  s3) == false);
		VERIFY((s1 >  s4) == true);
		VERIFY((s1 >  s5) == false);
		VERIFY((s1 >  s6) == true);

		VERIFY((s1 <= s1) == true);
		VERIFY((s1 <= s2) == true);
		VERIFY((s1 <= s3) == true);
		VERIFY((s1 <= s4) == false);
		VERIFY((s1 <= s5) == true);
		VERIFY((s1 <= s6) == false);

		VERIFY((s1 >= s1) == true);
		VERIFY((s1 >= s2) == true);
		VERIFY((s1 >= s3) == false);
		VERIFY((s1 >= s4) == true);
		VERIFY((s1 >= s5) == false);
		VERIFY((s1 >= s6) == true);
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CompareOperatorCharPtrTest()
{
	{
		bksge::static_wstring<N> const s1 = L"abc";
		wchar_t const* s2 = L"abc";
		wchar_t const* s3 = L"abcd";
		wchar_t const* s4 = L"ab";
		wchar_t const* s5 = L"abe";
		wchar_t const* s6 = L"aba";

		VERIFY((s1 == s2) == true);
		VERIFY((s1 == s3) == false);
		VERIFY((s1 == s4) == false);
		VERIFY((s1 == s5) == false);
		VERIFY((s1 == s6) == false);

		VERIFY((s1 != s2) == false);
		VERIFY((s1 != s3) == true);
		VERIFY((s1 != s4) == true);
		VERIFY((s1 != s5) == true);
		VERIFY((s1 != s6) == true);

		VERIFY((s1 <  s2) == false);
		VERIFY((s1 <  s3) == true);
		VERIFY((s1 <  s4) == false);
		VERIFY((s1 <  s5) == true);
		VERIFY((s1 <  s6) == false);

		VERIFY((s1 >  s2) == false);
		VERIFY((s1 >  s3) == false);
		VERIFY((s1 >  s4) == true);
		VERIFY((s1 >  s5) == false);
		VERIFY((s1 >  s6) == true);

		VERIFY((s1 <= s2) == true);
		VERIFY((s1 <= s3) == true);
		VERIFY((s1 <= s4) == false);
		VERIFY((s1 <= s5) == true);
		VERIFY((s1 <= s6) == false);

		VERIFY((s1 >= s2) == true);
		VERIFY((s1 >= s3) == false);
		VERIFY((s1 >= s4) == true);
		VERIFY((s1 >= s5) == false);
		VERIFY((s1 >= s6) == true);

		VERIFY((s2 == s1) == true);
		VERIFY((s3 == s1) == false);
		VERIFY((s4 == s1) == false);
		VERIFY((s5 == s1) == false);
		VERIFY((s6 == s1) == false);

		VERIFY((s2 != s1) == false);
		VERIFY((s3 != s1) == true);
		VERIFY((s4 != s1) == true);
		VERIFY((s5 != s1) == true);
		VERIFY((s6 != s1) == true);

		VERIFY((s2 <  s1) == false);
		VERIFY((s3 <  s1) == false);
		VERIFY((s4 <  s1) == true);
		VERIFY((s5 <  s1) == false);
		VERIFY((s6 <  s1) == true);

		VERIFY((s2 >  s1) == false);
		VERIFY((s3 >  s1) == true);
		VERIFY((s4 >  s1) == false);
		VERIFY((s5 >  s1) == true);
		VERIFY((s6 >  s1) == false);

		VERIFY((s2 <= s1) == true);
		VERIFY((s3 <= s1) == false);
		VERIFY((s4 <= s1) == true);
		VERIFY((s5 <= s1) == false);
		VERIFY((s6 <= s1) == true);

		VERIFY((s2 >= s1) == true);
		VERIFY((s3 >= s1) == true);
		VERIFY((s4 >= s1) == false);
		VERIFY((s5 >= s1) == true);
		VERIFY((s6 >= s1) == false);
	}
	return true;
}

GTEST_TEST(StaticWStringTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringPosCountTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringPosCountTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringPosCountTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringPosCountTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringPosCountTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ComparePosCountStringPosCountTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountCharPtrCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountCharPtrCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountCharPtrCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareStringViewTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountStringViewTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountStringViewPosCountTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountStringViewPosCountTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparePosCountStringViewPosCountTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareOperatorStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareOperatorStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareOperatorStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareOperatorStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareOperatorStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareOperatorStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareOperatorCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareOperatorCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareOperatorCharPtrTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindStringTest()
{
	bksge::static_wstring<N1> const s1 = L"ab abc abcd";

	VERIFY(s1.find(bksge::static_wstring<N2>{L"a"}) == 0);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"ab"}) == 0);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"abc"}) == 3);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"abcd"}) == 7);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"abcde"}) == bksge::static_wstring<N1>::npos);

	VERIFY(s1.find(bksge::static_wstring<N2>{L"a"}, 1) == 3);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"ab"}, 1) == 3);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"abc"}, 1) == 3);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"abcd"}, 1) == 7);
	VERIFY(s1.find(bksge::static_wstring<N2>{L"abcde"}, 1) == bksge::static_wstring<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindCharPtrTest()
{
	bksge::static_wstring<N> const s1 = L"ab abc abcd";

	VERIFY(s1.find(L"a") == 0);
	VERIFY(s1.find(L"ab") == 0);
	VERIFY(s1.find(L"abc") == 3);
	VERIFY(s1.find(L"abcd") == 7);
	VERIFY(s1.find(L"abcde") == bksge::static_wstring<N>::npos);

	VERIFY(s1.find(L"a", 1) == 3);
	VERIFY(s1.find(L"ab", 1) == 3);
	VERIFY(s1.find(L"abc", 1) == 3);
	VERIFY(s1.find(L"abcd", 1) == 7);
	VERIFY(s1.find(L"abcde", 1) == bksge::static_wstring<N>::npos);

	VERIFY(s1.find(L"abcde", 1, 1) == 3);
	VERIFY(s1.find(L"abcde", 1, 2) == 3);
	VERIFY(s1.find(L"abcde", 1, 3) == 3);
	VERIFY(s1.find(L"abcde", 1, 4) == 7);
	VERIFY(s1.find(L"abcde", 1, 5) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindCharTest()
{
	bksge::static_wstring<N> const s1 = L"ab abc abcd";

	VERIFY(s1.find('a') == 0);
	VERIFY(s1.find('b') == 1);
	VERIFY(s1.find('c') == 5);
	VERIFY(s1.find('d') == 10);
	VERIFY(s1.find('e') == bksge::static_wstring<N>::npos);

	VERIFY(s1.find('a', 1) == 3);
	VERIFY(s1.find('a', 4) == 7);
	VERIFY(s1.find('a', 8) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindStringViewTest()
{
	bksge::static_wstring<N> const s1 = L"ab abc abcd";

	VERIFY(s1.find(bksge::wstring_view{L"a"}) == 0);
	VERIFY(s1.find(bksge::wstring_view{L"ab"}) == 0);
	VERIFY(s1.find(bksge::wstring_view{L"abc"}) == 3);
	VERIFY(s1.find(bksge::wstring_view{L"abcd"}) == 7);
	VERIFY(s1.find(bksge::wstring_view{L"abcde"}) == bksge::static_wstring<N>::npos);

	VERIFY(s1.find(bksge::wstring_view{L"a"}, 1) == 3);
	VERIFY(s1.find(bksge::wstring_view{L"ab"}, 1) == 3);
	VERIFY(s1.find(bksge::wstring_view{L"abc"}, 1) == 3);
	VERIFY(s1.find(bksge::wstring_view{L"abcd"}, 1) == 7);
	VERIFY(s1.find(bksge::wstring_view{L"abcde"}, 1) == bksge::static_wstring<N>::npos);

	return true;
}

GTEST_TEST(StaticWStringTest, FindTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool RFindStringTest()
{
	bksge::static_wstring<N1> const s1 = L"abcd abc ab";

	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"a"}) == 9);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"ab"}) == 9);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abc"}) == 5);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abcd"}) == 0);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abcde"}) == bksge::static_wstring<N1>::npos);

	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"a"}, 10) == 9);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"ab"}, 10) == 9);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abc"}, 10) == 5);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abcd"}, 10) == 0);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abcde"}, 10) == bksge::static_wstring<N1>::npos);

	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"a"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"ab"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abc"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abcd"}, 8) == 0);
	VERIFY(s1.rfind(bksge::static_wstring<N2>{L"abcde"}, 8) == bksge::static_wstring<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindCharPtrTest()
{
	bksge::static_wstring<N> const s1 = L"abcd abc ab";

	VERIFY(s1.rfind(L"a") == 9);
	VERIFY(s1.rfind(L"ab") == 9);
	VERIFY(s1.rfind(L"abc") == 5);
	VERIFY(s1.rfind(L"abcd") == 0);
	VERIFY(s1.rfind(L"abcde") == bksge::static_wstring<N>::npos);

	VERIFY(s1.rfind(L"a", 6) == 5);
	VERIFY(s1.rfind(L"ab", 6) == 5);
	VERIFY(s1.rfind(L"abc", 6) == 5);
	VERIFY(s1.rfind(L"abcd", 6) == 0);
	VERIFY(s1.rfind(L"abcde", 6) == bksge::static_wstring<N>::npos);

	VERIFY(s1.rfind(L"abcde", 7, 1) == 5);
	VERIFY(s1.rfind(L"abcde", 7, 2) == 5);
	VERIFY(s1.rfind(L"abcde", 7, 3) == 5);
	VERIFY(s1.rfind(L"abcde", 7, 4) == 0);
	VERIFY(s1.rfind(L"abcde", 7, 5) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindCharTest()
{
	bksge::static_wstring<N> const s1 = L"abcd abc ab";

	VERIFY(s1.rfind('a') == 9);
	VERIFY(s1.rfind('b') == 10);
	VERIFY(s1.rfind('c') == 7);
	VERIFY(s1.rfind('d') == 3);
	VERIFY(s1.rfind('e') == bksge::static_wstring<N>::npos);

	VERIFY(s1.rfind('b', 10) == 10);
	VERIFY(s1.rfind('b', 9) == 6);
	VERIFY(s1.rfind('b', 5) == 1);
	VERIFY(s1.rfind('b', 0) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindStringViewTest()
{
	bksge::static_wstring<N> const s1 = L"abcd abc ab";

	VERIFY(s1.rfind(bksge::wstring_view{L"a"}) == 9);
	VERIFY(s1.rfind(bksge::wstring_view{L"ab"}) == 9);
	VERIFY(s1.rfind(bksge::wstring_view{L"abc"}) == 5);
	VERIFY(s1.rfind(bksge::wstring_view{L"abcd"}) == 0);
	VERIFY(s1.rfind(bksge::wstring_view{L"abcde"}) == bksge::static_wstring<N>::npos);

	VERIFY(s1.rfind(bksge::wstring_view{L"a"}, 10) == 9);
	VERIFY(s1.rfind(bksge::wstring_view{L"ab"}, 10) == 9);
	VERIFY(s1.rfind(bksge::wstring_view{L"abc"}, 10) == 5);
	VERIFY(s1.rfind(bksge::wstring_view{L"abcd"}, 10) == 0);
	VERIFY(s1.rfind(bksge::wstring_view{L"abcde"}, 10) == bksge::static_wstring<N>::npos);

	VERIFY(s1.rfind(bksge::wstring_view{L"a"}, 8) == 5);
	VERIFY(s1.rfind(bksge::wstring_view{L"ab"}, 8) == 5);
	VERIFY(s1.rfind(bksge::wstring_view{L"abc"}, 8) == 5);
	VERIFY(s1.rfind(bksge::wstring_view{L"abcd"}, 8) == 0);
	VERIFY(s1.rfind(bksge::wstring_view{L"abcde"}, 8) == bksge::static_wstring<N>::npos);

	return true;
}

GTEST_TEST(StaticWStringTest, RFindTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((RFindStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((RFindStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((RFindStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((RFindStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((RFindStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((RFindStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfStringTest()
{
	bksge::static_wstring<N1> const s1 = L"abcde abcde";

	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"a"}) == 0);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"b"}) == 1);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"c"}) == 2);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"d"}) == 3);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"e"}) == 4);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyz"}) == bksge::static_wstring<N1>::npos);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyze"}) == 4);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzed"}) == 3);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzedc"}) == 2);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzedcb"}) == 1);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzedcba"}) == 0);

	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyz"}, 2) == bksge::static_wstring<N1>::npos);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyze"}, 2) == 4);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzed"}, 2) == 3);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzedc"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzedcb"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::static_wstring<N2>{L"xyzedcba"}, 2) == 2);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfCharPtrTest()
{
	bksge::static_wstring<N> const s1 = L"abcde abcde";

	VERIFY(s1.find_first_of(L"a") == 0);
	VERIFY(s1.find_first_of(L"b") == 1);
	VERIFY(s1.find_first_of(L"c") == 2);
	VERIFY(s1.find_first_of(L"d") == 3);
	VERIFY(s1.find_first_of(L"e") == 4);
	VERIFY(s1.find_first_of(L"xyz") == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_of(L"xyze") == 4);
	VERIFY(s1.find_first_of(L"xyzed") == 3);
	VERIFY(s1.find_first_of(L"xyzedc") == 2);
	VERIFY(s1.find_first_of(L"xyzedcb") == 1);
	VERIFY(s1.find_first_of(L"xyzedcba") == 0);

	VERIFY(s1.find_first_of(L"xyz", 2) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_of(L"xyze", 2) == 4);
	VERIFY(s1.find_first_of(L"xyzed", 2) == 3);
	VERIFY(s1.find_first_of(L"xyzedc", 2) == 2);
	VERIFY(s1.find_first_of(L"xyzedcb", 2) == 2);
	VERIFY(s1.find_first_of(L"xyzedcba", 2) == 2);

	VERIFY(s1.find_first_of(L"xedcba", 1, 1) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_of(L"xedcba", 1, 2) == 4);
	VERIFY(s1.find_first_of(L"xedcba", 1, 3) == 3);
	VERIFY(s1.find_first_of(L"xedcba", 1, 4) == 2);
	VERIFY(s1.find_first_of(L"xedcba", 1, 5) == 1);
	VERIFY(s1.find_first_of(L"xedcba", 1, 6) == 1);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfCharTest()
{
	bksge::static_wstring<N> const s1 = L"ab abc abcd";

	VERIFY(s1.find_first_of('a') == 0);
	VERIFY(s1.find_first_of('b') == 1);
	VERIFY(s1.find_first_of('c') == 5);
	VERIFY(s1.find_first_of('d') == 10);
	VERIFY(s1.find_first_of('e') == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_first_of('a', 1) == 3);
	VERIFY(s1.find_first_of('a', 4) == 7);
	VERIFY(s1.find_first_of('a', 8) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfStringViewTest()
{
	bksge::static_wstring<N> const s1 = L"abcde abcde";

	VERIFY(s1.find_first_of(bksge::wstring_view{L"a"}) == 0);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"b"}) == 1);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"c"}) == 2);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"d"}) == 3);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"e"}) == 4);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyz"}) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyze"}) == 4);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzed"}) == 3);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzedc"}) == 2);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzedcb"}) == 1);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzedcba"}) == 0);

	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyz"}, 2) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyze"}, 2) == 4);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzed"}, 2) == 3);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzedc"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzedcb"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::wstring_view{L"xyzedcba"}, 2) == 2);

	return true;
}

GTEST_TEST(StaticWStringTest, FindFirstOfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstOfStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstOfStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstOfStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstOfStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstOfStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstOfStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfStringTest()
{
	bksge::static_wstring<N1> const s1 = L"abcde abcde";

	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"a"}) == 6);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"b"}) == 7);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"c"}) == 8);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"d"}) == 9);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"e"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyz"}) == bksge::static_wstring<N1>::npos);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyze"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzed"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzedc"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzedcb"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzedcba"}) == 10);

	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyz"}, 8) == bksge::static_wstring<N1>::npos);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyze"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzed"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzedc"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzedcb"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::static_wstring<N2>{L"xyzedcba"}, 8) == 8);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfCharPtrTest()
{
	bksge::static_wstring<N> const s1 = L"abcde abcde";

	VERIFY(s1.find_last_of(L"a") == 6);
	VERIFY(s1.find_last_of(L"b") == 7);
	VERIFY(s1.find_last_of(L"c") == 8);
	VERIFY(s1.find_last_of(L"d") == 9);
	VERIFY(s1.find_last_of(L"e") == 10);
	VERIFY(s1.find_last_of(L"xyz") == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_last_of(L"xyze") == 10);
	VERIFY(s1.find_last_of(L"xyzed") == 10);
	VERIFY(s1.find_last_of(L"xyzedc") == 10);
	VERIFY(s1.find_last_of(L"xyzedcb") == 10);
	VERIFY(s1.find_last_of(L"xyzedcba") == 10);

	VERIFY(s1.find_last_of(L"xyz", 8) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_last_of(L"xyze", 8) == 4);
	VERIFY(s1.find_last_of(L"xyzed", 8) == 4);
	VERIFY(s1.find_last_of(L"xyzedc", 8) == 8);
	VERIFY(s1.find_last_of(L"xyzedcb", 8) == 8);
	VERIFY(s1.find_last_of(L"xyzedcba", 8) == 8);

	VERIFY(s1.find_last_of(L"Xabcde", 8, 1) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_last_of(L"Xabcde", 8, 2) == 6);
	VERIFY(s1.find_last_of(L"Xabcde", 8, 3) == 7);
	VERIFY(s1.find_last_of(L"Xabcde", 8, 4) == 8);
	VERIFY(s1.find_last_of(L"Xabcde", 8, 5) == 8);
	VERIFY(s1.find_last_of(L"Xabcde", 8, 6) == 8);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfCharTest()
{
	bksge::static_wstring<N> const s1 = L"ab abc abcd";

	VERIFY(s1.find_last_of('a') == 7);
	VERIFY(s1.find_last_of('b') == 8);
	VERIFY(s1.find_last_of('c') == 9);
	VERIFY(s1.find_last_of('d') == 10);
	VERIFY(s1.find_last_of('e') == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_last_of('b', 8) == 8);
	VERIFY(s1.find_last_of('b', 7) == 4);
	VERIFY(s1.find_last_of('b', 4) == 4);
	VERIFY(s1.find_last_of('b', 3) == 1);
	VERIFY(s1.find_last_of('b', 1) == 1);
	VERIFY(s1.find_last_of('b', 0) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfStringViewTest()
{
	bksge::static_wstring<N> const s1 = L"abcde abcde";

	VERIFY(s1.find_last_of(bksge::wstring_view{L"a"}) == 6);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"b"}) == 7);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"c"}) == 8);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"d"}) == 9);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"e"}) == 10);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyz"}) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyze"}) == 10);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzed"}) == 10);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzedc"}) == 10);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzedcb"}) == 10);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzedcba"}) == 10);

	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyz"}, 8) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyze"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzed"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzedc"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzedcb"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::wstring_view{L"xyzedcba"}, 8) == 8);

	return true;
}

GTEST_TEST(StaticWStringTest, FindLastOfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastOfStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastOfStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastOfStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastOfStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastOfStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastOfStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfStringTest()
{
	bksge::static_wstring<N1> const s1 = L"abcde";

	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"a"}) == 1);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"b"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"c"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"d"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"e"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"ba"}) == 2);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"cba"}) == 3);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"dcba"}) == 4);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"edcba"}) == bksge::static_wstring<N1>::npos);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"xyzedcba"}) == bksge::static_wstring<N1>::npos);

	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"de"}, 1) == 1);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"de"}, 2) == 2);
	VERIFY(s1.find_first_not_of(bksge::static_wstring<N2>{L"de"}, 3) == bksge::static_wstring<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfCharPtrTest()
{
	bksge::static_wstring<N> const s1 = L"abcde";

	VERIFY(s1.find_first_not_of(L"a") == 1);
	VERIFY(s1.find_first_not_of(L"b") == 0);
	VERIFY(s1.find_first_not_of(L"c") == 0);
	VERIFY(s1.find_first_not_of(L"d") == 0);
	VERIFY(s1.find_first_not_of(L"e") == 0);
	VERIFY(s1.find_first_not_of(L"ba") == 2);
	VERIFY(s1.find_first_not_of(L"cba") == 3);
	VERIFY(s1.find_first_not_of(L"dcba") == 4);
	VERIFY(s1.find_first_not_of(L"edcba") == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_not_of(L"xyzedcba") == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_first_not_of(L"de", 1) == 1);
	VERIFY(s1.find_first_not_of(L"de", 2) == 2);
	VERIFY(s1.find_first_not_of(L"de", 3) == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_first_not_of(L"abcde", 1, 1) == 1);
	VERIFY(s1.find_first_not_of(L"abcde", 1, 2) == 2);
	VERIFY(s1.find_first_not_of(L"abcde", 1, 3) == 3);
	VERIFY(s1.find_first_not_of(L"abcde", 1, 4) == 4);
	VERIFY(s1.find_first_not_of(L"abcde", 1, 5) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfCharTest()
{
	bksge::static_wstring<N> const s1 = L"aaaabbbccd";

	VERIFY(s1.find_first_not_of('a') == 4);
	VERIFY(s1.find_first_not_of('b') == 0);
	VERIFY(s1.find_first_not_of('c') == 0);
	VERIFY(s1.find_first_not_of('d') == 0);
	VERIFY(s1.find_first_not_of('e') == 0);

	VERIFY(s1.find_first_not_of('b', 4) == 7);
	VERIFY(s1.find_first_not_of('b', 8) == 8);
	VERIFY(s1.find_first_not_of('b', 9) == 9);
	VERIFY(s1.find_first_not_of('b', 10) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_not_of('d', 4) == 4);
	VERIFY(s1.find_first_not_of('d', 8) == 8);
	VERIFY(s1.find_first_not_of('d', 9) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_not_of('d', 10) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfStringViewTest()
{
	bksge::static_wstring<N> const s1 = L"abcde";

	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"a"}) == 1);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"b"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"c"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"d"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"e"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"ba"}) == 2);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"cba"}) == 3);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"dcba"}) == 4);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"edcba"}) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"xyzedcba"}) == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"de"}, 1) == 1);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"de"}, 2) == 2);
	VERIFY(s1.find_first_not_of(bksge::wstring_view{L"de"}, 3) == bksge::static_wstring<N>::npos);

	return true;
}

GTEST_TEST(StaticWStringTest, FindFirstNotOfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstNotOfStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstNotOfStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstNotOfStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstNotOfStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstNotOfStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindFirstNotOfStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfStringViewTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfStringTest()
{
	bksge::static_wstring<N1> const s1 = L"ddddcccbba";

	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"a"}) == 8);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"b"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"c"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"d"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"e"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"ab"}) == 6);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"abc"}) == 3);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"abcd"}) == bksge::static_wstring<N1>::npos);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"abcde"}) == bksge::static_wstring<N1>::npos);

	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"cd"}, 8) == 8);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"cd"}, 7) == 7);
	VERIFY(s1.find_last_not_of(bksge::static_wstring<N2>{L"cd"}, 6) == bksge::static_wstring<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfCharPtrTest()
{
	bksge::static_wstring<N> const s1 = L"ddddcccbba";

	VERIFY(s1.find_last_not_of(L"a") == 8);
	VERIFY(s1.find_last_not_of(L"b") == 9);
	VERIFY(s1.find_last_not_of(L"c") == 9);
	VERIFY(s1.find_last_not_of(L"d") == 9);
	VERIFY(s1.find_last_not_of(L"e") == 9);
	VERIFY(s1.find_last_not_of(L"ab") == 6);
	VERIFY(s1.find_last_not_of(L"abc") == 3);
	VERIFY(s1.find_last_not_of(L"abcd") == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_last_not_of(L"abcde") == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_last_not_of(L"cd", 8) == 8);
	VERIFY(s1.find_last_not_of(L"cd", 7) == 7);
	VERIFY(s1.find_last_not_of(L"cd", 6) == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_last_not_of(L"abcde", 8, 1) == 8);
	VERIFY(s1.find_last_not_of(L"abcde", 8, 2) == 6);
	VERIFY(s1.find_last_not_of(L"abcde", 8, 3) == 3);
	VERIFY(s1.find_last_not_of(L"abcde", 8, 4) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfCharTest()
{
	bksge::static_wstring<N> const s1 = L"ddddcccbba";

	VERIFY(s1.find_last_not_of('a') == 8);
	VERIFY(s1.find_last_not_of('b') == 9);
	VERIFY(s1.find_last_not_of('c') == 9);
	VERIFY(s1.find_last_not_of('d') == 9);
	VERIFY(s1.find_last_not_of('e') == 9);

	VERIFY(s1.find_last_not_of('d', 5) == 5);
	VERIFY(s1.find_last_not_of('d', 4) == 4);
	VERIFY(s1.find_last_not_of('d', 3) == bksge::static_wstring<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfStringViewTest()
{
	bksge::static_wstring<N> const s1 = L"ddddcccbba";

	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"a"}) == 8);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"b"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"c"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"d"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"e"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"ab"}) == 6);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"abc"}) == 3);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"abcd"}) == bksge::static_wstring<N>::npos);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"abcde"}) == bksge::static_wstring<N>::npos);

	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"cd"}, 8) == 8);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"cd"}, 7) == 7);
	VERIFY(s1.find_last_not_of(bksge::wstring_view{L"cd"}, 6) == bksge::static_wstring<N>::npos);

	return true;
}

GTEST_TEST(StaticWStringTest, FindLastNotOfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastNotOfStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastNotOfStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastNotOfStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastNotOfStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastNotOfStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((FindLastNotOfStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfStringViewTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfStringViewTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfStringViewTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool SubstrTest()
{
	bksge::static_wstring<N> const s1 = L"abcde";
	auto s2 = s1.substr();
	auto s3 = s1.substr(1);
	auto s4 = s1.substr(2);
	auto s5 = s1.substr(1, 1);
	auto s6 = s1.substr(1, 2);
	auto s7 = s1.substr(1, 3);
	auto s8 = s1.substr(2, 1);
	auto s9 = s1.substr(2, 2);
	auto s10 = s1.substr(2, 3);
	auto s11 = s1.substr(2, 4);

	VERIFY(s2 == L"abcde");
	VERIFY(s3 == L"bcde");
	VERIFY(s4 == L"cde");
	VERIFY(s5 == L"b");
	VERIFY(s6 == L"bc");
	VERIFY(s7 == L"bcd");
	VERIFY(s8 == L"c");
	VERIFY(s9 == L"cd");
	VERIFY(s10 == L"cde");
	VERIFY(s11 == L"cde");

	return true;
}

GTEST_TEST(StaticWStringTest, SubstrTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool StartsWithTest()
{
	bksge::static_wstring<N> const s = L"abcde";

	VERIFY(s.starts_with(bksge::wstring_view{L"abcde"})  == true);
	VERIFY(s.starts_with(bksge::wstring_view{L"abc"})    == true);
	VERIFY(s.starts_with(bksge::wstring_view{L"a"})      == true);
	VERIFY(s.starts_with(bksge::wstring_view{L"abcdef"}) == false);
	VERIFY(s.starts_with(bksge::wstring_view{L"abd"})    == false);
	VERIFY(s.starts_with(bksge::wstring_view{L"bc"})     == false);

	VERIFY(s.starts_with('a') == true);
	VERIFY(s.starts_with('b') == false);
	VERIFY(s.starts_with('e') == false);

	VERIFY(s.starts_with(L"abcde")  == true);
	VERIFY(s.starts_with(L"abc")    == true);
	VERIFY(s.starts_with(L"a")      == true);
	VERIFY(s.starts_with(L"abcdef") == false);
	VERIFY(s.starts_with(L"abd")    == false);
	VERIFY(s.starts_with(L"bc")     == false);

	return true;
}

GTEST_TEST(StaticWStringTest, StartsWithTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EndsWithTest()
{
	bksge::static_wstring<N> const s = L"abcde";

	VERIFY(s.ends_with(bksge::wstring_view{L"abcde"})  == true);
	VERIFY(s.ends_with(bksge::wstring_view{L"cde"})    == true);
	VERIFY(s.ends_with(bksge::wstring_view{L"e"})      == true);
	VERIFY(s.ends_with(bksge::wstring_view{L"abcdef"}) == false);
	VERIFY(s.ends_with(bksge::wstring_view{L"dde"})    == false);
	VERIFY(s.ends_with(bksge::wstring_view{L"cdf"})    == false);
	VERIFY(s.ends_with(bksge::wstring_view{L"cd"})     == false);

	VERIFY(s.ends_with('e') == true);
	VERIFY(s.ends_with('d') == false);
	VERIFY(s.ends_with('a') == false);

	VERIFY(s.ends_with(L"abcde")  == true);
	VERIFY(s.ends_with(L"cde")    == true);
	VERIFY(s.ends_with(L"e")      == true);
	VERIFY(s.ends_with(L"abcdef") == false);
	VERIFY(s.ends_with(L"dde")    == false);
	VERIFY(s.ends_with(L"cdf")    == false);
	VERIFY(s.ends_with(L"cd")     == false);

	return true;
}

GTEST_TEST(StaticWStringTest, EndsWithTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	{
		bksge::static_wstring<N> const s = L"abc";
		auto p = s.data();
		VERIFY(p[0] == 'a');
		VERIFY(p[1] == 'b');
		VERIFY(p[2] == 'c');
		VERIFY(c_str_test(s, L"abc"));
	}
	{
		bksge::static_wstring<N> s = L"abc";
		auto p = s.data();
		VERIFY(p[0] == 'a');
		VERIFY(p[1] == 'b');
		VERIFY(p[2] == 'c');
		p[1] = 'X';
		VERIFY(c_str_test(s, L"aXc"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	{
		bksge::static_wstring<N1> s1 = L"abc";
		bksge::static_wstring<N2> s2 = L"12345";
		s1.swap(s2);
		VERIFY(c_str_test(s1, L"12345"));
		VERIFY(c_str_test(s2, L"abc"));
	}
	{
		bksge::static_wstring<N1> s1 = L"abcdefg";
		bksge::static_wstring<N2> s2 = L"123";
		bksge::ranges::swap(s1, s2);
		VERIFY(c_str_test(s1, L"123"));
		VERIFY(c_str_test(s2, L"abcdefg"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<100, 100>()));
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AddStringStringTest()
{
	{
		bksge::static_wstring<N1> const s1 = L"abc";
		bksge::static_wstring<N2> const s2 = L"12345";
		auto s3 = s1 + s2;
		VERIFY(c_str_test(s3, L"abc12345"));
	}
	{
		bksge::static_wstring<N1> const s1 = L"abc";
		bksge::static_wstring<N2> const s2 = L"123";
		auto s3 = L"xxx" + s1 + L'y' + s2 + L'z' + L"AA";
		VERIFY(c_str_test(s3, L"xxxabcy123zAA"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddStringCharPtrTest()
{
	{
		bksge::static_wstring<N> const s1 = L"abc";
		auto s2 = s1 + L"defg";
		VERIFY(c_str_test(s2, L"abcdefg"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddStringCharTest()
{
	{
		bksge::static_wstring<N> const s1 = L"abc";
		auto s2 = s1 + L'1';
		VERIFY(c_str_test(s2, L"abc1"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddCharPtrStringTest()
{
	{
		bksge::static_wstring<N> const s1 = L"abc";
		auto s2 = L"defg" + s1;
		VERIFY(c_str_test(s2, L"defgabc"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddCharStringTest()
{
	{
		bksge::static_wstring<N> const s1 = L"abc";
		auto s2 = L'1' + s1;
		VERIFY(c_str_test(s2, L"1abc"));
	}
	return true;
}

GTEST_TEST(StaticWStringTest, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddStringStringTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddStringStringTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddStringStringTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddStringStringTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddStringStringTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddStringStringTest<100, 100>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddStringCharPtrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddStringCharPtrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddStringCharPtrTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddStringCharTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddStringCharTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddStringCharTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddCharPtrStringTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddCharPtrStringTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddCharPtrStringTest<100>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddCharStringTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddCharStringTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddCharStringTest<100>());
}

GTEST_TEST(StaticWStringTest, InputStreamTest)
{
	{
		std::wstringstream ss(L"abc");
		bksge::static_wstring<16> s;
		ss >> s;
		EXPECT_TRUE(s == L"abc");
	}
	{
		std::wstringstream ss(L"Hello World");
		bksge::static_wstring<32> s;
		ss >> s;
		EXPECT_TRUE(s == L"Hello");
		ss >> s;
		EXPECT_TRUE(s == L"World");
	}
}

GTEST_TEST(StaticWStringTest, OutputStreamTest)
{
	{
		bksge::static_wstring<16> const s = L"abc";
		std::wstringstream ss;
		ss << s;
		EXPECT_TRUE(ss.str() == L"abc");
	}
	{
		bksge::static_wstring<32> const s = L"Hello World";
		std::wstringstream ss;
		ss << s;
		EXPECT_TRUE(ss.str() == L"Hello World");
	}
}

#undef VERIFY

}	// namespace bksge_static_wstring_test
