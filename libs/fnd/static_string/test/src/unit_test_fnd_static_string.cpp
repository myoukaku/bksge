/**
 *	@file	unit_test_fnd_static_string.cpp
 *
 *	@brief	bksge::static_string のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/static_string/static_string.hpp>
#include <bksge/fnd/string_view/string_view.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <cstddef>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_static_string_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
c_str_test(bksge::static_string<N> const& s, char const* str)
{
	using traits_type = typename bksge::static_string<N>::traits_type;
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
		bksge::static_string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));
	}
	{
		bksge::static_string<N> s{};
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));
	}
	{
		bksge::static_string<N> s={};
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCountCharTest()
{
	{
		bksge::static_string<N> s(0, 'a');
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));
	}
	{
		bksge::static_string<N> s(1, 'a');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "a"));
	}
	{
		bksge::static_string<N> s(4, 'c');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "cccc"));
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorOtherPosTest()
{
	{
		bksge::static_string<N1> const s1("hello");
		bksge::static_string<N2> const s2(s1, 1);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 4);
		VERIFY(s2.length()   == 4);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, "ello"));
	}
	{
		bksge::static_string<N1> const s1("hello");
		bksge::static_string<N2> const s2{s1, 2};

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 3);
		VERIFY(s2.length()   == 3);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, "llo"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorOtherPosCountTest()
{
	{
		bksge::static_string<N1> const s1("hello");
		bksge::static_string<N2> const s2(s1, 1, 3);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 3);
		VERIFY(s2.length()   == 3);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, "ell"));
	}
	{
		bksge::static_string<N1> const s1("hello");
		bksge::static_string<N2> const s2{s1, 2, 2};

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "hello"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 2);
		VERIFY(s2.length()   == 2);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, "ll"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrCountTest()
{
	{
		bksge::static_string<N> s("abcde", 4);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abcd"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrTest()
{
	{
		bksge::static_string<N> s("abcde");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abcde"));
	}
	{
		bksge::static_string<N> s{"hello world!"};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 12);
		VERIFY(s.length()   == 12);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "hello world!"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorIteratorTest()
{
	{
		char const buf[] = "abcde";
		bksge::static_string<N> const s(buf, buf + 3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abc"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorCopyTest()
{
	{
		bksge::static_string<N1> const s1("hello world");
		bksge::static_string<N2> const s2(s1);

		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "hello world"));

		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 11);
		VERIFY(s2.length()   == 11);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, "hello world"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CtorMoveTest()
{
	{
		bksge::static_string<N1> s1("hello world");
		bksge::static_string<N2> const s2(std::move(s1));
		VERIFY(!s2.empty());
		VERIFY(s2.size()     == 11);
		VERIFY(s2.length()   == 11);
		VERIFY(s2.max_size() == N2);
		VERIFY(s2.capacity() == N2);
		VERIFY(c_str_test(s2, "hello world"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorInitializerListTest()
{
	{
		bksge::static_string<N> s{'h', 'e', 'l', 'l', 'o'};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "hello"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringViewTest()
{
	{
		bksge::static_string<N> s(bksge::string_view{"Hello World"});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "Hello World"));
	}
	{
		bksge::static_string<N> s("Hello World");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "Hello World"));
	}
	{
		bksge::static_string<N> s(bksge::string_view{"Hello World"}, 2, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "llo W"));
	}
	{
		bksge::static_string<N> s("Hello World", 2, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "llo W"));
	}
	{
		bksge::static_string<N> s(bksge::string_view{"Hello World"}, 2, 100);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 9);
		VERIFY(s.length()   == 9);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "llo World"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, CtorTest)
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
		bksge::static_string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_string<N2> const s2("hello world");
		s1 = s2;
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "hello world"));

		bksge::static_string<N2> const s3("abc");
		s1.assign(s3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "abc"));

		bksge::static_string<N2> const s4("Hello World");
		s1.assign(s4, 3, 4);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 4);
		VERIFY(s1.length()   == 4);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "lo W"));

		s1.assign(s4, 3, 100);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "lo World"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringMoveTest()
{
	{
		bksge::static_string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_string<N2> s2("hello world");
		s1 = std::move(s2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "hello world"));

		bksge::static_string<N2> s3("abc");
		s1.assign(std::move(s3));
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "abc"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharPtrTest()
{
	{
		bksge::static_string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));

		s = "hoge";
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "hoge"));

		s.assign("a");
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "a"));

		s.assign("world", 3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "wor"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharTest()
{
	{
		bksge::static_string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));

		s = 'A';
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "A"));

		s.assign(2, 'B');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 2);
		VERIFY(s.length()   == 2);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "BB"));

		s = 'C';
		VERIFY(!s.empty());
		VERIFY(s.size()     == 1);
		VERIFY(s.length()   == 1);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "C"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignIteratorTest()
{
	{
		bksge::static_string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));

		char buf[] = "hello";

		s.assign(buf, buf+5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "hello"));

		s.assign(buf, buf+3);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "hel"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignInitializerListTest()
{
	{
		bksge::static_string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));

		s = {'h', 'e', 'l', 'l', 'o'};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "hello"));

		s.assign({'a', 'b', 'c', 'd'});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abcd"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringViewTest()
{
	{
		bksge::static_string<N> s;
		VERIFY(s.empty());
		VERIFY(s.size()     == 0);
		VERIFY(s.length()   == 0);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, ""));

		s = bksge::string_view{"Hello World"};
		VERIFY(!s.empty());
		VERIFY(s.size()     == 11);
		VERIFY(s.length()   == 11);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "Hello World"));

		s.assign(bksge::string_view{"abc"});
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abc"));

		s.assign(bksge::string_view{"Hello World"}, 1, 5);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "ello "));

		s.assign("Hello World", 2, 6);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 6);
		VERIFY(s.length()   == 6);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "llo Wo"));

		s.assign(bksge::string_view{"Hello World"}, 2, 100);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 9);
		VERIFY(s.length()   == 9);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "llo World"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, AssignTest)
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
		bksge::static_string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_string<N2> const s2 = "abc";
		s1 += s2;
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "abc"));

		bksge::static_string<N2> const s3 = "hello";
		s1.append(s3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "abchello"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringPosTest()
{
	{
		bksge::static_string<N1> s1;
		VERIFY(s1.empty());

		bksge::static_string<N2> const s2 = "abc";
		s1.append(s2, 1);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "bc"));

		bksge::static_string<N2> const s3 = "hello";
		s1.append(s3, 2, 3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "bcllo"));

		bksge::static_string<N2> const s4 = "world";
		s1.append(s4, 1, 10);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 9);
		VERIFY(s1.length()   == 9);
		VERIFY(s1.max_size() == N1);
		VERIFY(s1.capacity() == N1);
		VERIFY(c_str_test(s1, "bclloorld"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharPtrTest()
{
	{
		bksge::static_string<N> s1;
		VERIFY(s1.empty());

		s1 += "hello";
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "hello"));

		s1.append(" world");
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "hello world"));

		s1.append("ABCDE", 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 13);
		VERIFY(s1.length()   == 13);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "hello worldAB"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharTest()
{
	{
		bksge::static_string<N> s1;
		VERIFY(s1.empty());

		s1 += 'A';
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "A"));

		s1.append(3, 'B');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 4);
		VERIFY(s1.length()   == 4);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "ABBB"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendInitializerListTest()
{
	{
		bksge::static_string<N> s1;
		VERIFY(s1.empty());

		s1 += { 'A', 'B', 'C' };
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "ABC"));

		s1.append({ 'h', 'e', 'l', 'l', 'o' });
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "ABChello"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendIteratorTest()
{
	{
		bksge::static_string<N> s1;
		VERIFY(s1.empty());

		char buf[] = "hello";

		s1.append(buf, buf+5);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "hello"));

		s1.append(buf+1, buf+3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 7);
		VERIFY(s1.length()   == 7);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "helloel"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringViewTest()
{
	{
		bksge::static_string<N> s1;
		VERIFY(s1.empty());

		s1 += bksge::string_view{"Hel"};
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "Hel"));

		s1.append(bksge::string_view{"lo"});
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 5);
		VERIFY(s1.length()   == 5);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "Hello"));

		s1.append(bksge::string_view{"abcde"}, 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 8);
		VERIFY(s1.length()   == 8);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "Hellocde"));

		s1.append(bksge::string_view{"ABCDE"}, 1, 3);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 11);
		VERIFY(s1.length()   == 11);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "HellocdeBCD"));

		s1.append("ABCDE", 2, 2);
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 13);
		VERIFY(s1.length()   == 13);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "HellocdeBCDCD"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, AppendTest)
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
		bksge::static_string<N1> s1 = "aaa";
		bksge::static_string<N2> s2 = "bbb";
		s1.insert(2, s2);
		VERIFY(c_str_test(s1, "aabbba"));
	}

	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringPosTest()
{
	{
		bksge::static_string<N1> s1 = "aaa";
		bksge::static_string<N2> s2 = "12345";
		s1.insert(2, s2, 2, 3);
		VERIFY(c_str_test(s1, "aa345a"));
	}
	{
		bksge::static_string<N1> s1 = "aaa";
		bksge::static_string<N2> s2 = "12345";
		s1.insert(3, s2, 1);
		VERIFY(c_str_test(s1, "aaa2345"));
	}
	{
		bksge::static_string<N1> s1 = "aaa";
		bksge::static_string<N2> s2 = "12345";
		s1.insert(1, s2, 1, 100);
		VERIFY(c_str_test(s1, "a2345aa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharPtrCountTest()
{
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(2, "12345", 2);
		VERIFY(c_str_test(s1, "aa12a"));
	}
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(2, "12345", 0);
		VERIFY(c_str_test(s1, "aaa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharPtrTest()
{
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(1, "12345");
		VERIFY(c_str_test(s1, "a12345aa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertCharTest()
{
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(2, 3, 'b');
		VERIFY(c_str_test(s1, "aabbba"));
	}
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(2, 0, 'b');
		VERIFY(c_str_test(s1, "aaa"));
	}

	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(s1.begin(), 'b');
		VERIFY(c_str_test(s1, "baaa"));
	}
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(s1.end(), 'c');
		VERIFY(c_str_test(s1, "aaac"));
	}

	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(s1.begin(), 2, 'b');
		VERIFY(c_str_test(s1, "bbaaa"));
	}
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(s1.end(), 3, 'c');
		VERIFY(c_str_test(s1, "aaaccc"));
	}
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(s1.end(), 0, 'c');
		VERIFY(c_str_test(s1, "aaa"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertIteratorTest()
{
	{
		bksge::static_string<N> s1 = "aaa";
		char buf[] = "xyz";
		s1.insert(s1.begin(), buf, buf+3);
		VERIFY(c_str_test(s1, "xyzaaa"));
	}
	{
		bksge::static_string<N> s1 = "aaa";
		char buf[] = "xyz";
		s1.insert(s1.end(), buf, buf+3);
		VERIFY(c_str_test(s1, "aaaxyz"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertInitializerListTest()
{
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(s1.begin()+1, {'1', '2', '3', '4', '5'});
		VERIFY(c_str_test(s1, "a12345aa"));
	}
	{
		bksge::static_string<N> s1 = "aaa";
		s1.insert(s1.end(), {'b', 'c'});
		VERIFY(c_str_test(s1, "aaabc"));
	}

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool InsertStringViewTest()
{
	{
		bksge::static_string<N> s1 = "abcde";
		s1.insert(0, bksge::string_view{"xyz"});
		VERIFY(c_str_test(s1, "xyzabcde"));
	}
	{
		bksge::static_string<N> s1 = "abcde";
		s1.insert(1, bksge::string_view{"12345"}, 1);
		VERIFY(c_str_test(s1, "a2345bcde"));
	}
	{
		bksge::static_string<N> s1 = "abcde";
		s1.insert(2, bksge::string_view{"12345"}, 2, 3);
		VERIFY(c_str_test(s1, "ab345cde"));
	}
	{
		bksge::static_string<N> s1 = "abcde";
		s1.insert(2, bksge::string_view{"12345"}, 2, 4);
		VERIFY(c_str_test(s1, "ab345cde"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, InsertTest)
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
		bksge::static_string<N> s1 = "12345";
		s1.erase(1, 2);
		VERIFY(c_str_test(s1, "145"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.erase(2);
		VERIFY(c_str_test(s1, "12"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.erase();
		VERIFY(c_str_test(s1, ""));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EraseIteratorTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.erase(s1.begin());
		VERIFY(c_str_test(s1, "2345"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.erase(s1.begin()+1);
		VERIFY(c_str_test(s1, "1345"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EraseFirstLastTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.erase(s1.begin(), s1.begin()+2);
		VERIFY(c_str_test(s1, "345"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.erase(s1.begin()+2, s1.end());
		VERIFY(c_str_test(s1, "12"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, EraseTest)
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
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "abcde";
		s1.replace(1, 2, s2);
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "abcde";
		s1.replace(2, 100, s2);
		VERIFY(c_str_test(s1, "12abcde"));
	}
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "a";
		s1.replace(1, 2, s2);
		VERIFY(c_str_test(s1, "1a45"));
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringPosCountTest()
{
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "abcde";
		s1.replace(1, 2, s2, 2, 3);
		VERIFY(c_str_test(s1, "1cde45"));
	}
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "abcde";
		s1.replace(2, 1, s2, 1);
		VERIFY(c_str_test(s1, "12bcde45"));
	}
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "abcde";
		s1.replace(1, 2, s2, 2, 1);
		VERIFY(c_str_test(s1, "1c45"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrCountTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 2, "abcde", 3);
		VERIFY(c_str_test(s1, "1abc45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(2, 100, "abcde", 2);
		VERIFY(c_str_test(s1, "12ab"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 2, "abcde");
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(2, 100, "abcde");
		VERIFY(c_str_test(s1, "12abcde"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 3, "z");
		VERIFY(c_str_test(s1, "1z5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCountCharTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 2, 3, 'x');
		VERIFY(c_str_test(s1, "1xxx45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(2, 100, 4, 'y');
		VERIFY(c_str_test(s1, "12yyyy"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 3, 1, 'z');
		VERIFY(c_str_test(s1, "1z5"));
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorStringTest()
{
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2);
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "abcde";
		s1.replace(s1.begin(), s1.end(), s2);
		VERIFY(c_str_test(s1, "abcde"));
	}
	{
		bksge::static_string<N1> s1 = "12345";
		bksge::static_string<N2> s2 = "xy";
		s1.replace(s1.begin() + 1, s1.begin() + 4, s2);
		VERIFY(c_str_test(s1, "1xy5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCharPtrCountTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, "abcde", 3);
		VERIFY(c_str_test(s1, "1abc45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin(), s1.end(), "abcde", 2);
		VERIFY(c_str_test(s1, "ab"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCharPtrTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, "abcde");
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin(), s1.end(), "abcde");
		VERIFY(c_str_test(s1, "abcde"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin() + 1, s1.begin() + 4, "xy");
		VERIFY(c_str_test(s1, "1xy5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorCountCharTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, 3, 'x');
		VERIFY(c_str_test(s1, "1xxx45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin(), s1.end(), 2, 'y');
		VERIFY(c_str_test(s1, "yy"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorIteratorTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		bksge::static_string<N> s2 = "abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2.begin(), s2.end());
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		bksge::static_string<N> s2 = "abcde";
		s1.replace(s1.begin(), s1.end(), s2.begin(), s2.end());
		VERIFY(c_str_test(s1, "abcde"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		bksge::static_string<N> s2 = "abcde";
		s1.replace(s1.begin() + 1, s1.begin() + 3, s2.begin(), s2.begin()+1);
		VERIFY(c_str_test(s1, "1a45"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorInitializerListTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, {'a', 'b', 'c', 'd', 'e'});
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin(), s1.end(), {'a', 'b', 'c', 'd'});
		VERIFY(c_str_test(s1, "abcd"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 2, bksge::string_view{"abcde"});
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 100, bksge::string_view{"abcde"});
		VERIFY(c_str_test(s1, "1abcde"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 3, bksge::string_view{"A"});
		VERIFY(c_str_test(s1, "1A5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewPosCountTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 2, bksge::string_view{"XXXabcdeYYY"}, 3, 5);
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(2, 2, bksge::string_view{"XXXabcdeYYY"}, 3);
		VERIFY(c_str_test(s1, "12abcdeYYY5"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(2, 1, "abcde", 2, 3);
		VERIFY(c_str_test(s1, "12cde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(1, 3, "abcde", 2, 1);
		VERIFY(c_str_test(s1, "1c5"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceIteratorStringViewTest()
{
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin() + 1, s1.begin() + 3, bksge::string_view{"abcde"});
		VERIFY(c_str_test(s1, "1abcde45"));
	}
	{
		bksge::static_string<N> s1 = "12345";
		s1.replace(s1.begin(), s1.end(), bksge::string_view{"abc"});
		VERIFY(c_str_test(s1, "abc"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, ReplaceTest)
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
	bksge::static_string<N> const s = "hello";
	using traits_type = typename bksge::static_string<N>::traits_type;
	{
		char result[5 + 1] ={};
		auto ret = s.copy(result, 5);
		VERIFY(traits_type::compare(result, "hello", 5) == 0);
		VERIFY(ret == 5);
	}
	{
		char result[3 + 1] ={};
		auto ret = s.copy(result, 3);
		VERIFY(traits_type::compare(result, "hel", 3) == 0);
		VERIFY(ret == 3);
	}
	{
		char result[3 + 1] ={};
		auto ret = s.copy(result, 3, 2);
		VERIFY(traits_type::compare(result, "llo", 3) == 0);
		VERIFY(ret == 3);
	}
	{
		char result[5 + 1] ={};
		auto ret = s.copy(result, 100, 1);
		VERIFY(traits_type::compare(result, "ello", 4) == 0);
		VERIFY(ret == 4);
	}
	return true;
}

GTEST_TEST(StaticStringTest, CopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool PushBackTest()
{
	{
		bksge::static_string<N> s1;
		VERIFY(s1.empty());

		s1.push_back('a');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "a"));

		s1.push_back('b');
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "ab"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, PushBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PushBackTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool PopBackTest()
{
	{
		bksge::static_string<N> s1 = "abc";
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 3);
		VERIFY(s1.length()   == 3);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "abc"));

		s1.pop_back();
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 2);
		VERIFY(s1.length()   == 2);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "ab"));

		s1.pop_back();
		VERIFY(!s1.empty());
		VERIFY(s1.size()     == 1);
		VERIFY(s1.length()   == 1);
		VERIFY(s1.max_size() == N);
		VERIFY(s1.capacity() == N);
		VERIFY(c_str_test(s1, "a"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, PopBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PopBackTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool BeginEndTest()
{
	{
		bksge::static_string<N> s = "abc";
		auto it = s.begin();
		VERIFY(*it == 'a');
		*it++ = 'X';
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.end());
		++it;
		VERIFY(it == s.end());
		VERIFY(c_str_test(s, "Xbc"));
	}
	{
		bksge::static_string<N> const s = "abc";
		auto it = s.begin();
		VERIFY(*it++ == 'a');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.end());
		++it;
		VERIFY(it == s.end());
		VERIFY(c_str_test(s, "abc"));
	}
	{
		bksge::static_string<N> s = "abc";
		auto it = s.cbegin();
		VERIFY(*it++ == 'a');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'c');
		VERIFY(it != s.cend());
		++it;
		VERIFY(it == s.cend());
		VERIFY(c_str_test(s, "abc"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, BeginEndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RBeginREndTest()
{
	{
		bksge::static_string<N> s = "abc";
		auto it = s.rbegin();
		VERIFY(*it == 'c');
		*it++ = 'X';
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.rend());
		++it;
		VERIFY(it == s.rend());
		VERIFY(c_str_test(s, "abX"));
	}
	{
		bksge::static_string<N> const s = "abc";
		auto it = s.rbegin();
		VERIFY(*it++ == 'c');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.rend());
		++it;
		VERIFY(it == s.rend());
		VERIFY(c_str_test(s, "abc"));
	}
	{
		bksge::static_string<N> s = "abc";
		auto it = s.crbegin();
		VERIFY(*it++ == 'c');
		VERIFY(*it == 'b');
		++it;
		VERIFY(*it == 'a');
		VERIFY(it != s.crend());
		++it;
		VERIFY(it == s.crend());
		VERIFY(c_str_test(s, "abc"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, RBeginREndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ResizeTest()
{
	{
		bksge::static_string<N> s = "abc";
		VERIFY(!s.empty());
		VERIFY(s.size()     == 3);
		VERIFY(s.length()   == 3);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abc"));
		s.resize(5, 'X');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 5);
		VERIFY(s.length()   == 5);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abcXX"));
		s.resize(4, 'Y');
		VERIFY(!s.empty());
		VERIFY(s.size()     == 4);
		VERIFY(s.length()   == 4);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "abcX"));
		s.resize(6);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 6);
		VERIFY(s.length()   == 6);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		//VERIFY(s.compare("abcX") == 0);
		s.resize(2);
		VERIFY(!s.empty());
		VERIFY(s.size()     == 2);
		VERIFY(s.length()   == 2);
		VERIFY(s.max_size() == N);
		VERIFY(s.capacity() == N);
		VERIFY(c_str_test(s, "ab"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, ResizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ResizeTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ReserveTest()
{
	{
		bksge::static_string<N> s = "abc";
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

GTEST_TEST(StaticStringTest, ReserveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReserveTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ClearTest()
{
	{
		bksge::static_string<N> s = "abc";
		VERIFY(!s.empty());
		VERIFY(c_str_test(s, "abc"));

		s.clear();
		VERIFY(s.empty());
		VERIFY(c_str_test(s, ""));
	}

	return true;
}

GTEST_TEST(StaticStringTest, ClearTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ClearTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool BraceTest()
{
	{
		bksge::static_string<N> const s = "abc";
		VERIFY(s[0] == 'a');
		VERIFY(s[1] == 'b');
		VERIFY(s[2] == 'c');
	}
	{
		bksge::static_string<N> s = "abc";
		s[1] = 'Z';
		VERIFY(c_str_test(s, "aZc"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, BraceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BraceTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	{
		bksge::static_string<N> const s = "abc";
		VERIFY(s.at(0) == 'a');
		VERIFY(s.at(1) == 'b');
		VERIFY(s.at(2) == 'c');
	}
	{
		bksge::static_string<N> s = "abc";
		s.at(1) = 'Z';
		VERIFY(c_str_test(s, "aZc"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FrontBackTest()
{
	{
		bksge::static_string<N> const s = "abc";
		VERIFY(s.front() == 'a');
		VERIFY(s.back()  == 'c');
	}
	{
		bksge::static_string<N> s = "abc";
		s.front() = 'X';
		s.back()  = 'Y';
		VERIFY(c_str_test(s, "XbY"));
	}

	return true;
}

GTEST_TEST(StaticStringTest, FrontBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool CompareStringTest()
{
	{
		bksge::static_string<N1> const s1 = "12345";
		bksge::static_string<N2> const s2 = "12345";
		bksge::static_string<N2> const s3 = "123456";
		bksge::static_string<N2> const s4 = "1234";
		bksge::static_string<N2> const s5 = "12346";
		bksge::static_string<N2> const s6 = "12344";

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
		bksge::static_string<N1> const s1 = "123456";
		bksge::static_string<N2> const s2 = "12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", "12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringPosCountTest()
{
	{
		bksge::static_string<N1> const s1 = "12345";
		bksge::static_string<N2> const s2 = "123456";

		VERIFY(s1.compare(0, 5, s2, 0, 5) == 0);	// "12345", "12345"
		VERIFY(s1.compare(0, 6, s2, 0)    < 0);		// "12345", "123456"
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
		bksge::static_string<N> const s1 = "12345";
		char const* s2 = "12345";
		char const* s3 = "123456";
		char const* s4 = "1234";
		char const* s5 = "12346";
		char const* s6 = "12344";

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
		bksge::static_string<N> const s1 = "123456";
		char const* s2 = "12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", "12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountCharPtrCountTest()
{
	{
		bksge::static_string<N> const s1 = "12345";
		char const* s2 = "123456";

		VERIFY(s1.compare(0, 5, s2, 5) == 0);	// "12345", "12345"
		VERIFY(s1.compare(0, 5, s2, 9) < 0);	// "12345", "123456"
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
		bksge::static_string<N> const s1 = "12345";
		bksge::string_view const s2 = "12345";
		bksge::string_view const s3 = "123456";
		bksge::string_view const s4 = "1234";
		bksge::string_view const s5 = "12346";
		bksge::string_view const s6 = "12344";

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
		bksge::static_string<N> const s1 = "123456";
		bksge::string_view const s2 = "12345";

		VERIFY(s1.compare(0, 5, s2) == 0);	// "12345",  "12345"
		VERIFY(s1.compare(0, 9, s2) > 0);	// "123456", "12345"
		VERIFY(s1.compare(1, 5, s2) > 0);	// "23456",  "12345"
		VERIFY(s1.compare(0, 4, s2) < 0);	// "1234",   "12345"
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringViewPosCountTest()
{
	{
		bksge::static_string<N> const s1 = "12345";
		bksge::string_view const s2 = "123456";

		VERIFY(s1.compare(0, 5, s2, 0, 5) == 0);	// "12345", "12345"
		VERIFY(s1.compare(0, 6, s2, 0)    < 0);		// "12345", "123456"
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
		bksge::static_string<N1> const s1 = "abc";
		bksge::static_string<N2> const s2 = "abc";
		bksge::static_string<N2> const s3 = "abcd";
		bksge::static_string<N2> const s4 = "ab";
		bksge::static_string<N2> const s5 = "abe";
		bksge::static_string<N2> const s6 = "aba";

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

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY(bksge::is_eq(s1 <=> s1));
		VERIFY(bksge::is_eq(s1 <=> s2));
		VERIFY(bksge::is_lt(s1 <=> s3));
		VERIFY(bksge::is_gt(s1 <=> s4));
		VERIFY(bksge::is_lt(s1 <=> s5));
		VERIFY(bksge::is_gt(s1 <=> s6));
#endif
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool CompareOperatorCharPtrTest()
{
	{
		bksge::static_string<N> const s1 = "abc";
		char const* s2 = "abc";
		char const* s3 = "abcd";
		char const* s4 = "ab";
		char const* s5 = "abe";
		char const* s6 = "aba";

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

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY(bksge::is_eq(s1 <=> s1));
		VERIFY(bksge::is_eq(s1 <=> s2));
		VERIFY(bksge::is_lt(s1 <=> s3));
		VERIFY(bksge::is_gt(s1 <=> s4));
		VERIFY(bksge::is_lt(s1 <=> s5));
		VERIFY(bksge::is_gt(s1 <=> s6));
#endif
	}
	return true;
}

GTEST_TEST(StaticStringTest, CompareTest)
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
	bksge::static_string<N1> const s1 = "ab abc abcd";

	VERIFY(s1.find(bksge::static_string<N2>{"a"}) == 0);
	VERIFY(s1.find(bksge::static_string<N2>{"ab"}) == 0);
	VERIFY(s1.find(bksge::static_string<N2>{"abc"}) == 3);
	VERIFY(s1.find(bksge::static_string<N2>{"abcd"}) == 7);
	VERIFY(s1.find(bksge::static_string<N2>{"abcde"}) == bksge::static_string<N1>::npos);

	VERIFY(s1.find(bksge::static_string<N2>{"a"}, 1) == 3);
	VERIFY(s1.find(bksge::static_string<N2>{"ab"}, 1) == 3);
	VERIFY(s1.find(bksge::static_string<N2>{"abc"}, 1) == 3);
	VERIFY(s1.find(bksge::static_string<N2>{"abcd"}, 1) == 7);
	VERIFY(s1.find(bksge::static_string<N2>{"abcde"}, 1) == bksge::static_string<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindCharPtrTest()
{
	bksge::static_string<N> const s1 = "ab abc abcd";

	VERIFY(s1.find("a") == 0);
	VERIFY(s1.find("ab") == 0);
	VERIFY(s1.find("abc") == 3);
	VERIFY(s1.find("abcd") == 7);
	VERIFY(s1.find("abcde") == bksge::static_string<N>::npos);

	VERIFY(s1.find("a", 1) == 3);
	VERIFY(s1.find("ab", 1) == 3);
	VERIFY(s1.find("abc", 1) == 3);
	VERIFY(s1.find("abcd", 1) == 7);
	VERIFY(s1.find("abcde", 1) == bksge::static_string<N>::npos);

	VERIFY(s1.find("abcde", 1, 1) == 3);
	VERIFY(s1.find("abcde", 1, 2) == 3);
	VERIFY(s1.find("abcde", 1, 3) == 3);
	VERIFY(s1.find("abcde", 1, 4) == 7);
	VERIFY(s1.find("abcde", 1, 5) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindCharTest()
{
	bksge::static_string<N> const s1 = "ab abc abcd";

	VERIFY(s1.find('a') == 0);
	VERIFY(s1.find('b') == 1);
	VERIFY(s1.find('c') == 5);
	VERIFY(s1.find('d') == 10);
	VERIFY(s1.find('e') == bksge::static_string<N>::npos);

	VERIFY(s1.find('a', 1) == 3);
	VERIFY(s1.find('a', 4) == 7);
	VERIFY(s1.find('a', 8) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindStringViewTest()
{
	bksge::static_string<N> const s1 = "ab abc abcd";

	VERIFY(s1.find(bksge::string_view{"a"}) == 0);
	VERIFY(s1.find(bksge::string_view{"ab"}) == 0);
	VERIFY(s1.find(bksge::string_view{"abc"}) == 3);
	VERIFY(s1.find(bksge::string_view{"abcd"}) == 7);
	VERIFY(s1.find(bksge::string_view{"abcde"}) == bksge::static_string<N>::npos);

	VERIFY(s1.find(bksge::string_view{"a"}, 1) == 3);
	VERIFY(s1.find(bksge::string_view{"ab"}, 1) == 3);
	VERIFY(s1.find(bksge::string_view{"abc"}, 1) == 3);
	VERIFY(s1.find(bksge::string_view{"abcd"}, 1) == 7);
	VERIFY(s1.find(bksge::string_view{"abcde"}, 1) == bksge::static_string<N>::npos);

	return true;
}

GTEST_TEST(StaticStringTest, FindTest)
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
	bksge::static_string<N1> const s1 = "abcd abc ab";

	VERIFY(s1.rfind(bksge::static_string<N2>{"a"}) == 9);
	VERIFY(s1.rfind(bksge::static_string<N2>{"ab"}) == 9);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abc"}) == 5);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abcd"}) == 0);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abcde"}) == bksge::static_string<N1>::npos);

	VERIFY(s1.rfind(bksge::static_string<N2>{"a"}, 10) == 9);
	VERIFY(s1.rfind(bksge::static_string<N2>{"ab"}, 10) == 9);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abc"}, 10) == 5);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abcd"}, 10) == 0);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abcde"}, 10) == bksge::static_string<N1>::npos);

	VERIFY(s1.rfind(bksge::static_string<N2>{"a"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_string<N2>{"ab"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abc"}, 8) == 5);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abcd"}, 8) == 0);
	VERIFY(s1.rfind(bksge::static_string<N2>{"abcde"}, 8) == bksge::static_string<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindCharPtrTest()
{
	bksge::static_string<N> const s1 = "abcd abc ab";

	VERIFY(s1.rfind("a") == 9);
	VERIFY(s1.rfind("ab") == 9);
	VERIFY(s1.rfind("abc") == 5);
	VERIFY(s1.rfind("abcd") == 0);
	VERIFY(s1.rfind("abcde") == bksge::static_string<N>::npos);

	VERIFY(s1.rfind("a", 6) == 5);
	VERIFY(s1.rfind("ab", 6) == 5);
	VERIFY(s1.rfind("abc", 6) == 5);
	VERIFY(s1.rfind("abcd", 6) == 0);
	VERIFY(s1.rfind("abcde", 6) == bksge::static_string<N>::npos);

	VERIFY(s1.rfind("abcde", 7, 1) == 5);
	VERIFY(s1.rfind("abcde", 7, 2) == 5);
	VERIFY(s1.rfind("abcde", 7, 3) == 5);
	VERIFY(s1.rfind("abcde", 7, 4) == 0);
	VERIFY(s1.rfind("abcde", 7, 5) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindCharTest()
{
	bksge::static_string<N> const s1 = "abcd abc ab";

	VERIFY(s1.rfind('a') == 9);
	VERIFY(s1.rfind('b') == 10);
	VERIFY(s1.rfind('c') == 7);
	VERIFY(s1.rfind('d') == 3);
	VERIFY(s1.rfind('e') == bksge::static_string<N>::npos);

	VERIFY(s1.rfind('b', 10) == 10);
	VERIFY(s1.rfind('b', 9) == 6);
	VERIFY(s1.rfind('b', 5) == 1);
	VERIFY(s1.rfind('b', 0) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool RFindStringViewTest()
{
	bksge::static_string<N> const s1 = "abcd abc ab";

	VERIFY(s1.rfind(bksge::string_view{"a"}) == 9);
	VERIFY(s1.rfind(bksge::string_view{"ab"}) == 9);
	VERIFY(s1.rfind(bksge::string_view{"abc"}) == 5);
	VERIFY(s1.rfind(bksge::string_view{"abcd"}) == 0);
	VERIFY(s1.rfind(bksge::string_view{"abcde"}) == bksge::static_string<N>::npos);

	VERIFY(s1.rfind(bksge::string_view{"a"}, 10) == 9);
	VERIFY(s1.rfind(bksge::string_view{"ab"}, 10) == 9);
	VERIFY(s1.rfind(bksge::string_view{"abc"}, 10) == 5);
	VERIFY(s1.rfind(bksge::string_view{"abcd"}, 10) == 0);
	VERIFY(s1.rfind(bksge::string_view{"abcde"}, 10) == bksge::static_string<N>::npos);

	VERIFY(s1.rfind(bksge::string_view{"a"}, 8) == 5);
	VERIFY(s1.rfind(bksge::string_view{"ab"}, 8) == 5);
	VERIFY(s1.rfind(bksge::string_view{"abc"}, 8) == 5);
	VERIFY(s1.rfind(bksge::string_view{"abcd"}, 8) == 0);
	VERIFY(s1.rfind(bksge::string_view{"abcde"}, 8) == bksge::static_string<N>::npos);

	return true;
}

GTEST_TEST(StaticStringTest, RFindTest)
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
	bksge::static_string<N1> const s1 = "abcde abcde";

	VERIFY(s1.find_first_of(bksge::static_string<N2>{"a"}) == 0);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"b"}) == 1);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"c"}) == 2);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"d"}) == 3);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"e"}) == 4);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyz"}) == bksge::static_string<N1>::npos);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyze"}) == 4);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzed"}) == 3);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzedc"}) == 2);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzedcb"}) == 1);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzedcba"}) == 0);

	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyz"}, 2) == bksge::static_string<N1>::npos);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyze"}, 2) == 4);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzed"}, 2) == 3);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzedc"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzedcb"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::static_string<N2>{"xyzedcba"}, 2) == 2);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfCharPtrTest()
{
	bksge::static_string<N> const s1 = "abcde abcde";

	VERIFY(s1.find_first_of("a") == 0);
	VERIFY(s1.find_first_of("b") == 1);
	VERIFY(s1.find_first_of("c") == 2);
	VERIFY(s1.find_first_of("d") == 3);
	VERIFY(s1.find_first_of("e") == 4);
	VERIFY(s1.find_first_of("xyz") == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_of("xyze") == 4);
	VERIFY(s1.find_first_of("xyzed") == 3);
	VERIFY(s1.find_first_of("xyzedc") == 2);
	VERIFY(s1.find_first_of("xyzedcb") == 1);
	VERIFY(s1.find_first_of("xyzedcba") == 0);

	VERIFY(s1.find_first_of("xyz", 2) == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_of("xyze", 2) == 4);
	VERIFY(s1.find_first_of("xyzed", 2) == 3);
	VERIFY(s1.find_first_of("xyzedc", 2) == 2);
	VERIFY(s1.find_first_of("xyzedcb", 2) == 2);
	VERIFY(s1.find_first_of("xyzedcba", 2) == 2);

	VERIFY(s1.find_first_of("xedcba", 1, 1) == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_of("xedcba", 1, 2) == 4);
	VERIFY(s1.find_first_of("xedcba", 1, 3) == 3);
	VERIFY(s1.find_first_of("xedcba", 1, 4) == 2);
	VERIFY(s1.find_first_of("xedcba", 1, 5) == 1);
	VERIFY(s1.find_first_of("xedcba", 1, 6) == 1);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfCharTest()
{
	bksge::static_string<N> const s1 = "ab abc abcd";

	VERIFY(s1.find_first_of('a') == 0);
	VERIFY(s1.find_first_of('b') == 1);
	VERIFY(s1.find_first_of('c') == 5);
	VERIFY(s1.find_first_of('d') == 10);
	VERIFY(s1.find_first_of('e') == bksge::static_string<N>::npos);

	VERIFY(s1.find_first_of('a', 1) == 3);
	VERIFY(s1.find_first_of('a', 4) == 7);
	VERIFY(s1.find_first_of('a', 8) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfStringViewTest()
{
	bksge::static_string<N> const s1 = "abcde abcde";

	VERIFY(s1.find_first_of(bksge::string_view{"a"}) == 0);
	VERIFY(s1.find_first_of(bksge::string_view{"b"}) == 1);
	VERIFY(s1.find_first_of(bksge::string_view{"c"}) == 2);
	VERIFY(s1.find_first_of(bksge::string_view{"d"}) == 3);
	VERIFY(s1.find_first_of(bksge::string_view{"e"}) == 4);
	VERIFY(s1.find_first_of(bksge::string_view{"xyz"}) == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_of(bksge::string_view{"xyze"}) == 4);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzed"}) == 3);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzedc"}) == 2);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzedcb"}) == 1);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzedcba"}) == 0);

	VERIFY(s1.find_first_of(bksge::string_view{"xyz"}, 2) == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_of(bksge::string_view{"xyze"}, 2) == 4);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzed"}, 2) == 3);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzedc"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzedcb"}, 2) == 2);
	VERIFY(s1.find_first_of(bksge::string_view{"xyzedcba"}, 2) == 2);

	return true;
}

GTEST_TEST(StaticStringTest, FindFirstOfTest)
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
	bksge::static_string<N1> const s1 = "abcde abcde";

	VERIFY(s1.find_last_of(bksge::static_string<N2>{"a"}) == 6);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"b"}) == 7);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"c"}) == 8);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"d"}) == 9);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"e"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyz"}) == bksge::static_string<N1>::npos);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyze"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzed"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzedc"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzedcb"}) == 10);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzedcba"}) == 10);

	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyz"}, 8) == bksge::static_string<N1>::npos);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyze"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzed"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzedc"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzedcb"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::static_string<N2>{"xyzedcba"}, 8) == 8);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfCharPtrTest()
{
	bksge::static_string<N> const s1 = "abcde abcde";

	VERIFY(s1.find_last_of("a") == 6);
	VERIFY(s1.find_last_of("b") == 7);
	VERIFY(s1.find_last_of("c") == 8);
	VERIFY(s1.find_last_of("d") == 9);
	VERIFY(s1.find_last_of("e") == 10);
	VERIFY(s1.find_last_of("xyz") == bksge::static_string<N>::npos);
	VERIFY(s1.find_last_of("xyze") == 10);
	VERIFY(s1.find_last_of("xyzed") == 10);
	VERIFY(s1.find_last_of("xyzedc") == 10);
	VERIFY(s1.find_last_of("xyzedcb") == 10);
	VERIFY(s1.find_last_of("xyzedcba") == 10);

	VERIFY(s1.find_last_of("xyz", 8) == bksge::static_string<N>::npos);
	VERIFY(s1.find_last_of("xyze", 8) == 4);
	VERIFY(s1.find_last_of("xyzed", 8) == 4);
	VERIFY(s1.find_last_of("xyzedc", 8) == 8);
	VERIFY(s1.find_last_of("xyzedcb", 8) == 8);
	VERIFY(s1.find_last_of("xyzedcba", 8) == 8);

	VERIFY(s1.find_last_of("Xabcde", 8, 1) == bksge::static_string<N>::npos);
	VERIFY(s1.find_last_of("Xabcde", 8, 2) == 6);
	VERIFY(s1.find_last_of("Xabcde", 8, 3) == 7);
	VERIFY(s1.find_last_of("Xabcde", 8, 4) == 8);
	VERIFY(s1.find_last_of("Xabcde", 8, 5) == 8);
	VERIFY(s1.find_last_of("Xabcde", 8, 6) == 8);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfCharTest()
{
	bksge::static_string<N> const s1 = "ab abc abcd";

	VERIFY(s1.find_last_of('a') == 7);
	VERIFY(s1.find_last_of('b') == 8);
	VERIFY(s1.find_last_of('c') == 9);
	VERIFY(s1.find_last_of('d') == 10);
	VERIFY(s1.find_last_of('e') == bksge::static_string<N>::npos);

	VERIFY(s1.find_last_of('b', 8) == 8);
	VERIFY(s1.find_last_of('b', 7) == 4);
	VERIFY(s1.find_last_of('b', 4) == 4);
	VERIFY(s1.find_last_of('b', 3) == 1);
	VERIFY(s1.find_last_of('b', 1) == 1);
	VERIFY(s1.find_last_of('b', 0) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfStringViewTest()
{
	bksge::static_string<N> const s1 = "abcde abcde";

	VERIFY(s1.find_last_of(bksge::string_view{"a"}) == 6);
	VERIFY(s1.find_last_of(bksge::string_view{"b"}) == 7);
	VERIFY(s1.find_last_of(bksge::string_view{"c"}) == 8);
	VERIFY(s1.find_last_of(bksge::string_view{"d"}) == 9);
	VERIFY(s1.find_last_of(bksge::string_view{"e"}) == 10);
	VERIFY(s1.find_last_of(bksge::string_view{"xyz"}) == bksge::static_string<N>::npos);
	VERIFY(s1.find_last_of(bksge::string_view{"xyze"}) == 10);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzed"}) == 10);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzedc"}) == 10);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzedcb"}) == 10);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzedcba"}) == 10);

	VERIFY(s1.find_last_of(bksge::string_view{"xyz"}, 8) == bksge::static_string<N>::npos);
	VERIFY(s1.find_last_of(bksge::string_view{"xyze"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzed"}, 8) == 4);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzedc"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzedcb"}, 8) == 8);
	VERIFY(s1.find_last_of(bksge::string_view{"xyzedcba"}, 8) == 8);

	return true;
}

GTEST_TEST(StaticStringTest, FindLastOfTest)
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
	bksge::static_string<N1> const s1 = "abcde";

	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"a"}) == 1);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"b"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"c"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"d"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"e"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"ba"}) == 2);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"cba"}) == 3);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"dcba"}) == 4);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"edcba"}) == bksge::static_string<N1>::npos);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"xyzedcba"}) == bksge::static_string<N1>::npos);

	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"de"}, 1) == 1);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"de"}, 2) == 2);
	VERIFY(s1.find_first_not_of(bksge::static_string<N2>{"de"}, 3) == bksge::static_string<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfCharPtrTest()
{
	bksge::static_string<N> const s1 = "abcde";

	VERIFY(s1.find_first_not_of("a") == 1);
	VERIFY(s1.find_first_not_of("b") == 0);
	VERIFY(s1.find_first_not_of("c") == 0);
	VERIFY(s1.find_first_not_of("d") == 0);
	VERIFY(s1.find_first_not_of("e") == 0);
	VERIFY(s1.find_first_not_of("ba") == 2);
	VERIFY(s1.find_first_not_of("cba") == 3);
	VERIFY(s1.find_first_not_of("dcba") == 4);
	VERIFY(s1.find_first_not_of("edcba") == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_not_of("xyzedcba") == bksge::static_string<N>::npos);

	VERIFY(s1.find_first_not_of("de", 1) == 1);
	VERIFY(s1.find_first_not_of("de", 2) == 2);
	VERIFY(s1.find_first_not_of("de", 3) == bksge::static_string<N>::npos);

	VERIFY(s1.find_first_not_of("abcde", 1, 1) == 1);
	VERIFY(s1.find_first_not_of("abcde", 1, 2) == 2);
	VERIFY(s1.find_first_not_of("abcde", 1, 3) == 3);
	VERIFY(s1.find_first_not_of("abcde", 1, 4) == 4);
	VERIFY(s1.find_first_not_of("abcde", 1, 5) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfCharTest()
{
	bksge::static_string<N> const s1 = "aaaabbbccd";

	VERIFY(s1.find_first_not_of('a') == 4);
	VERIFY(s1.find_first_not_of('b') == 0);
	VERIFY(s1.find_first_not_of('c') == 0);
	VERIFY(s1.find_first_not_of('d') == 0);
	VERIFY(s1.find_first_not_of('e') == 0);

	VERIFY(s1.find_first_not_of('b', 4) == 7);
	VERIFY(s1.find_first_not_of('b', 8) == 8);
	VERIFY(s1.find_first_not_of('b', 9) == 9);
	VERIFY(s1.find_first_not_of('b', 10) == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_not_of('d', 4) == 4);
	VERIFY(s1.find_first_not_of('d', 8) == 8);
	VERIFY(s1.find_first_not_of('d', 9) == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_not_of('d', 10) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfStringViewTest()
{
	bksge::static_string<N> const s1 = "abcde";

	VERIFY(s1.find_first_not_of(bksge::string_view{"a"}) == 1);
	VERIFY(s1.find_first_not_of(bksge::string_view{"b"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::string_view{"c"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::string_view{"d"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::string_view{"e"}) == 0);
	VERIFY(s1.find_first_not_of(bksge::string_view{"ba"}) == 2);
	VERIFY(s1.find_first_not_of(bksge::string_view{"cba"}) == 3);
	VERIFY(s1.find_first_not_of(bksge::string_view{"dcba"}) == 4);
	VERIFY(s1.find_first_not_of(bksge::string_view{"edcba"}) == bksge::static_string<N>::npos);
	VERIFY(s1.find_first_not_of(bksge::string_view{"xyzedcba"}) == bksge::static_string<N>::npos);

	VERIFY(s1.find_first_not_of(bksge::string_view{"de"}, 1) == 1);
	VERIFY(s1.find_first_not_of(bksge::string_view{"de"}, 2) == 2);
	VERIFY(s1.find_first_not_of(bksge::string_view{"de"}, 3) == bksge::static_string<N>::npos);

	return true;
}

GTEST_TEST(StaticStringTest, FindFirstNotOfTest)
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
	bksge::static_string<N1> const s1 = "ddddcccbba";

	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"a"}) == 8);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"b"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"c"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"d"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"e"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"ab"}) == 6);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"abc"}) == 3);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"abcd"}) == bksge::static_string<N1>::npos);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"abcde"}) == bksge::static_string<N1>::npos);

	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"cd"}, 8) == 8);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"cd"}, 7) == 7);
	VERIFY(s1.find_last_not_of(bksge::static_string<N2>{"cd"}, 6) == bksge::static_string<N1>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfCharPtrTest()
{
	bksge::static_string<N> const s1 = "ddddcccbba";

	VERIFY(s1.find_last_not_of("a") == 8);
	VERIFY(s1.find_last_not_of("b") == 9);
	VERIFY(s1.find_last_not_of("c") == 9);
	VERIFY(s1.find_last_not_of("d") == 9);
	VERIFY(s1.find_last_not_of("e") == 9);
	VERIFY(s1.find_last_not_of("ab") == 6);
	VERIFY(s1.find_last_not_of("abc") == 3);
	VERIFY(s1.find_last_not_of("abcd") == bksge::static_string<N>::npos);
	VERIFY(s1.find_last_not_of("abcde") == bksge::static_string<N>::npos);

	VERIFY(s1.find_last_not_of("cd", 8) == 8);
	VERIFY(s1.find_last_not_of("cd", 7) == 7);
	VERIFY(s1.find_last_not_of("cd", 6) == bksge::static_string<N>::npos);

	VERIFY(s1.find_last_not_of("abcde", 8, 1) == 8);
	VERIFY(s1.find_last_not_of("abcde", 8, 2) == 6);
	VERIFY(s1.find_last_not_of("abcde", 8, 3) == 3);
	VERIFY(s1.find_last_not_of("abcde", 8, 4) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfCharTest()
{
	bksge::static_string<N> const s1 = "ddddcccbba";

	VERIFY(s1.find_last_not_of('a') == 8);
	VERIFY(s1.find_last_not_of('b') == 9);
	VERIFY(s1.find_last_not_of('c') == 9);
	VERIFY(s1.find_last_not_of('d') == 9);
	VERIFY(s1.find_last_not_of('e') == 9);

	VERIFY(s1.find_last_not_of('d', 5) == 5);
	VERIFY(s1.find_last_not_of('d', 4) == 4);
	VERIFY(s1.find_last_not_of('d', 3) == bksge::static_string<N>::npos);

	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfStringViewTest()
{
	bksge::static_string<N> const s1 = "ddddcccbba";

	VERIFY(s1.find_last_not_of(bksge::string_view{"a"}) == 8);
	VERIFY(s1.find_last_not_of(bksge::string_view{"b"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::string_view{"c"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::string_view{"d"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::string_view{"e"}) == 9);
	VERIFY(s1.find_last_not_of(bksge::string_view{"ab"}) == 6);
	VERIFY(s1.find_last_not_of(bksge::string_view{"abc"}) == 3);
	VERIFY(s1.find_last_not_of(bksge::string_view{"abcd"}) == bksge::static_string<N>::npos);
	VERIFY(s1.find_last_not_of(bksge::string_view{"abcde"}) == bksge::static_string<N>::npos);

	VERIFY(s1.find_last_not_of(bksge::string_view{"cd"}, 8) == 8);
	VERIFY(s1.find_last_not_of(bksge::string_view{"cd"}, 7) == 7);
	VERIFY(s1.find_last_not_of(bksge::string_view{"cd"}, 6) == bksge::static_string<N>::npos);

	return true;
}

GTEST_TEST(StaticStringTest, FindLastNotOfTest)
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
	bksge::static_string<N> const s1 = "abcde";
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

	VERIFY(s2 == "abcde");
	VERIFY(s3 == "bcde");
	VERIFY(s4 == "cde");
	VERIFY(s5 == "b");
	VERIFY(s6 == "bc");
	VERIFY(s7 == "bcd");
	VERIFY(s8 == "c");
	VERIFY(s9 == "cd");
	VERIFY(s10 == "cde");
	VERIFY(s11 == "cde");

	return true;
}

GTEST_TEST(StaticStringTest, SubstrTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubstrTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool StartsWithTest()
{
	bksge::static_string<N> const s = "abcde";

	VERIFY(s.starts_with(bksge::string_view{"abcde"})  == true);
	VERIFY(s.starts_with(bksge::string_view{"abc"})    == true);
	VERIFY(s.starts_with(bksge::string_view{"a"})      == true);
	VERIFY(s.starts_with(bksge::string_view{"abcdef"}) == false);
	VERIFY(s.starts_with(bksge::string_view{"abd"})    == false);
	VERIFY(s.starts_with(bksge::string_view{"bc"})     == false);

	VERIFY(s.starts_with('a') == true);
	VERIFY(s.starts_with('b') == false);
	VERIFY(s.starts_with('e') == false);

	VERIFY(s.starts_with("abcde")  == true);
	VERIFY(s.starts_with("abc")    == true);
	VERIFY(s.starts_with("a")      == true);
	VERIFY(s.starts_with("abcdef") == false);
	VERIFY(s.starts_with("abd")    == false);
	VERIFY(s.starts_with("bc")     == false);

	return true;
}

GTEST_TEST(StaticStringTest, StartsWithTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool EndsWithTest()
{
	bksge::static_string<N> const s = "abcde";

	VERIFY(s.ends_with(bksge::string_view{"abcde"})  == true);
	VERIFY(s.ends_with(bksge::string_view{"cde"})    == true);
	VERIFY(s.ends_with(bksge::string_view{"e"})      == true);
	VERIFY(s.ends_with(bksge::string_view{"abcdef"}) == false);
	VERIFY(s.ends_with(bksge::string_view{"dde"})    == false);
	VERIFY(s.ends_with(bksge::string_view{"cdf"})    == false);
	VERIFY(s.ends_with(bksge::string_view{"cd"})     == false);

	VERIFY(s.ends_with('e') == true);
	VERIFY(s.ends_with('d') == false);
	VERIFY(s.ends_with('a') == false);

	VERIFY(s.ends_with("abcde")  == true);
	VERIFY(s.ends_with("cde")    == true);
	VERIFY(s.ends_with("e")      == true);
	VERIFY(s.ends_with("abcdef") == false);
	VERIFY(s.ends_with("dde")    == false);
	VERIFY(s.ends_with("cdf")    == false);
	VERIFY(s.ends_with("cd")     == false);

	return true;
}

GTEST_TEST(StaticStringTest, EndsWithTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<100>());
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	{
		bksge::static_string<N> const s = "abc";
		auto p = s.data();
		VERIFY(p[0] == 'a');
		VERIFY(p[1] == 'b');
		VERIFY(p[2] == 'c');
		VERIFY(c_str_test(s, "abc"));
	}
	{
		bksge::static_string<N> s = "abc";
		auto p = s.data();
		VERIFY(p[0] == 'a');
		VERIFY(p[1] == 'b');
		VERIFY(p[2] == 'c');
		p[1] = 'X';
		VERIFY(c_str_test(s, "aXc"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<16>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<32>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<100>());
}

template <std::size_t N1, std::size_t N2>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	{
		bksge::static_string<N1> s1 = "abc";
		bksge::static_string<N2> s2 = "12345";
		s1.swap(s2);
		VERIFY(c_str_test(s1, "12345"));
		VERIFY(c_str_test(s2, "abc"));
	}
	{
		bksge::static_string<N1> s1 = "abcdefg";
		bksge::static_string<N2> s2 = "123";
		bksge::ranges::swap(s1, s2);
		VERIFY(c_str_test(s1, "123"));
		VERIFY(c_str_test(s2, "abcdefg"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, SwapTest)
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
		bksge::static_string<N1> const s1 = "abc";
		bksge::static_string<N2> const s2 = "12345";
		auto s3 = s1 + s2;
		VERIFY(c_str_test(s3, "abc12345"));
	}
	{
		bksge::static_string<N1> const s1 = "abc";
		bksge::static_string<N2> const s2 = "123";
		auto s3 = "xxx" + s1 + 'y' + s2 + 'z' + "AA";
		VERIFY(c_str_test(s3, "xxxabcy123zAA"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddStringCharPtrTest()
{
	{
		bksge::static_string<N> const s1 = "abc";
		auto s2 = s1 + "defg";
		VERIFY(c_str_test(s2, "abcdefg"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddStringCharTest()
{
	{
		bksge::static_string<N> const s1 = "abc";
		auto s2 = s1 + '1';
		VERIFY(c_str_test(s2, "abc1"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddCharPtrStringTest()
{
	{
		bksge::static_string<N> const s1 = "abc";
		auto s2 = "defg" + s1;
		VERIFY(c_str_test(s2, "defgabc"));
	}
	return true;
}

template <std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool AddCharStringTest()
{
	{
		bksge::static_string<N> const s1 = "abc";
		auto s2 = '1' + s1;
		VERIFY(c_str_test(s2, "1abc"));
	}
	return true;
}

GTEST_TEST(StaticStringTest, AddTest)
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

GTEST_TEST(StaticStringTest, InputStreamTest)
{
	{
		std::stringstream ss("abc");
		bksge::static_string<16> s;
		ss >> s;
		EXPECT_TRUE(s == "abc");
	}
	{
		std::stringstream ss("Hello World");
		bksge::static_string<32> s;
		ss >> s;
		EXPECT_TRUE(s == "Hello");
		ss >> s;
		EXPECT_TRUE(s == "World");
	}
}

GTEST_TEST(StaticStringTest, OutputStreamTest)
{
	{
		bksge::static_string<16> const s = "abc";
		std::stringstream ss;
		ss << s;
		EXPECT_TRUE(ss.str() == "abc");
	}
	{
		bksge::static_string<32> const s = "Hello World";
		std::stringstream ss;
		ss << s;
		EXPECT_TRUE(ss.str() == "Hello World");
	}
}

#undef VERIFY

}	// namespace bksge_static_string_test
