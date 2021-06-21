/**
 *	@file	unit_test_fnd_static_u8string.cpp
 *
 *	@brief	bksge::static_u8string のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/static_string/static_u8string.hpp>
#include <bksge/fnd/string_view/u8string_view.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace bksge_static_u8string_test
{

#if defined(BKSGE_HAS_CXX20_CHAR8_T)

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
c_str_test(bksge::static_u8string<N> const& s, char8_t const* str)
{
	using traits_type = typename bksge::static_u8string<N>::traits_type;
	auto const str2 = s.c_str();
	VERIFY(traits_type::length(str2) == traits_type::length(str));
	VERIFY(traits_type::length(str2) == s.length());
	VERIFY(traits_type::compare(str2, str, s.length()) == 0);
	VERIFY(s.compare(str) == 0);
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorDefaultTest()
{
	{
		bksge::static_u8string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));
	}
	{
		bksge::static_u8string<N> s{};
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));
	}
	{
		bksge::static_u8string<N> s={};
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCountCharTest()
{
	{
		bksge::static_u8string<N> s(0, u8'a');
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));
	}
	{
		bksge::static_u8string<N> s(1, u8'a');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"a"));
	}
	{
		bksge::static_u8string<N> s(4, u8'c');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"cccc"));
	}
	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorOtherPosTest()
{
	{
		bksge::static_u8string<N1> const s1(u8"hello");
		bksge::static_u8string<N2> const s2(s1, 1);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 4);
		VERIFY(s2.length()   == 4);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, u8"ello"));
	}
	{
		bksge::static_u8string<N1> const s1(u8"hello");
		bksge::static_u8string<N2> const s2{s1, 2};

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 3);
		VERIFY(s2.length()   == 3);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, u8"llo"));
	}

	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorOtherPosCountTest()
{
	{
		bksge::static_u8string<N1> const s1(u8"hello");
		bksge::static_u8string<N2> const s2(s1, 1, 3);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 3);
		VERIFY(s2.length()   == 3);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, u8"ell"));
	}
	{
		bksge::static_u8string<N1> const s1(u8"hello");
		bksge::static_u8string<N2> const s2{s1, 2, 2};

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 2);
		VERIFY(s2.length()   == 2);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, u8"ll"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrCountTest()
{
	{
		bksge::static_u8string<N> s(u8"abcde", 4);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abcd"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrTest()
{
	{
		bksge::static_u8string<N> s(u8"abcde");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abcde"));
	}
	{
		bksge::static_u8string<N> s{u8"hello world!"};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 12);
		VERIFY(s.length()   == 12);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"hello world!"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorIteratorTest()
{
	{
		char8_t const buf[] = u8"abcde";
		bksge::static_u8string<N> const s(buf, buf + 3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abc"));
	}

	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorCopyTest()
{
	{
		bksge::static_u8string<N1> const s1(u8"hello world");
		bksge::static_u8string<N2> const s2(s1);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"hello world"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 11);
		VERIFY(s2.length()   == 11);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, u8"hello world"));
	}

	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorMoveTest()
{
	{
		bksge::static_u8string<N1> s1(u8"hello world");
		bksge::static_u8string<N2> const s2(bksge::move(s1));
		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 11);
		VERIFY(s2.length()   == 11);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, u8"hello world"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorInitializerListTest()
{
	{
		bksge::static_u8string<N> s{'h', u8'e', u8'l', u8'l', u8'o'};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"hello"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringViewTest()
{
	{
		bksge::static_u8string<N> s(bksge::u8string_view{u8"Hello World"});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"Hello World"));
	}
	{
		bksge::static_u8string<N> s(u8"Hello World");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"Hello World"));
	}
	{
		bksge::static_u8string<N> s(bksge::u8string_view{u8"Hello World"}, 2, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"llo W"));
	}
	{
		bksge::static_u8string<N> s(u8"Hello World", 2, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"llo W"));
	}
	{
		bksge::static_u8string<N> s(bksge::u8string_view{u8"Hello World"}, 2, 100);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 9);
		VERIFY(s.length()   == 9);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"llo World"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, CtorTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringTest()
{
	{
		bksge::static_u8string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_u8string<N2> const s2(u8"hello world");
		s1 = s2;
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"hello world"));

		bksge::static_u8string<N2> const s3(u8"abc");
		s1.assign(s3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"abc"));

		bksge::static_u8string<N2> const s4(u8"Hello World");
		s1.assign(s4, 3, 4);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 4);
		VERIFY(s1.length()   == 4);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"lo W"));

		s1.assign(s4, 3, 100);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"lo World"));
	}

	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringMoveTest()
{
	{
		bksge::static_u8string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_u8string<N2> s2(u8"hello world");
		s1 = bksge::move(s2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"hello world"));

		bksge::static_u8string<N2> s3(u8"abc");
		s1.assign(bksge::move(s3));
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"abc"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharPtrTest()
{
	{
		bksge::static_u8string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));

		s = u8"hoge";
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"hoge"));

		s.assign(u8"a");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"a"));

		s.assign(u8"world", 3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"wor"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharTest()
{
	{
		bksge::static_u8string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));

		s = 'A';
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"A"));

		s.assign(2, u8'B');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 2);
		VERIFY(s.length()   == 2);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"BB"));

		s = 'C';
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"C"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignIteratorTest()
{
	{
		bksge::static_u8string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));

		char8_t buf[] = u8"hello";

		s.assign(buf, buf+5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"hello"));

		s.assign(buf, buf+3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"hel"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignInitializerListTest()
{
	{
		bksge::static_u8string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));

		s = {'h', u8'e', u8'l', u8'l', u8'o'};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"hello"));

		s.assign({'a', u8'b', u8'c', u8'd'});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abcd"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringViewTest()
{
	{
		bksge::static_u8string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8""));

		s = bksge::u8string_view{u8"Hello World"};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"Hello World"));

		s.assign(bksge::u8string_view{u8"abc"});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abc"));

		s.assign(bksge::u8string_view{u8"Hello World"}, 1, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"ello "));

		s.assign(u8"Hello World", 2, 6);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 6);
		VERIFY(s.length()   == 6);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"llo Wo"));

		s.assign(bksge::u8string_view{u8"Hello World"}, 2, 100);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 9);
		VERIFY(s.length()   == 9);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"llo World"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, AssignTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringTest()
{
	{
		bksge::static_u8string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_u8string<N2> const s2 = u8"abc";
		s1 += s2;
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"abc"));

		bksge::static_u8string<N2> const s3 = u8"hello";
		s1.append(s3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"abchello"));
	}

	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringPosTest()
{
	{
		bksge::static_u8string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_u8string<N2> const s2 = u8"abc";
		s1.append(s2, 1);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"bc"));

		bksge::static_u8string<N2> const s3 = u8"hello";
		s1.append(s3, 2, 3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"bcllo"));

		bksge::static_u8string<N2> const s4 = u8"world";
		s1.append(s4, 1, 10);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 9);
		VERIFY(s1.length()   == 9);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, u8"bclloorld"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharPtrTest()
{
	{
		bksge::static_u8string<N> s1;
		VERIFY(s1.empty());

		s1 += u8"hello";
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"hello"));

		s1.append(u8" world");
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"hello world"));

		s1.append(u8"ABCDE", 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 13);
		VERIFY(s1.length()   == 13);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"hello worldAB"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharTest()
{
	{
		bksge::static_u8string<N> s1;
		VERIFY(s1.empty());

		s1 += 'A';
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"A"));

		s1.append(3, u8'B');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 4);
		VERIFY(s1.length()   == 4);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"ABBB"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendInitializerListTest()
{
	{
		bksge::static_u8string<N> s1;
		VERIFY(s1.empty());

		s1 += { 'A', u8'B', u8'C' };
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"ABC"));

		s1.append({ 'h', u8'e', u8'l', u8'l', u8'o' });
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"ABChello"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendIteratorTest()
{
	{
		bksge::static_u8string<N> s1;
		VERIFY(s1.empty());

		char8_t buf[] = u8"hello";

		s1.append(buf, buf+5);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"hello"));

		s1.append(buf+1, buf+3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 7);
		VERIFY(s1.length()   == 7);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"helloel"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringViewTest()
{
	{
		bksge::static_u8string<N> s1;
		VERIFY(s1.empty());

		s1 += bksge::u8string_view{u8"Hel"};
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"Hel"));

		s1.append(bksge::u8string_view{u8"lo"});
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"Hello"));

		s1.append(bksge::u8string_view{u8"abcde"}, 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"Hellocde"));

		s1.append(bksge::u8string_view{u8"ABCDE"}, 1, 3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"HellocdeBCD"));

		s1.append(u8"ABCDE", 2, 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 13);
		VERIFY(s1.length()   == 13);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"HellocdeBCDCD"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, AppendTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringTest()
{
	{
		bksge::static_u8string<N1> s1 = u8"aaa";
		bksge::static_u8string<N2> s2 = u8"bbb";
		s1.insert(2, s2);
		VERIFY(c_str_test(s1, u8"aabbba"));
	}

	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringPosTest()
{
	{
		bksge::static_u8string<N1> s1 = u8"aaa";
		bksge::static_u8string<N2> s2 = u8"12345";
		s1.insert(2, s2, 2, 3);
		VERIFY(c_str_test(s1, u8"aa345a"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"aaa";
		bksge::static_u8string<N2> s2 = u8"12345";
		s1.insert(3, s2, 1);
		VERIFY(c_str_test(s1, u8"aaa2345"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"aaa";
		bksge::static_u8string<N2> s2 = u8"12345";
		s1.insert(1, s2, 1, 100);
		VERIFY(c_str_test(s1, u8"a2345aa"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharPtrCountTest()
{
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(2, u8"12345", 2);
		VERIFY(c_str_test(s1, u8"aa12a"));
	}
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(2, u8"12345", 0);
		VERIFY(c_str_test(s1, u8"aaa"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharPtrTest()
{
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(1, u8"12345");
		VERIFY(c_str_test(s1, u8"a12345aa"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharTest()
{
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(2, 3, u8'b');
		VERIFY(c_str_test(s1, u8"aabbba"));
	}
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(2, 0, u8'b');
		VERIFY(c_str_test(s1, u8"aaa"));
	}

	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(s1.begin(), u8'b');
		VERIFY(c_str_test(s1, u8"baaa"));
	}
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(s1.end(), u8'c');
		VERIFY(c_str_test(s1, u8"aaac"));
	}

	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(s1.begin(), 2, u8'b');
		VERIFY(c_str_test(s1, u8"bbaaa"));
	}
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(s1.end(), 3, u8'c');
		VERIFY(c_str_test(s1, u8"aaaccc"));
	}
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(s1.end(), 0, u8'c');
		VERIFY(c_str_test(s1, u8"aaa"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertIteratorTest()
{
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		char8_t buf[] = u8"xyz";
		s1.insert(s1.begin(), buf, buf+3);
		VERIFY(c_str_test(s1, u8"xyzaaa"));
	}
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		char8_t buf[] = u8"xyz";
		s1.insert(s1.end(), buf, buf+3);
		VERIFY(c_str_test(s1, u8"aaaxyz"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertInitializerListTest()
{
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(s1.begin()+1, {'1', u8'2', u8'3', u8'4', u8'5'});
		VERIFY(c_str_test(s1, u8"a12345aa"));
	}
	{
		bksge::static_u8string<N> s1 = u8"aaa";
		s1.insert(s1.end(), {'b', u8'c'});
		VERIFY(c_str_test(s1, u8"aaabc"));
	}

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringViewTest()
{
	{
		bksge::static_u8string<N> s1 = u8"abcde";
		s1.insert(0, bksge::u8string_view{u8"xyz"});
		VERIFY(c_str_test(s1, u8"xyzabcde"));
	}
	{
		bksge::static_u8string<N> s1 = u8"abcde";
		s1.insert(1, bksge::u8string_view{u8"12345"}, 1);
		VERIFY(c_str_test(s1, u8"a2345bcde"));
	}
	{
		bksge::static_u8string<N> s1 = u8"abcde";
		s1.insert(2, bksge::u8string_view{u8"12345"}, 2, 3);
		VERIFY(c_str_test(s1, u8"ab345cde"));
	}
	{
		bksge::static_u8string<N> s1 = u8"abcde";
		s1.insert(2, bksge::u8string_view{u8"12345"}, 2, 4);
		VERIFY(c_str_test(s1, u8"ab345cde"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, InsertTest)
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

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ErasePosCountTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.erase(1, 2);
		VERIFY(c_str_test(s1, u8"145"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.erase(2);
		VERIFY(c_str_test(s1, u8"12"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.erase();
		VERIFY(c_str_test(s1, u8""));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EraseIteratorTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.erase(s1.begin());
		VERIFY(c_str_test(s1, u8"2345"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.erase(s1.begin()+1);
		VERIFY(c_str_test(s1, u8"1345"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EraseFirstLastTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.erase(s1.begin(), s1.begin()+2);
		VERIFY(c_str_test(s1, u8"345"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.erase(s1.begin()+2, s1.end());
		VERIFY(c_str_test(s1, u8"12"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, EraseTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringTest()
{
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"abcde";
		s1.replace(1, 2, s2);
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"abcde";
		s1.replace(2, 100, s2);
		VERIFY(c_str_test(s1, u8"12abcde"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"a";
		s1.replace(1, 2, s2);
		VERIFY(c_str_test(s1, u8"1a45"));
	}
	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringPosCountTest()
{
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"abcde";
		s1.replace(1, 2, s2, 2, 3);
		VERIFY(c_str_test(s1, u8"1cde45"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"abcde";
		s1.replace(2, 1, s2, 1);
		VERIFY(c_str_test(s1, u8"12bcde45"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"abcde";
		s1.replace(1, 2, s2, 2, 1);
		VERIFY(c_str_test(s1, u8"1c45"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrCountTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 2, u8"abcde", 3);
		VERIFY(c_str_test(s1, u8"1abc45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(2, 100, u8"abcde", 2);
		VERIFY(c_str_test(s1, u8"12ab"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 2, u8"abcde");
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(2, 100, u8"abcde");
		VERIFY(c_str_test(s1, u8"12abcde"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 3, u8"z");
		VERIFY(c_str_test(s1, u8"1z5"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCountCharTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 2, 3, u8'x');
		VERIFY(c_str_test(s1, u8"1xxx45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(2, 100, 4, u8'y');
		VERIFY(c_str_test(s1, u8"12yyyy"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 3, 1, u8'z');
		VERIFY(c_str_test(s1, u8"1z5"));
	}
	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorStringTest()
{
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2);
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"abcde";
		s1.replace(s1.begin(), s1.end(), s2);
		VERIFY(c_str_test(s1, u8"abcde"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"12345";
		bksge::static_u8string<N2> s2 = u8"xy";
		s1.replace(s1.begin() + 1, s1.begin() + 4, s2);
		VERIFY(c_str_test(s1, u8"1xy5"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCharPtrCountTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, u8"abcde", 3);
		VERIFY(c_str_test(s1, u8"1abc45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin(), s1.end(), u8"abcde", 2);
		VERIFY(c_str_test(s1, u8"ab"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCharPtrTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, u8"abcde");
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin(), s1.end(), u8"abcde");
		VERIFY(c_str_test(s1, u8"abcde"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 4, u8"xy");
		VERIFY(c_str_test(s1, u8"1xy5"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCountCharTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, 3, u8'x');
		VERIFY(c_str_test(s1, u8"1xxx45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin(), s1.end(), 2, u8'y');
		VERIFY(c_str_test(s1, u8"yy"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorIteratorTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		bksge::static_u8string<N> s2 = u8"abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2.begin(), s2.end());
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		bksge::static_u8string<N> s2 = u8"abcde";
		s1.replace(s1.begin(), s1.end(), s2.begin(), s2.end());
		VERIFY(c_str_test(s1, u8"abcde"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		bksge::static_u8string<N> s2 = u8"abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2.begin(), s2.begin()+1);
		VERIFY(c_str_test(s1, u8"1a45"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorInitializerListTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, {'a', u8'b', u8'c', u8'd', u8'e'});
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin(), s1.end(), {'a', u8'b', u8'c', u8'd'});
		VERIFY(c_str_test(s1, u8"abcd"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 2, bksge::u8string_view{u8"abcde"});
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 100, bksge::u8string_view{u8"abcde"});
		VERIFY(c_str_test(s1, u8"1abcde"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 3, bksge::u8string_view{u8"A"});
		VERIFY(c_str_test(s1, u8"1A5"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewPosCountTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 2, bksge::u8string_view{u8"XXXabcdeYYY"}, 3, 5);
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(2, 2, bksge::u8string_view{u8"XXXabcdeYYY"}, 3);
		VERIFY(c_str_test(s1, u8"12abcdeYYY5"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(2, 1, u8"abcde", 2, 3);
		VERIFY(c_str_test(s1, u8"12cde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(1, 3, u8"abcde", 2, 1);
		VERIFY(c_str_test(s1, u8"1c5"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorStringViewTest()
{
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, bksge::u8string_view{u8"abcde"});
		VERIFY(c_str_test(s1, u8"1abcde45"));
	}
	{
		bksge::static_u8string<N> s1 = u8"12345";
		s1.replace(s1.begin(), s1.end(), bksge::u8string_view{u8"abc"});
		VERIFY(c_str_test(s1, u8"abc"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, ReplaceTest)
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

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CopyTest()
{
	bksge::static_u8string<N> const s = u8"hello";
	using traits_type = typename bksge::static_u8string<N>::traits_type;
	{
		char8_t result[5 + 1] ={};
		auto ret = s.copy(result, 5);
		VERIFY(traits_type::compare(result, u8"hello", 5) == 0);
		VERIFY(ret == 5);
	}
	{
		char8_t result[3 + 1] ={};
		auto ret = s.copy(result, 3);
		VERIFY(traits_type::compare(result, u8"hel", 3) == 0);
		VERIFY(ret == 3);
	}
	{
		char8_t result[3 + 1] ={};
		auto ret = s.copy(result, 3, 2);
		VERIFY(traits_type::compare(result, u8"llo", 3) == 0);
		VERIFY(ret == 3);
	}
	{
		char8_t result[5 + 1] ={};
		auto ret = s.copy(result, 100, 1);
		VERIFY(traits_type::compare(result, u8"ello", 4) == 0);
		VERIFY(ret == 4);
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, CopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool PushBackTest()
{
	{
		bksge::static_u8string<N> s1;
		VERIFY(s1.empty());

		s1.push_back('a');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"a"));

		s1.push_back('b');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"ab"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, PushBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool PopBackTest()
{
	{
		bksge::static_u8string<N> s1 = u8"abc";
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"abc"));

		s1.pop_back();
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"ab"));

		s1.pop_back();
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, u8"a"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, PopBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool BeginEndTest()
{
	{
		bksge::static_u8string<N> s = u8"abc";
		auto it = s.begin();
		VERIFY(*it == 'a');
		*it++ = 'X';
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.end());
		++it;
		VERIFY(it == s.end());
		VERIFY(c_str_test(s, u8"Xbc"));
	}
	{
		bksge::static_u8string<N> const s = u8"abc";
		auto it = s.begin();
		VERIFY(*it++ == 'a');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.end());
		++it;
		VERIFY(it == s.end());
		VERIFY(c_str_test(s, u8"abc"));
	}
	{
		bksge::static_u8string<N> s = u8"abc";
		auto it = s.cbegin();
		VERIFY(*it++ == 'a');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.cend());
		++it;
		VERIFY(it == s.cend());
		VERIFY(c_str_test(s, u8"abc"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, BeginEndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RBeginREndTest()
{
	{
		bksge::static_u8string<N> s = u8"abc";
		auto it = s.rbegin();
		VERIFY(*it == 'c');
		*it++ = 'X';
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.rend());
		++it;
		VERIFY(it == s.rend());
		VERIFY(c_str_test(s, u8"abX"));
	}
	{
		bksge::static_u8string<N> const s = u8"abc";
		auto it = s.rbegin();
		VERIFY(*it++ == 'c');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.rend());
		++it;
		VERIFY(it == s.rend());
		VERIFY(c_str_test(s, u8"abc"));
	}
	{
		bksge::static_u8string<N> s = u8"abc";
		auto it = s.crbegin();
		VERIFY(*it++ == 'c');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.crend());
		++it;
		VERIFY(it == s.crend());
		VERIFY(c_str_test(s, u8"abc"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, RBeginREndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ResizeTest()
{
	{
		bksge::static_u8string<N> s = u8"abc";
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abc"));
		s.resize(5, u8'X');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abcXX"));
		s.resize(4, u8'Y');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"abcX"));
		s.resize(6);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 6);
		VERIFY(s.length()   == 6);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		//VERIFY(s.compare(u8"abcX") == 0);
		s.resize(2);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 2);
		VERIFY(s.length()   == 2);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, u8"ab"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, ResizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReserveTest()
{
	{
		bksge::static_u8string<N> s = u8"abc";
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

GTEST_TEST(StaticU8StringTest, ReserveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ClearTest()
{
	{
		bksge::static_u8string<N> s = u8"abc";
		VERIFY(!s.empty());
		VERIFY(c_str_test(s, u8"abc"));

		s.clear();
		VERIFY(s.empty());
		VERIFY(c_str_test(s, u8""));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, ClearTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool BraceTest()
{
	{
		bksge::static_u8string<N> const s = u8"abc";
		VERIFY(s[0] == 'a');
		VERIFY(s[1] == 'b');
		VERIFY(s[2] == 'c');
	}
	{
		bksge::static_u8string<N> s = u8"abc";
		s[1] = 'Z';
		VERIFY(c_str_test(s, u8"aZc"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, BraceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	{
		bksge::static_u8string<N> const s = u8"abc";
		VERIFY(s.at(0) == 'a');
		VERIFY(s.at(1) == 'b');
		VERIFY(s.at(2) == 'c');
	}
	{
		bksge::static_u8string<N> s = u8"abc";
		s.at(1) = 'Z';
		VERIFY(c_str_test(s, u8"aZc"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FrontBackTest()
{
	{
		bksge::static_u8string<N> const s = u8"abc";
		VERIFY(s.front() == 'a');
		VERIFY(s.back()  == 'c');
	}
	{
		bksge::static_u8string<N> s = u8"abc";
		s.front() = 'X';
		s.back()  = 'Y';
		VERIFY(c_str_test(s, u8"XbY"));
	}

	return true;
}

GTEST_TEST(StaticU8StringTest, FrontBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<100>());
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CompareStringTest()
{
	{
		bksge::static_u8string<N1> const s1 = u8"12345";
		bksge::static_u8string<N2> const s2 = u8"12345";
		bksge::static_u8string<N2> const s3 = u8"123456";
		bksge::static_u8string<N2> const s4 = u8"1234";
		bksge::static_u8string<N2> const s5 = u8"12346";
		bksge::static_u8string<N2> const s6 = u8"12344";

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) < 0);
		VERIFY(s1.compare(s4) > 0);
		VERIFY(s1.compare(s5) < 0);
		VERIFY(s1.compare(s6) > 0);
	}
	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringTest()
{
	{
		bksge::static_u8string<N1> const s1 = u8"123456";
		bksge::static_u8string<N2> const s2 = u8"12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", u8"12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringPosCountTest()
{
	{
		bksge::static_u8string<N1> const s1 = u8"12345";
		bksge::static_u8string<N2> const s2 = u8"123456";

		VERIFY(s1.compare(0, 5, s2, 0, 5) == 0);	// "12345", u8"12345"
		VERIFY(s1.compare(0, 6, s2, 0)    < 0);		// "12345", u8"123456"
		VERIFY(s1.compare(0, 4, s2, 0, 5) < 0);		// "1234",  "12345"
		VERIFY(s1.compare(0, 4, s2, 0, 3) > 0);		// "1234",  "123"
		VERIFY(s1.compare(1, 3, s2, 1, 3) == 0);	// "234",   "234"
		VERIFY(s1.compare(1, 3, s2, 0, 3) > 0);		// "234",   "123"
		VERIFY(s1.compare(1, 4, s2, 2, 3) < 0);		// "2345",  "345"
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CompareCharPtrTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"12345";
		char8_t const* s2 = u8"12345";
		char8_t const* s3 = u8"123456";
		char8_t const* s4 = u8"1234";
		char8_t const* s5 = u8"12346";
		char8_t const* s6 = u8"12344";

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) < 0);
		VERIFY(s1.compare(s4) > 0);
		VERIFY(s1.compare(s5) < 0);
		VERIFY(s1.compare(s6) > 0);
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountCharPtrTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"123456";
		char8_t const* s2 = u8"12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", u8"12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountCharPtrCountTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"12345";
		char8_t const* s2 = u8"123456";

		VERIFY(s1.compare(0, 5, s2, 5) == 0);	// "12345", u8"12345"
		VERIFY(s1.compare(0, 5, s2, 9) < 0);	// "12345", u8"123456"
		VERIFY(s1.compare(1, 4, s2, 9) > 0);	// "2345",  "123456"
		VERIFY(s1.compare(0, 4, s2, 5) < 0);	// "1234",  "12345"
		VERIFY(s1.compare(0, 4, s2, 3) > 0);	// "1234",  "123"
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CompareStringViewTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"12345";
		bksge::u8string_view const s2 = u8"12345";
		bksge::u8string_view const s3 = u8"123456";
		bksge::u8string_view const s4 = u8"1234";
		bksge::u8string_view const s5 = u8"12346";
		bksge::u8string_view const s6 = u8"12344";

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) < 0);
		VERIFY(s1.compare(s4) > 0);
		VERIFY(s1.compare(s5) < 0);
		VERIFY(s1.compare(s6) > 0);
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringViewTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"123456";
		bksge::u8string_view const s2 = u8"12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", u8"12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringViewPosCountTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"12345";
		bksge::u8string_view const s2 = u8"123456";

		VERIFY(s1.compare(0, 5, s2, 0, 5) == 0);	// "12345", u8"12345"
		VERIFY(s1.compare(0, 6, s2, 0)    < 0);		// "12345", u8"123456"
		VERIFY(s1.compare(0, 4, s2, 0, 5) < 0);		// "1234",  "12345"
		VERIFY(s1.compare(0, 4, s2, 0, 3) > 0);		// "1234",  "123"
		VERIFY(s1.compare(1, 3, s2, 1, 3) == 0);	// "234",   "234"
		VERIFY(s1.compare(1, 3, s2, 0, 3) > 0);		// "234",   "123"
		VERIFY(s1.compare(1, 4, s2, 2, 3) < 0);		// "2345",  "345"
	}
	return true;
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CompareOperatorStringTest()
{
	{
		bksge::static_u8string<N1> const s1 = u8"abc";
		bksge::static_u8string<N2> const s2 = u8"abc";
		bksge::static_u8string<N2> const s3 = u8"abcd";
		bksge::static_u8string<N2> const s4 = u8"ab";
		bksge::static_u8string<N2> const s5 = u8"abe";
		bksge::static_u8string<N2> const s6 = u8"aba";

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

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CompareOperatorCharPtrTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"abc";
		char8_t const* s2 = u8"abc";
		char8_t const* s3 = u8"abcd";
		char8_t const* s4 = u8"ab";
		char8_t const* s5 = u8"abe";
		char8_t const* s6 = u8"aba";

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

GTEST_TEST(StaticU8StringTest, CompareTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindStringTest()
{
	bksge::static_u8string<N1> const s1 = u8"ab abc abcd";

	VERIFY(s1.find(bksge::static_u8string<N2>{u8"a"}) == 0);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"ab"}) == 0);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"abc"}) == 3);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"abcd"}) == 7);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"abcde"}) == bksge::static_u8string<N1>::npos);

	VERIFY(s1.find(bksge::static_u8string<N2>{u8"a"}, 1) == 3);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"ab"}, 1) == 3);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"abc"}, 1) == 3);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"abcd"}, 1) == 7);
	VERIFY(s1.find(bksge::static_u8string<N2>{u8"abcde"}, 1) == bksge::static_u8string<N1>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindCharPtrTest()
{
	bksge::static_u8string<N> const s1 = u8"ab abc abcd";

	VERIFY(s1.find(u8"a") == 0);
	VERIFY(s1.find(u8"ab") == 0);
	VERIFY(s1.find(u8"abc") == 3);
	VERIFY(s1.find(u8"abcd") == 7);
	VERIFY(s1.find(u8"abcde") == bksge::static_u8string<N>::npos);

	VERIFY(s1.find(u8"a", 1) == 3);
	VERIFY(s1.find(u8"ab", 1) == 3);
	VERIFY(s1.find(u8"abc", 1) == 3);
	VERIFY(s1.find(u8"abcd", 1) == 7);
	VERIFY(s1.find(u8"abcde", 1) == bksge::static_u8string<N>::npos);

	VERIFY(s1.find(u8"abcde", 1, 1) == 3);
	VERIFY(s1.find(u8"abcde", 1, 2) == 3);
	VERIFY(s1.find(u8"abcde", 1, 3) == 3);
	VERIFY(s1.find(u8"abcde", 1, 4) == 7);
	VERIFY(s1.find(u8"abcde", 1, 5) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindCharTest()
{
	bksge::static_u8string<N> const s1 = u8"ab abc abcd";

	VERIFY(s1.find('a') == 0);
	VERIFY(s1.find('b') == 1);
	VERIFY(s1.find('c') == 5);
	VERIFY(s1.find('d') == 10);
	VERIFY(s1.find('e') == bksge::static_u8string<N>::npos);

	VERIFY(s1.find('a', 1) == 3);
	VERIFY(s1.find('a', 4) == 7);
	VERIFY(s1.find('a', 8) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindStringViewTest()
{
	bksge::static_u8string<N> const s1 = u8"ab abc abcd";

	VERIFY(s1.find(bksge::u8string_view{u8"a"}) == 0);
	VERIFY(s1.find(bksge::u8string_view{u8"ab"}) == 0);
	VERIFY(s1.find(bksge::u8string_view{u8"abc"}) == 3);
	VERIFY(s1.find(bksge::u8string_view{u8"abcd"}) == 7);
	VERIFY(s1.find(bksge::u8string_view{u8"abcde"}) == bksge::static_u8string<N>::npos);

	VERIFY(s1.find(bksge::u8string_view{u8"a"}, 1) == 3);
	VERIFY(s1.find(bksge::u8string_view{u8"ab"}, 1) == 3);
	VERIFY(s1.find(bksge::u8string_view{u8"abc"}, 1) == 3);
	VERIFY(s1.find(bksge::u8string_view{u8"abcd"}, 1) == 7);
	VERIFY(s1.find(bksge::u8string_view{u8"abcde"}, 1) == bksge::static_u8string<N>::npos);

	return true;
}

GTEST_TEST(StaticU8StringTest, FindTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool RFindStringTest()
{
	bksge::static_u8string<N1> const s1 = u8"abcd abc ab";

	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"a"}) == 9);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"ab"}) == 9);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abc"}) == 5);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abcd"}) == 0);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abcde"}) == bksge::static_u8string<N1>::npos);

	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"a"}, 10) == 9);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"ab"}, 10) == 9);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abc"}, 10) == 5);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abcd"}, 10) == 0);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abcde"}, 10) == bksge::static_u8string<N1>::npos);

	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"a"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"ab"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abc"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abcd"}, 8) == 0);
	VERIFY(s1.rfind(bksge::static_u8string<N2>{u8"abcde"}, 8) == bksge::static_u8string<N1>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindCharPtrTest()
{
	bksge::static_u8string<N> const s1 = u8"abcd abc ab";

	VERIFY(s1.rfind(u8"a") == 9);
	VERIFY(s1.rfind(u8"ab") == 9);
	VERIFY(s1.rfind(u8"abc") == 5);
	VERIFY(s1.rfind(u8"abcd") == 0);
	VERIFY(s1.rfind(u8"abcde") == bksge::static_u8string<N>::npos);

	VERIFY(s1.rfind(u8"a", 6) == 5);
	VERIFY(s1.rfind(u8"ab", 6) == 5);
	VERIFY(s1.rfind(u8"abc", 6) == 5);
	VERIFY(s1.rfind(u8"abcd", 6) == 0);
	VERIFY(s1.rfind(u8"abcde", 6) == bksge::static_u8string<N>::npos);

	VERIFY(s1.rfind(u8"abcde", 7, 1) == 5);
	VERIFY(s1.rfind(u8"abcde", 7, 2) == 5);
	VERIFY(s1.rfind(u8"abcde", 7, 3) == 5);
	VERIFY(s1.rfind(u8"abcde", 7, 4) == 0);
	VERIFY(s1.rfind(u8"abcde", 7, 5) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindCharTest()
{
	bksge::static_u8string<N> const s1 = u8"abcd abc ab";

	VERIFY(s1.rfind('a') == 9);
	VERIFY(s1.rfind('b') == 10);
	VERIFY(s1.rfind('c') == 7);
	VERIFY(s1.rfind('d') == 3);
	VERIFY(s1.rfind('e') == bksge::static_u8string<N>::npos);

	VERIFY(s1.rfind('b', 10) == 10);
	VERIFY(s1.rfind('b', 9) == 6);
	VERIFY(s1.rfind('b', 5) == 1);
	VERIFY(s1.rfind('b', 0) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindStringViewTest()
{
	bksge::static_u8string<N> const s1 = u8"abcd abc ab";

	VERIFY(s1.rfind(bksge::u8string_view{u8"a"}) == 9);
	VERIFY(s1.rfind(bksge::u8string_view{u8"ab"}) == 9);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abc"}) == 5);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abcd"}) == 0);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abcde"}) == bksge::static_u8string<N>::npos);

	VERIFY(s1.rfind(bksge::u8string_view{u8"a"}, 10) == 9);
	VERIFY(s1.rfind(bksge::u8string_view{u8"ab"}, 10) == 9);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abc"}, 10) == 5);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abcd"}, 10) == 0);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abcde"}, 10) == bksge::static_u8string<N>::npos);

	VERIFY(s1.rfind(bksge::u8string_view{u8"a"}, 8) == 5);
	VERIFY(s1.rfind(bksge::u8string_view{u8"ab"}, 8) == 5);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abc"}, 8) == 5);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abcd"}, 8) == 0);
	VERIFY(s1.rfind(bksge::u8string_view{u8"abcde"}, 8) == bksge::static_u8string<N>::npos);

	return true;
}

GTEST_TEST(StaticU8StringTest, RFindTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfStringTest()
{
	bksge::static_u8string<N1> const s1 = u8"abcde abcde";

	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"a"}) == 0);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"b"}) == 1);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"c"}) == 2);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"d"}) == 3);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"e"}) == 4);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyz"}) == bksge::static_u8string<N1>::npos);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyze"}) == 4);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzed"}) == 3);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzedc"}) == 2);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzedcb"}) == 1);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzedcba"}) == 0);

	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyz"}, 2) == bksge::static_u8string<N1>::npos);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyze"}, 2) == 4);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzed"}, 2) == 3);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzedc"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzedcb"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::static_u8string<N2>{u8"xyzedcba"}, 2) == 2);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfCharPtrTest()
{
	bksge::static_u8string<N> const s1 = u8"abcde abcde";

	VERIFY(s1.find_first_of(u8"a") == 0);
	VERIFY(s1.find_first_of(u8"b") == 1);
	VERIFY(s1.find_first_of(u8"c") == 2);
	VERIFY(s1.find_first_of(u8"d") == 3);
	VERIFY(s1.find_first_of(u8"e") == 4);
	VERIFY(s1.find_first_of(u8"xyz") == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_of(u8"xyze") == 4);
	VERIFY(s1.find_first_of(u8"xyzed") == 3);
	VERIFY(s1.find_first_of(u8"xyzedc") == 2);
	VERIFY(s1.find_first_of(u8"xyzedcb") == 1);
	VERIFY(s1.find_first_of(u8"xyzedcba") == 0);

	VERIFY(s1.find_first_of(u8"xyz", 2) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_of(u8"xyze", 2) == 4);
	VERIFY(s1.find_first_of(u8"xyzed", 2) == 3);
	VERIFY(s1.find_first_of(u8"xyzedc", 2) == 2);
	VERIFY(s1.find_first_of(u8"xyzedcb", 2) == 2);
	VERIFY(s1.find_first_of(u8"xyzedcba", 2) == 2);

	VERIFY(s1.find_first_of(u8"xedcba", 1, 1) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_of(u8"xedcba", 1, 2) == 4);
	VERIFY(s1.find_first_of(u8"xedcba", 1, 3) == 3);
	VERIFY(s1.find_first_of(u8"xedcba", 1, 4) == 2);
	VERIFY(s1.find_first_of(u8"xedcba", 1, 5) == 1);
	VERIFY(s1.find_first_of(u8"xedcba", 1, 6) == 1);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfCharTest()
{
	bksge::static_u8string<N> const s1 = u8"ab abc abcd";

	VERIFY(s1.find_first_of('a') == 0);
	VERIFY(s1.find_first_of('b') == 1);
	VERIFY(s1.find_first_of('c') == 5);
	VERIFY(s1.find_first_of('d') == 10);
	VERIFY(s1.find_first_of('e') == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_first_of('a', 1) == 3);
	VERIFY(s1.find_first_of('a', 4) == 7);
	VERIFY(s1.find_first_of('a', 8) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfStringViewTest()
{
	bksge::static_u8string<N> const s1 = u8"abcde abcde";

	VERIFY(s1.find_first_of(bksge::u8string_view{u8"a"}) == 0);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"b"}) == 1);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"c"}) == 2);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"d"}) == 3);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"e"}) == 4);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyz"}) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyze"}) == 4);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzed"}) == 3);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzedc"}) == 2);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzedcb"}) == 1);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzedcba"}) == 0);

	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyz"}, 2) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyze"}, 2) == 4);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzed"}, 2) == 3);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzedc"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzedcb"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::u8string_view{u8"xyzedcba"}, 2) == 2);

	return true;
}

GTEST_TEST(StaticU8StringTest, FindFirstOfTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfStringTest()
{
	bksge::static_u8string<N1> const s1 = u8"abcde abcde";

	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"a"}) == 6);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"b"}) == 7);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"c"}) == 8);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"d"}) == 9);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"e"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyz"}) == bksge::static_u8string<N1>::npos);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyze"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzed"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzedc"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzedcb"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzedcba"}) == 10);

	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyz"}, 8) == bksge::static_u8string<N1>::npos);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyze"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzed"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzedc"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzedcb"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::static_u8string<N2>{u8"xyzedcba"}, 8) == 8);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfCharPtrTest()
{
	bksge::static_u8string<N> const s1 = u8"abcde abcde";

	VERIFY(s1.find_last_of(u8"a") == 6);
	VERIFY(s1.find_last_of(u8"b") == 7);
	VERIFY(s1.find_last_of(u8"c") == 8);
	VERIFY(s1.find_last_of(u8"d") == 9);
	VERIFY(s1.find_last_of(u8"e") == 10);
	VERIFY(s1.find_last_of(u8"xyz") == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_last_of(u8"xyze") == 10);
	VERIFY(s1.find_last_of(u8"xyzed") == 10);
	VERIFY(s1.find_last_of(u8"xyzedc") == 10);
	VERIFY(s1.find_last_of(u8"xyzedcb") == 10);
	VERIFY(s1.find_last_of(u8"xyzedcba") == 10);

	VERIFY(s1.find_last_of(u8"xyz", 8) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_last_of(u8"xyze", 8) == 4);
	VERIFY(s1.find_last_of(u8"xyzed", 8) == 4);
	VERIFY(s1.find_last_of(u8"xyzedc", 8) == 8);
	VERIFY(s1.find_last_of(u8"xyzedcb", 8) == 8);
	VERIFY(s1.find_last_of(u8"xyzedcba", 8) == 8);

	VERIFY(s1.find_last_of(u8"Xabcde", 8, 1) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_last_of(u8"Xabcde", 8, 2) == 6);
	VERIFY(s1.find_last_of(u8"Xabcde", 8, 3) == 7);
	VERIFY(s1.find_last_of(u8"Xabcde", 8, 4) == 8);
	VERIFY(s1.find_last_of(u8"Xabcde", 8, 5) == 8);
	VERIFY(s1.find_last_of(u8"Xabcde", 8, 6) == 8);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfCharTest()
{
	bksge::static_u8string<N> const s1 = u8"ab abc abcd";

	VERIFY(s1.find_last_of('a') == 7);
	VERIFY(s1.find_last_of('b') == 8);
	VERIFY(s1.find_last_of('c') == 9);
	VERIFY(s1.find_last_of('d') == 10);
	VERIFY(s1.find_last_of('e') == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_last_of('b', 8) == 8);
	VERIFY(s1.find_last_of('b', 7) == 4);
	VERIFY(s1.find_last_of('b', 4) == 4);
	VERIFY(s1.find_last_of('b', 3) == 1);
	VERIFY(s1.find_last_of('b', 1) == 1);
	VERIFY(s1.find_last_of('b', 0) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfStringViewTest()
{
	bksge::static_u8string<N> const s1 = u8"abcde abcde";

	VERIFY(s1.find_last_of(bksge::u8string_view{u8"a"}) == 6);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"b"}) == 7);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"c"}) == 8);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"d"}) == 9);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"e"}) == 10);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyz"}) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyze"}) == 10);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzed"}) == 10);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzedc"}) == 10);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzedcb"}) == 10);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzedcba"}) == 10);

	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyz"}, 8) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyze"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzed"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzedc"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzedcb"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::u8string_view{u8"xyzedcba"}, 8) == 8);

	return true;
}

GTEST_TEST(StaticU8StringTest, FindLastOfTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfStringTest()
{
	bksge::static_u8string<N1> const s1 = u8"abcde";

	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"a"}) == 1);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"b"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"c"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"d"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"e"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"ba"}) == 2);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"cba"}) == 3);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"dcba"}) == 4);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"edcba"}) == bksge::static_u8string<N1>::npos);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"xyzedcba"}) == bksge::static_u8string<N1>::npos);

	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"de"}, 1) == 1);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"de"}, 2) == 2);
	VERIFY(s1.find_first_not_of(bksge::static_u8string<N2>{u8"de"}, 3) == bksge::static_u8string<N1>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfCharPtrTest()
{
	bksge::static_u8string<N> const s1 = u8"abcde";

	VERIFY(s1.find_first_not_of(u8"a") == 1);
	VERIFY(s1.find_first_not_of(u8"b") == 0);
	VERIFY(s1.find_first_not_of(u8"c") == 0);
	VERIFY(s1.find_first_not_of(u8"d") == 0);
	VERIFY(s1.find_first_not_of(u8"e") == 0);
	VERIFY(s1.find_first_not_of(u8"ba") == 2);
	VERIFY(s1.find_first_not_of(u8"cba") == 3);
	VERIFY(s1.find_first_not_of(u8"dcba") == 4);
	VERIFY(s1.find_first_not_of(u8"edcba") == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_not_of(u8"xyzedcba") == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_first_not_of(u8"de", 1) == 1);
	VERIFY(s1.find_first_not_of(u8"de", 2) == 2);
	VERIFY(s1.find_first_not_of(u8"de", 3) == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_first_not_of(u8"abcde", 1, 1) == 1);
	VERIFY(s1.find_first_not_of(u8"abcde", 1, 2) == 2);
	VERIFY(s1.find_first_not_of(u8"abcde", 1, 3) == 3);
	VERIFY(s1.find_first_not_of(u8"abcde", 1, 4) == 4);
	VERIFY(s1.find_first_not_of(u8"abcde", 1, 5) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfCharTest()
{
	bksge::static_u8string<N> const s1 = u8"aaaabbbccd";

	VERIFY(s1.find_first_not_of('a') == 4);
	VERIFY(s1.find_first_not_of('b') == 0);
	VERIFY(s1.find_first_not_of('c') == 0);
	VERIFY(s1.find_first_not_of('d') == 0);
	VERIFY(s1.find_first_not_of('e') == 0);

	VERIFY(s1.find_first_not_of('b', 4) == 7);
	VERIFY(s1.find_first_not_of('b', 8) == 8);
	VERIFY(s1.find_first_not_of('b', 9) == 9);
	VERIFY(s1.find_first_not_of('b', 10) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_not_of('d', 4) == 4);
	VERIFY(s1.find_first_not_of('d', 8) == 8);
	VERIFY(s1.find_first_not_of('d', 9) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_not_of('d', 10) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfStringViewTest()
{
	bksge::static_u8string<N> const s1 = u8"abcde";

	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"a"}) == 1);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"b"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"c"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"d"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"e"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"ba"}) == 2);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"cba"}) == 3);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"dcba"}) == 4);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"edcba"}) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"xyzedcba"}) == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"de"}, 1) == 1);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"de"}, 2) == 2);
	VERIFY(s1.find_first_not_of(bksge::u8string_view{u8"de"}, 3) == bksge::static_u8string<N>::npos);

	return true;
}

GTEST_TEST(StaticU8StringTest, FindFirstNotOfTest)
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

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfStringTest()
{
	bksge::static_u8string<N1> const s1 = u8"ddddcccbba";

	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"a"}) == 8);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"b"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"c"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"d"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"e"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"ab"}) == 6);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"abc"}) == 3);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"abcd"}) == bksge::static_u8string<N1>::npos);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"abcde"}) == bksge::static_u8string<N1>::npos);

	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"cd"}, 8) == 8);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"cd"}, 7) == 7);
	VERIFY(s1.find_last_not_of(bksge::static_u8string<N2>{u8"cd"}, 6) == bksge::static_u8string<N1>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfCharPtrTest()
{
	bksge::static_u8string<N> const s1 = u8"ddddcccbba";

	VERIFY(s1.find_last_not_of(u8"a") == 8);
	VERIFY(s1.find_last_not_of(u8"b") == 9);
	VERIFY(s1.find_last_not_of(u8"c") == 9);
	VERIFY(s1.find_last_not_of(u8"d") == 9);
	VERIFY(s1.find_last_not_of(u8"e") == 9);
	VERIFY(s1.find_last_not_of(u8"ab") == 6);
	VERIFY(s1.find_last_not_of(u8"abc") == 3);
	VERIFY(s1.find_last_not_of(u8"abcd") == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_last_not_of(u8"abcde") == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_last_not_of(u8"cd", 8) == 8);
	VERIFY(s1.find_last_not_of(u8"cd", 7) == 7);
	VERIFY(s1.find_last_not_of(u8"cd", 6) == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_last_not_of(u8"abcde", 8, 1) == 8);
	VERIFY(s1.find_last_not_of(u8"abcde", 8, 2) == 6);
	VERIFY(s1.find_last_not_of(u8"abcde", 8, 3) == 3);
	VERIFY(s1.find_last_not_of(u8"abcde", 8, 4) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfCharTest()
{
	bksge::static_u8string<N> const s1 = u8"ddddcccbba";

	VERIFY(s1.find_last_not_of('a') == 8);
	VERIFY(s1.find_last_not_of('b') == 9);
	VERIFY(s1.find_last_not_of('c') == 9);
	VERIFY(s1.find_last_not_of('d') == 9);
	VERIFY(s1.find_last_not_of('e') == 9);

	VERIFY(s1.find_last_not_of('d', 5) == 5);
	VERIFY(s1.find_last_not_of('d', 4) == 4);
	VERIFY(s1.find_last_not_of('d', 3) == bksge::static_u8string<N>::npos);

	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfStringViewTest()
{
	bksge::static_u8string<N> const s1 = u8"ddddcccbba";

	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"a"}) == 8);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"b"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"c"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"d"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"e"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"ab"}) == 6);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"abc"}) == 3);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"abcd"}) == bksge::static_u8string<N>::npos);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"abcde"}) == bksge::static_u8string<N>::npos);

	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"cd"}, 8) == 8);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"cd"}, 7) == 7);
	VERIFY(s1.find_last_not_of(bksge::u8string_view{u8"cd"}, 6) == bksge::static_u8string<N>::npos);

	return true;
}

GTEST_TEST(StaticU8StringTest, FindLastNotOfTest)
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

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool SubstrTest()
{
	bksge::static_u8string<N> const s1 = u8"abcde";
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

	VERIFY(s2 == u8"abcde");
	VERIFY(s3 == u8"bcde");
	VERIFY(s4 == u8"cde");
	VERIFY(s5 == u8"b");
	VERIFY(s6 == u8"bc");
	VERIFY(s7 == u8"bcd");
	VERIFY(s8 == u8"c");
	VERIFY(s9 == u8"cd");
	VERIFY(s10 == u8"cde");
	VERIFY(s11 == u8"cde");

	return true;
}

GTEST_TEST(StaticU8StringTest, SubstrTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool StartsWithTest()
{
	bksge::static_u8string<N> const s = u8"abcde";

	VERIFY(s.starts_with(bksge::u8string_view{u8"abcde"})  == true);
	VERIFY(s.starts_with(bksge::u8string_view{u8"abc"})    == true);
	VERIFY(s.starts_with(bksge::u8string_view{u8"a"})      == true);
	VERIFY(s.starts_with(bksge::u8string_view{u8"abcdef"}) == false);
	VERIFY(s.starts_with(bksge::u8string_view{u8"abd"})    == false);
	VERIFY(s.starts_with(bksge::u8string_view{u8"bc"})     == false);

	VERIFY(s.starts_with('a') == true);
	VERIFY(s.starts_with('b') == false);
	VERIFY(s.starts_with('e') == false);

	VERIFY(s.starts_with(u8"abcde")  == true);
	VERIFY(s.starts_with(u8"abc")    == true);
	VERIFY(s.starts_with(u8"a")      == true);
	VERIFY(s.starts_with(u8"abcdef") == false);
	VERIFY(s.starts_with(u8"abd")    == false);
	VERIFY(s.starts_with(u8"bc")     == false);

	return true;
}

GTEST_TEST(StaticU8StringTest, StartsWithTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EndsWithTest()
{
	bksge::static_u8string<N> const s = u8"abcde";

	VERIFY(s.ends_with(bksge::u8string_view{u8"abcde"})  == true);
	VERIFY(s.ends_with(bksge::u8string_view{u8"cde"})    == true);
	VERIFY(s.ends_with(bksge::u8string_view{u8"e"})      == true);
	VERIFY(s.ends_with(bksge::u8string_view{u8"abcdef"}) == false);
	VERIFY(s.ends_with(bksge::u8string_view{u8"dde"})    == false);
	VERIFY(s.ends_with(bksge::u8string_view{u8"cdf"})    == false);
	VERIFY(s.ends_with(bksge::u8string_view{u8"cd"})     == false);

	VERIFY(s.ends_with('e') == true);
	VERIFY(s.ends_with('d') == false);
	VERIFY(s.ends_with('a') == false);

	VERIFY(s.ends_with(u8"abcde")  == true);
	VERIFY(s.ends_with(u8"cde")    == true);
	VERIFY(s.ends_with(u8"e")      == true);
	VERIFY(s.ends_with(u8"abcdef") == false);
	VERIFY(s.ends_with(u8"dde")    == false);
	VERIFY(s.ends_with(u8"cdf")    == false);
	VERIFY(s.ends_with(u8"cd")     == false);

	return true;
}

GTEST_TEST(StaticU8StringTest, EndsWithTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<100>());
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	{
		bksge::static_u8string<N> const s = u8"abc";
		auto p = s.data();
		VERIFY(p[0] == 'a');
		VERIFY(p[1] == 'b');
		VERIFY(p[2] == 'c');
		VERIFY(c_str_test(s, u8"abc"));
	}
	{
		bksge::static_u8string<N> s = u8"abc";
		auto p = s.data();
		VERIFY(p[0] == 'a');
		VERIFY(p[1] == 'b');
		VERIFY(p[2] == 'c');
		p[1] = 'X';
		VERIFY(c_str_test(s, u8"aXc"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<100>());
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	{
		bksge::static_u8string<N1> s1 = u8"abc";
		bksge::static_u8string<N2> s2 = u8"12345";
		s1.swap(s2);
		VERIFY(c_str_test(s1, u8"12345"));
		VERIFY(c_str_test(s2, u8"abc"));
	}
	{
		bksge::static_u8string<N1> s1 = u8"abcdefg";
		bksge::static_u8string<N2> s2 = u8"123";
		bksge::ranges::swap(s1, s2);
		VERIFY(c_str_test(s1, u8"123"));
		VERIFY(c_str_test(s2, u8"abcdefg"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<16, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<16, 24>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<32, 16>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<32, 32>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<100, 50>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SwapTest<100, 100>()));
}

template <bksge::size_t N1, bksge::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AddStringStringTest()
{
	{
		bksge::static_u8string<N1> const s1 = u8"abc";
		bksge::static_u8string<N2> const s2 = u8"12345";
		auto s3 = s1 + s2;
		VERIFY(c_str_test(s3, u8"abc12345"));
	}
	{
		bksge::static_u8string<N1> const s1 = u8"abc";
		bksge::static_u8string<N2> const s2 = u8"123";
		auto s3 = u8"xxx" + s1 + u8'y' + s2 + u8'z' + u8"AA";
		VERIFY(c_str_test(s3, u8"xxxabcy123zAA"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddStringCharPtrTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"abc";
		auto s2 = s1 + u8"defg";
		VERIFY(c_str_test(s2, u8"abcdefg"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddStringCharTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"abc";
		auto s2 = s1 + u8'1';
		VERIFY(c_str_test(s2, u8"abc1"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddCharPtrStringTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"abc";
		auto s2 = u8"defg" + s1;
		VERIFY(c_str_test(s2, u8"defgabc"));
	}
	return true;
}

template <bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddCharStringTest()
{
	{
		bksge::static_u8string<N> const s1 = u8"abc";
		auto s2 = u8'1' + s1;
		VERIFY(c_str_test(s2, u8"1abc"));
	}
	return true;
}

GTEST_TEST(StaticU8StringTest, AddTest)
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

#if 0
GTEST_TEST(StaticU8StringTest, InputStreamTest)
{
	{
		std::basic_stringstream<char8_t> ss(u8"abc");
		bksge::static_u8string<16> s;
		ss >> s;
		EXPECT_TRUE(s == u8"abc");
	}
	{
		std::basic_stringstream<char8_t> ss(u8"Hello World");
		bksge::static_u8string<32> s;
		ss >> s;
		EXPECT_TRUE(s == u8"Hello");
		ss >> s;
		EXPECT_TRUE(s == u8"World");
	}
}
#endif

GTEST_TEST(StaticU8StringTest, OutputStreamTest)
{
	{
		bksge::static_u8string<16> const s = u8"abc";
		std::basic_stringstream<char8_t> ss;
		ss << s;
		EXPECT_TRUE(ss.str() == u8"abc");
	}
	{
		bksge::static_u8string<32> const s = u8"Hello World";
		std::basic_stringstream<char8_t> ss;
		ss << s;
		EXPECT_TRUE(ss.str() == u8"Hello World");
	}
}

#undef VERIFY

#endif // defined(BKSGE_HAS_CXX20_CHAR8_T)

}	// namespace bksge_static_u8string_test
