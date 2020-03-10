/**
 *	@file	unit_test_fnd_string_view.cpp
 *
 *	@brief	basic_string_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/string_view/string_view.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/sstream/basic_stringstream.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_string_view_string_view_test
{

template <typename T>
class StringViewTest : public ::testing::Test {};

using StringViewTestTypes =
::testing::Types<
	  char
	, wchar_t
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	, char16_t
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	, char32_t
#endif
>;

TYPED_TEST_SUITE(StringViewTest, StringViewTestTypes);

template <typename CharT>
struct StringViewTestHelper;

template <>
struct StringViewTestHelper<char>
{
	BKSGE_CONSTEXPR static const char* foo_bar()    { return "foo bar"; }
	BKSGE_CONSTEXPR static const char* with_nulls() { return "This contains \0 a zero byte."; }
	BKSGE_CONSTEXPR static const char* aababc()     { return "aababc"; }
	BKSGE_CONSTEXPR static const char* abcd()       { return "abcd"; }
	BKSGE_CONSTEXPR static const char* ab()         { return "ab"; }
	BKSGE_CONSTEXPR static const char* cd()         { return "cd"; }
};

template <>
struct StringViewTestHelper<wchar_t>
{
	BKSGE_CONSTEXPR static const wchar_t* foo_bar()    { return L"foo bar"; }
	BKSGE_CONSTEXPR static const wchar_t* with_nulls() { return L"This contains \0 a zero byte."; }
	BKSGE_CONSTEXPR static const wchar_t* aababc()     { return L"aababc"; }
	BKSGE_CONSTEXPR static const wchar_t* abcd()       { return L"abcd"; }
	BKSGE_CONSTEXPR static const wchar_t* ab()         { return L"ab"; }
	BKSGE_CONSTEXPR static const wchar_t* cd()         { return L"cd"; }
};

#if defined(BKSGE_HAS_CXX11_CHAR16_T)

template <>
struct StringViewTestHelper<char16_t>
{
	BKSGE_CONSTEXPR static const char16_t* foo_bar()    { return u"foo bar"; }
	BKSGE_CONSTEXPR static const char16_t* with_nulls() { return u"This contains \0 a zero byte."; }
	BKSGE_CONSTEXPR static const char16_t* aababc()     { return u"aababc"; }
	BKSGE_CONSTEXPR static const char16_t* abcd()       { return u"abcd"; }
	BKSGE_CONSTEXPR static const char16_t* ab()         { return u"ab"; }
	BKSGE_CONSTEXPR static const char16_t* cd()         { return u"cd"; }
};

#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)

template <>
struct StringViewTestHelper<char32_t>
{
	BKSGE_CONSTEXPR static const char32_t* foo_bar()    { return U"foo bar"; }
	BKSGE_CONSTEXPR static const char32_t* with_nulls() { return U"This contains \0 a zero byte."; }
	BKSGE_CONSTEXPR static const char32_t* aababc()     { return U"aababc"; }
	BKSGE_CONSTEXPR static const char32_t* abcd()       { return U"abcd"; }
	BKSGE_CONSTEXPR static const char32_t* ab()         { return U"ab"; }
	BKSGE_CONSTEXPR static const char32_t* cd()         { return U"cd"; }
};

#endif

TYPED_TEST(StringViewTest, CtorTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;
	(void)npos;

	// basic_string_view()
	{
		BKSGE_CONSTEXPR_OR_CONST string_view sv;
		BKSGE_CONSTEXPR_EXPECT_EQ(0u, sv.length());
		BKSGE_CONSTEXPR_EXPECT_EQ(0u, sv.size());
		BKSGE_CONSTEXPR_EXPECT_EQ(nullptr, sv.data());
		BKSGE_CONSTEXPR_EXPECT_TRUE(sv.empty());
		BKSGE_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST string_view sv{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0u, sv.length());
		BKSGE_CONSTEXPR_EXPECT_EQ(0u, sv.size());
		BKSGE_CONSTEXPR_EXPECT_EQ(nullptr, sv.data());
		BKSGE_CONSTEXPR_EXPECT_TRUE(sv.empty());
		BKSGE_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}

	// basic_string_view(basic_string_view const&)
	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv1{str, 7};
		const string_view sv2{sv1};
		EXPECT_EQ(7u, sv2.length());
		EXPECT_EQ(7u, sv2.size());
		EXPECT_EQ(str, sv2.data());
		EXPECT_FALSE(sv2.empty());
		EXPECT_TRUE(sv2.max_size() >= sv2.size());
	}

	// basic_string_view(CharT const*)
	{
		BKSGE_CXX14_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str};
		EXPECT_EQ(7u, sv.length());
		EXPECT_EQ(7u, sv.size());
		EXPECT_EQ(str, sv.data());
		EXPECT_FALSE(sv.empty());
		EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	//{
	//	const string_view sv{nullptr};
	//	EXPECT_EQ(0u, sv.length());
	//	EXPECT_EQ(0u, sv.size());
	//	EXPECT_EQ(nullptr, sv.data());
	//	EXPECT_TRUE(sv.empty());
	//	EXPECT_TRUE(sv.max_size() >= sv.size());
	//}
	{
		BKSGE_CXX14_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::with_nulls();
		const string_view sv{str};
		EXPECT_EQ(14u, sv.length());
		EXPECT_EQ(14u, sv.size());
		EXPECT_EQ(str, sv.data());
		EXPECT_FALSE(sv.empty());
		EXPECT_TRUE(sv.max_size() >= sv.size());
	}

	// basic_string_view(CharT const*, size_type)
	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str, 7};
		EXPECT_EQ(7u, sv.length());
		EXPECT_EQ(7u, sv.size());
		EXPECT_EQ(str, sv.data());
		EXPECT_FALSE(sv.empty());
		EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST string_view sv{nullptr, 0};
		BKSGE_CONSTEXPR_EXPECT_EQ(0u, sv.length());
		BKSGE_CONSTEXPR_EXPECT_EQ(0u, sv.size());
		BKSGE_CONSTEXPR_EXPECT_EQ(nullptr, sv.data());
		BKSGE_CONSTEXPR_EXPECT_TRUE(sv.empty());
		BKSGE_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		BKSGE_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::with_nulls();
		BKSGE_CONSTEXPR_OR_CONST string_view sv{str, 28};
		BKSGE_CONSTEXPR_EXPECT_EQ(28u, sv.length());
		BKSGE_CONSTEXPR_EXPECT_EQ(28u, sv.size());
//		BKSGE_CONSTEXPR_EXPECT_EQ(str, sv.data());
		BKSGE_CONSTEXPR_EXPECT_FALSE(sv.empty());
		BKSGE_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
}

TYPED_TEST(StringViewTest, AssignTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	auto str = StringViewTestHelper<CharT>::foo_bar();
	string_view sv2{str};
	
	string_view sv1;
	EXPECT_EQ(0u, sv1.length());
	EXPECT_EQ(nullptr, sv1.data());
	EXPECT_TRUE(sv1.empty());

	sv1 = sv2;
	EXPECT_EQ(7u, sv1.length());
	EXPECT_EQ(str, sv1.data());
	EXPECT_FALSE(sv1.empty());
}

TYPED_TEST(StringViewTest, BeginEndTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using iterator = typename string_view::iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str, 7};
		const iterator first = sv.begin();
		const iterator last = sv.end();
		const iterator it0 = first;
		EXPECT_EQ(str[0], *it0);
		EXPECT_FALSE(it0 == last);
		const iterator it1 = bksge::next(it0);
		EXPECT_EQ(str[1], *it1);
		EXPECT_FALSE(it1 == last);
		const iterator it2 = bksge::next(it1);
		EXPECT_EQ(str[2], *it2);
		EXPECT_FALSE(it2 == last);
		const iterator it3 = bksge::next(it2);
		EXPECT_EQ(str[3], *it3);
		EXPECT_FALSE(it3 == last);
		const iterator it4 = bksge::next(it3);
		EXPECT_EQ(str[4], *it4);
		EXPECT_FALSE(it4 == last);
		const iterator it5 = bksge::next(it4);
		EXPECT_EQ(str[5], *it5);
		EXPECT_FALSE(it5 == last);
		const iterator it6 = bksge::next(it5);
		EXPECT_EQ(str[6], *it6);
		EXPECT_FALSE(it6 == last);
		const iterator it7 = bksge::next(it6);
		EXPECT_TRUE (it7 == last);

		EXPECT_EQ(str[0], first[0]);
		EXPECT_EQ(str[1], first[1]);
		EXPECT_EQ(str[2], first[2]);
		EXPECT_EQ(str[3], first[3]);
		EXPECT_EQ(str[4], first[4]);
		EXPECT_EQ(str[5], first[5]);
		EXPECT_EQ(str[6], first[6]);
	}
}

TYPED_TEST(StringViewTest, CBeginCEndTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using const_iterator = typename string_view::const_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str, 7};
		const const_iterator first = sv.cbegin();
		const const_iterator last = sv.cend();
		const const_iterator it0 = first;
		EXPECT_EQ(str[0], *it0);
		EXPECT_FALSE(it0 == last);
		const const_iterator it1 = bksge::next(it0);
		EXPECT_EQ(str[1], *it1);
		EXPECT_FALSE(it1 == last);
		const const_iterator it2 = bksge::next(it1);
		EXPECT_EQ(str[2], *it2);
		EXPECT_FALSE(it2 == last);
		const const_iterator it3 = bksge::next(it2);
		EXPECT_EQ(str[3], *it3);
		EXPECT_FALSE(it3 == last);
		const const_iterator it4 = bksge::next(it3);
		EXPECT_EQ(str[4], *it4);
		EXPECT_FALSE(it4 == last);
		const const_iterator it5 = bksge::next(it4);
		EXPECT_EQ(str[5], *it5);
		EXPECT_FALSE(it5 == last);
		const const_iterator it6 = bksge::next(it5);
		EXPECT_EQ(str[6], *it6);
		EXPECT_FALSE(it6 == last);
		const const_iterator it7 = bksge::next(it6);
		EXPECT_TRUE (it7 == last);

		EXPECT_EQ(str[0], first[0]);
		EXPECT_EQ(str[1], first[1]);
		EXPECT_EQ(str[2], first[2]);
		EXPECT_EQ(str[3], first[3]);
		EXPECT_EQ(str[4], first[4]);
		EXPECT_EQ(str[5], first[5]);
		EXPECT_EQ(str[6], first[6]);
	}
}

TYPED_TEST(StringViewTest, RBeginREndTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using reverse_iterator = typename string_view::reverse_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str, 7};
		const reverse_iterator first = sv.rbegin();
		const reverse_iterator last = sv.rend();
		const reverse_iterator it0 = first;
		EXPECT_EQ(str[6], *it0);
		EXPECT_FALSE(it0 == last);
		const reverse_iterator it1 = bksge::next(it0);
		EXPECT_EQ(str[5], *it1);
		EXPECT_FALSE(it1 == last);
		const reverse_iterator it2 = bksge::next(it1);
		EXPECT_EQ(str[4], *it2);
		EXPECT_FALSE(it2 == last);
		const reverse_iterator it3 = bksge::next(it2);
		EXPECT_EQ(str[3], *it3);
		EXPECT_FALSE(it3 == last);
		const reverse_iterator it4 = bksge::next(it3);
		EXPECT_EQ(str[2], *it4);
		EXPECT_FALSE(it4 == last);
		const reverse_iterator it5 = bksge::next(it4);
		EXPECT_EQ(str[1], *it5);
		EXPECT_FALSE(it5 == last);
		const reverse_iterator it6 = bksge::next(it5);
		EXPECT_EQ(str[0], *it6);
		EXPECT_FALSE(it6 == last);
		const reverse_iterator it7 = bksge::next(it6);
		EXPECT_TRUE(it7 == last);

		EXPECT_EQ(str[6], first[0]);
		EXPECT_EQ(str[5], first[1]);
		EXPECT_EQ(str[4], first[2]);
		EXPECT_EQ(str[3], first[3]);
		EXPECT_EQ(str[2], first[4]);
		EXPECT_EQ(str[1], first[5]);
		EXPECT_EQ(str[0], first[6]);
	}
}

TYPED_TEST(StringViewTest, CRBeginCREndTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using const_reverse_iterator = typename string_view::const_reverse_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str, 7};
		const const_reverse_iterator first = sv.crbegin();
		const const_reverse_iterator last = sv.crend();
		const const_reverse_iterator it0 = first;
		EXPECT_EQ(str[6], *it0);
		EXPECT_FALSE(it0 == last);
		const const_reverse_iterator it1 = bksge::next(it0);
		EXPECT_EQ(str[5], *it1);
		EXPECT_FALSE(it1 == last);
		const const_reverse_iterator it2 = bksge::next(it1);
		EXPECT_EQ(str[4], *it2);
		EXPECT_FALSE(it2 == last);
		const const_reverse_iterator it3 = bksge::next(it2);
		EXPECT_EQ(str[3], *it3);
		EXPECT_FALSE(it3 == last);
		const const_reverse_iterator it4 = bksge::next(it3);
		EXPECT_EQ(str[2], *it4);
		EXPECT_FALSE(it4 == last);
		const const_reverse_iterator it5 = bksge::next(it4);
		EXPECT_EQ(str[1], *it5);
		EXPECT_FALSE(it5 == last);
		const const_reverse_iterator it6 = bksge::next(it5);
		EXPECT_EQ(str[0], *it6);
		EXPECT_FALSE(it6 == last);
		const const_reverse_iterator it7 = bksge::next(it6);
		EXPECT_TRUE(it7 == last);

		EXPECT_EQ(str[6], first[0]);
		EXPECT_EQ(str[5], first[1]);
		EXPECT_EQ(str[4], first[2]);
		EXPECT_EQ(str[3], first[3]);
		EXPECT_EQ(str[2], first[4]);
		EXPECT_EQ(str[1], first[5]);
		EXPECT_EQ(str[0], first[6]);
	}
}

TYPED_TEST(StringViewTest, OperatorBracketTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		BKSGE_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::foo_bar();
		BKSGE_CONSTEXPR_OR_CONST string_view sv{str, 7};
		const const_reference r0 = sv[0];
		const const_reference r1 = sv[1];
		const const_reference r2 = sv[2];
		const const_reference r3 = sv[3];
		const const_reference r4 = sv[4];
		const const_reference r5 = sv[5];
		const const_reference r6 = sv[6];
		EXPECT_EQ(str[0], r0);
		EXPECT_EQ(str[1], r1);
		EXPECT_EQ(str[2], r2);
		EXPECT_EQ(str[3], r3);
		EXPECT_EQ(str[4], r4);
		EXPECT_EQ(str[5], r5);
		EXPECT_EQ(str[6], r6);
		//const reference r7 = sv[7];
		//(void)r7;
	}
}

TYPED_TEST(StringViewTest, AtTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		BKSGE_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::foo_bar();
		BKSGE_CONSTEXPR_OR_CONST string_view sv{str, 7};
		const const_reference r0 = sv.at(0);
		const const_reference r1 = sv.at(1);
		const const_reference r2 = sv.at(2);
		const const_reference r3 = sv.at(3);
		const const_reference r4 = sv.at(4);
		const const_reference r5 = sv.at(5);
		const const_reference r6 = sv.at(6);
		EXPECT_EQ(str[0], r0);
		EXPECT_EQ(str[1], r1);
		EXPECT_EQ(str[2], r2);
		EXPECT_EQ(str[3], r3);
		EXPECT_EQ(str[4], r4);
		EXPECT_EQ(str[5], r5);
		EXPECT_EQ(str[6], r6);
		EXPECT_THROW((void)sv.at(7), bksge::out_of_range);
	}
	{
		string_view sv{StringViewTestHelper<CharT>::with_nulls()};
		EXPECT_NO_THROW((void)sv.at(0));
		EXPECT_NO_THROW((void)sv.at(13));
		EXPECT_THROW   ((void)sv.at(14), bksge::out_of_range);
		EXPECT_THROW   ((void)sv.at(100), bksge::out_of_range);
	}
	{
		string_view sv;
		EXPECT_THROW((void)sv.at(0), bksge::out_of_range);
		EXPECT_THROW((void)sv.at(1), bksge::out_of_range);
	}
}

TYPED_TEST(StringViewTest, FrontTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		BKSGE_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::foo_bar();
		BKSGE_CONSTEXPR_OR_CONST string_view sv{str, 7};
		const const_reference r = sv.front();
		EXPECT_EQ(str[0], r);
	}
}

TYPED_TEST(StringViewTest, BackTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		BKSGE_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::foo_bar();
		BKSGE_CONSTEXPR_OR_CONST string_view sv{str, 7};
		const const_reference r = sv.back();
		EXPECT_EQ(str[6], r);
	}
}

TYPED_TEST(StringViewTest, DataTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		EXPECT_EQ(Helper::foo_bar(), sv.data());
	}
	{
		string_view sv{Helper::aababc()};
		EXPECT_EQ(Helper::aababc(), sv.data());
	}
	{
		string_view sv{Helper::abcd()};
		EXPECT_EQ(Helper::abcd(), sv.data());
	}
	{
		string_view sv;
		EXPECT_EQ(nullptr, sv.data());
	}
}

TYPED_TEST(StringViewTest, SizeTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		EXPECT_EQ(7u, sv.size());
	}
	{
		string_view sv{Helper::aababc()};
		EXPECT_EQ(6u, sv.size());
	}
	{
		string_view sv{Helper::abcd()};
		EXPECT_EQ(4u, sv.size());
	}
	{
		string_view sv;
		EXPECT_EQ(0u, sv.size());
	}
}

TYPED_TEST(StringViewTest, LengthTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		EXPECT_EQ(7u, sv.length());
	}
	{
		string_view sv{Helper::aababc()};
		EXPECT_EQ(6u, sv.length());
	}
	{
		string_view sv{Helper::abcd()};
		EXPECT_EQ(4u, sv.length());
	}
	{
		string_view sv;
		EXPECT_EQ(0u, sv.length());
	}
}

TYPED_TEST(StringViewTest, MaxSizeTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		string_view sv{Helper::aababc()};
		EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		string_view sv{Helper::abcd()};
		EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		string_view sv;
		EXPECT_TRUE(sv.max_size() >= sv.size());
	}
}

TYPED_TEST(StringViewTest, EmptyTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		EXPECT_FALSE(sv.empty());
	}
	{
		string_view sv{Helper::aababc()};
		EXPECT_FALSE(sv.empty());
	}
	{
		string_view sv{Helper::abcd()};
		EXPECT_FALSE(sv.empty());
	}
	{
		string_view sv;
		EXPECT_TRUE(sv.empty());
	}
}

TYPED_TEST(StringViewTest, RemovePrefixTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};

		EXPECT_EQ(str, sv.data());
		EXPECT_EQ(7u, sv.length());

		sv.remove_prefix(1);

		EXPECT_EQ(str + 1, sv.data());
		EXPECT_EQ(6u, sv.length());

		sv.remove_prefix(2);

		EXPECT_EQ(str + 3, sv.data());
		EXPECT_EQ(4u, sv.length());
	}
}

TYPED_TEST(StringViewTest, RemoveSuffixTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};

		EXPECT_EQ(str, sv.data());
		EXPECT_EQ(7u, sv.length());

		sv.remove_suffix(1);

		EXPECT_EQ(str, sv.data());
		EXPECT_EQ(6u, sv.length());

		sv.remove_suffix(2);

		EXPECT_EQ(str, sv.data());
		EXPECT_EQ(4u, sv.length());
	}
}

TYPED_TEST(StringViewTest, SwapTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	string_view sv1{Helper::aababc(), 6};
	string_view sv2{Helper::foo_bar(), 7};

	EXPECT_EQ(Helper::aababc(), sv1.data());
	EXPECT_EQ(6u, sv1.length());
	EXPECT_EQ(Helper::foo_bar(), sv2.data());
	EXPECT_EQ(7u, sv2.length());

	sv1.swap(sv2);

	EXPECT_EQ(Helper::foo_bar(), sv1.data());
	EXPECT_EQ(7u, sv1.length());
	EXPECT_EQ(Helper::aababc(), sv2.data());
	EXPECT_EQ(6u, sv2.length());

	bksge::swap(sv1, sv2);

	EXPECT_EQ(Helper::aababc(), sv1.data());
	EXPECT_EQ(6u, sv1.length());
	EXPECT_EQ(Helper::foo_bar(), sv2.data());
	EXPECT_EQ(7u, sv2.length());
}

TYPED_TEST(StringViewTest, CopyTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	auto str = StringViewTestHelper<CharT>::foo_bar();
	string_view sv{str, 7};

	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7);
		EXPECT_EQ(str[0], buffer[0]);
		EXPECT_EQ(7u, len);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 1);
		EXPECT_EQ(str[1], buffer[0]);
		EXPECT_EQ(6u, len);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 3, 1);
		EXPECT_EQ(str[1], buffer[0]);
		EXPECT_EQ(3u, len);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 6);
		EXPECT_EQ(str[6], buffer[0]);
		EXPECT_EQ(1u, len);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 7);
		EXPECT_EQ(str[7], buffer[0]);
		EXPECT_EQ(0u, len);
	}
	{
		CharT buffer[16] {};
		EXPECT_THROW(sv.copy(buffer, 7, 8), bksge::out_of_range);
	}
}

TYPED_TEST(StringViewTest, SubStrTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	
	const auto str = StringViewTestHelper<CharT>::foo_bar();
	const string_view sv1{str, 7};
	{
		const string_view sv2 = sv1.substr();
		EXPECT_EQ(str, sv2.data());
		EXPECT_EQ(7u, sv2.length());
	}
	{
		const string_view sv2 = sv1.substr(2);
		EXPECT_EQ(str + 2, sv2.data());
		EXPECT_EQ(5u, sv2.length());
	}
	{
		const string_view sv2 = sv1.substr(2, 3);
		EXPECT_EQ(str + 2, sv2.data());
		EXPECT_EQ(3u, sv2.length());
	}
	{
		const string_view sv2 = sv1.substr(7, 10);
		EXPECT_EQ(str + 7, sv2.data());
		EXPECT_EQ(0u, sv2.length());
	}
	{
		EXPECT_THROW((void)sv1.substr(8), bksge::out_of_range);
	}
}

TYPED_TEST(StringViewTest, CompareTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	BKSGE_STATIC_CONSTEXPR auto str = StringViewTestHelper<CharT>::foo_bar();
	BKSGE_CONSTEXPR_OR_CONST string_view sv1{str, 7};
	BKSGE_CONSTEXPR_OR_CONST string_view sv2{str, 6};
	BKSGE_CONSTEXPR_OR_CONST string_view sv3{str, 6};
	BKSGE_CONSTEXPR_OR_CONST string_view sv4{str, 5};
	BKSGE_CONSTEXPR_OR_CONST string_view sv5{str + 1, 2};
	BKSGE_CONSTEXPR_OR_CONST string_view sv6{str + 1, 3};
	BKSGE_CONSTEXPR_OR_CONST string_view sv7{str + 1, 3};
	BKSGE_CONSTEXPR_OR_CONST string_view sv8{str + 1, 4};

	// (1)
	EXPECT_TRUE(sv2.compare(sv1) <  0);
	EXPECT_TRUE(sv2.compare(sv2) == 0);
	EXPECT_TRUE(sv2.compare(sv3) == 0);
	EXPECT_TRUE(sv2.compare(sv4) >  0);
	EXPECT_TRUE(sv2.compare(sv5) <  0);
	EXPECT_TRUE(sv2.compare(sv6) <  0);
	EXPECT_TRUE(sv2.compare(sv7) <  0);
	EXPECT_TRUE(sv2.compare(sv8) <  0);

	EXPECT_TRUE(sv6.compare(sv1) >  0);
	EXPECT_TRUE(sv6.compare(sv2) >  0);
	EXPECT_TRUE(sv6.compare(sv3) >  0);
	EXPECT_TRUE(sv6.compare(sv4) >  0);
	EXPECT_TRUE(sv6.compare(sv5) >  0);
	EXPECT_TRUE(sv6.compare(sv6) == 0);
	EXPECT_TRUE(sv6.compare(sv7) == 0);
	EXPECT_TRUE(sv6.compare(sv8) <  0);

	// (2)
	EXPECT_TRUE(sv1.compare(0, 8, sv1) == 0);
	EXPECT_TRUE(sv1.compare(0, 6, sv1) <  0);
	EXPECT_TRUE(sv1.compare(1, 3, sv1) >  0);
	EXPECT_TRUE(sv1.compare(0, 6, sv2) == 0);
	EXPECT_TRUE(sv1.compare(1, 3, sv6) == 0);

	// (3)
	EXPECT_TRUE(sv1.compare(0, 7, sv1, 0, 7) == 0);
	EXPECT_TRUE(sv1.compare(0, 6, sv1, 0, 6) == 0);
	EXPECT_TRUE(sv1.compare(0, 7, sv1, 0, 8) == 0);
	EXPECT_TRUE(sv1.compare(0, 6, sv1, 0, 7) <  0);
	EXPECT_TRUE(sv1.compare(0, 7, sv1, 0, 6) >  0);
	EXPECT_TRUE(sv1.compare(1, 6, sv1, 0, 6) >  0);
	EXPECT_TRUE(sv1.compare(0, 6, sv1, 1, 6) <  0);
	EXPECT_TRUE(sv1.compare(2, 2, sv6, 1, 2) == 0);

	// (4)
	EXPECT_TRUE(sv1.compare(str) == 0);
	EXPECT_TRUE(sv1.compare(str + 1) < 0);
	EXPECT_TRUE(sv1.compare(str + 4) > 0);

	// (5)
	EXPECT_TRUE(sv1.compare(1, 7, str + 1) == 0);
	EXPECT_TRUE(sv1.compare(1, 6, str + 1) == 0);
	EXPECT_TRUE(sv1.compare(1, 5, str + 1) <  0);
	EXPECT_TRUE(sv1.compare(1, 5, str)     >  0);

	// (6)
	EXPECT_TRUE(sv1.compare(1, 6, str + 1, 6) == 0);
	EXPECT_TRUE(sv1.compare(1, 5, str + 1, 6) <  0);
	EXPECT_TRUE(sv1.compare(1, 6, str + 1, 5) >  0);
	EXPECT_TRUE(sv1.compare(0, 6, str + 1, 6) <  0);
	EXPECT_TRUE(sv1.compare(1, 6, str + 0, 6) >  0);
}

TYPED_TEST(StringViewTest, StartsWithTest)
{
#if (BKSGE_CXX_STANDARD >= 20 && defined(__cpp_lib_starts_ends_with) && (__cpp_lib_starts_ends_with >= 201711))
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		BKSGE_CXX17_CONSTEXPR_OR_CONST string_view sv{Helper::abcd(), 4};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (sv.starts_with(Helper::abcd()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (sv.starts_with(Helper::ab()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.starts_with(Helper::cd()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.starts_with(Helper::aababc()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (sv.starts_with(Helper::aababc()[0]));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.starts_with(Helper::aababc()[2]));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (sv.starts_with(string_view{Helper::aababc(), 1}));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.starts_with(string_view{Helper::aababc(), 2}));
	}
#endif
}

TYPED_TEST(StringViewTest, EndsWithTest)
{
#if (BKSGE_CXX_STANDARD >= 20 && defined(__cpp_lib_starts_ends_with) && (__cpp_lib_starts_ends_with >= 201711))
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		BKSGE_CXX17_CONSTEXPR_OR_CONST string_view sv{Helper::abcd(), 4};
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (sv.ends_with(Helper::abcd()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.ends_with(Helper::ab()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (sv.ends_with(Helper::cd()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.ends_with(Helper::aababc()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.ends_with(Helper::aababc()[0]));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.ends_with(Helper::aababc()[2]));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.ends_with(string_view{Helper::aababc(), 1}));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(sv.ends_with(string_view{Helper::aababc(), 2}));
	}
#endif
}

TYPED_TEST(StringViewTest, FindTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;

	BKSGE_CONSTEXPR_OR_CONST string_view sv1{Helper::aababc(), 6};	// "aababc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv2{Helper::abcd(), 1};	// "a"
	BKSGE_CONSTEXPR_OR_CONST string_view sv3{Helper::abcd(), 2};	// "ab"
	BKSGE_CONSTEXPR_OR_CONST string_view sv4{Helper::abcd(), 3};	// "abc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv5{Helper::abcd(), 4};	// "abcd"

	// (1)
	EXPECT_EQ(  0u, sv1.find(sv2));
	EXPECT_EQ(  1u, sv1.find(sv3));
	EXPECT_EQ(  3u, sv1.find(sv4));
	EXPECT_EQ(npos, sv1.find(sv5));
	EXPECT_EQ(  1u, sv1.find(sv2, 1));
	EXPECT_EQ(  1u, sv1.find(sv3, 1));
	EXPECT_EQ(  3u, sv1.find(sv4, 1));
	EXPECT_EQ(npos, sv1.find(sv5, 1));
	EXPECT_EQ(  3u, sv1.find(sv2, 2));
	EXPECT_EQ(  3u, sv1.find(sv3, 2));
	EXPECT_EQ(  3u, sv1.find(sv4, 2));
	EXPECT_EQ(npos, sv1.find(sv5, 2));

	// (2)
	EXPECT_EQ(  0u, sv1.find(Helper::abcd()[0]));
	EXPECT_EQ(  2u, sv1.find(Helper::abcd()[1]));
	EXPECT_EQ(  5u, sv1.find(Helper::abcd()[2]));
	EXPECT_EQ(npos, sv1.find(Helper::abcd()[3]));
	EXPECT_EQ(  2u, sv1.find(Helper::abcd()[1], 2));
	EXPECT_EQ(  4u, sv1.find(Helper::abcd()[1], 3));
	EXPECT_EQ(  4u, sv1.find(Helper::abcd()[1], 4));
	EXPECT_EQ(npos, sv1.find(Helper::abcd()[1], 5));

	// (3)
	EXPECT_EQ(  0u, sv1.find(Helper::abcd(), 0, 0));
	EXPECT_EQ(  0u, sv1.find(Helper::abcd(), 0, 1));
	EXPECT_EQ(  1u, sv1.find(Helper::abcd(), 0, 2));
	EXPECT_EQ(  3u, sv1.find(Helper::abcd(), 0, 3));
	EXPECT_EQ(npos, sv1.find(Helper::abcd(), 0, 4));
	EXPECT_EQ(  2u, sv1.find(Helper::abcd(), 2, 0));
	EXPECT_EQ(  3u, sv1.find(Helper::abcd(), 2, 1));
	EXPECT_EQ(  3u, sv1.find(Helper::abcd(), 2, 2));
	EXPECT_EQ(  3u, sv1.find(Helper::abcd(), 2, 3));
	EXPECT_EQ(npos, sv1.find(Helper::abcd(), 2, 4));

	// (4)
	EXPECT_EQ(npos, sv1.find(Helper::abcd()));
	EXPECT_EQ(  1u, sv1.find(Helper::ab()));
	EXPECT_EQ(  1u, sv1.find(Helper::ab(), 1));
	EXPECT_EQ(  3u, sv1.find(Helper::ab(), 2));
	EXPECT_EQ(  3u, sv1.find(Helper::ab(), 3));
	EXPECT_EQ(npos, sv1.find(Helper::ab(), 4));
	EXPECT_EQ(npos, sv1.find(Helper::ab(), 5));
}

TYPED_TEST(StringViewTest, RFindTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;

	BKSGE_CONSTEXPR_OR_CONST string_view sv1{Helper::aababc(), 6};	// "aababc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv2{Helper::abcd(), 1};	// "a"
	BKSGE_CONSTEXPR_OR_CONST string_view sv3{Helper::abcd(), 2};	// "ab"
	BKSGE_CONSTEXPR_OR_CONST string_view sv4{Helper::abcd(), 3};	// "abc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv5{Helper::abcd(), 4};	// "abcd"

	// (1)
	EXPECT_EQ(  0u, sv1.rfind(sv1));
	EXPECT_EQ(  3u, sv1.rfind(sv2));
	EXPECT_EQ(  3u, sv1.rfind(sv3));
	EXPECT_EQ(  3u, sv1.rfind(sv4));
	EXPECT_EQ(npos, sv1.rfind(sv5));
	EXPECT_EQ(  0u, sv1.rfind(sv1, 0));
	EXPECT_EQ(  0u, sv1.rfind(sv2, 0));
	EXPECT_EQ(npos, sv1.rfind(sv3, 0));
	EXPECT_EQ(npos, sv1.rfind(sv4, 0));
	EXPECT_EQ(npos, sv1.rfind(sv5, 0));
	EXPECT_EQ(  0u, sv1.rfind(sv1, 1));
	EXPECT_EQ(  1u, sv1.rfind(sv2, 1));
	EXPECT_EQ(  1u, sv1.rfind(sv3, 1));
	EXPECT_EQ(npos, sv1.rfind(sv4, 1));
	EXPECT_EQ(npos, sv1.rfind(sv5, 1));
	EXPECT_EQ(  0u, sv1.rfind(sv1, 3));
	EXPECT_EQ(  3u, sv1.rfind(sv2, 3));
	EXPECT_EQ(  3u, sv1.rfind(sv3, 3));
	EXPECT_EQ(  3u, sv1.rfind(sv4, 3));
	EXPECT_EQ(npos, sv1.rfind(sv5, 3));

	// (2)
	EXPECT_EQ(  3u, sv1.rfind(Helper::abcd()[0]));
	EXPECT_EQ(  4u, sv1.rfind(Helper::abcd()[1]));
	EXPECT_EQ(  5u, sv1.rfind(Helper::abcd()[2]));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[3]));
	EXPECT_EQ(  0u, sv1.rfind(Helper::abcd()[0], 0));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[1], 0));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[2], 0));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[3], 0));
	EXPECT_EQ(  1u, sv1.rfind(Helper::abcd()[0], 1));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[1], 1));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[2], 1));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[3], 1));
	EXPECT_EQ(  1u, sv1.rfind(Helper::abcd()[0], 2));
	EXPECT_EQ(  2u, sv1.rfind(Helper::abcd()[1], 2));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[2], 2));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[3], 2));
	EXPECT_EQ(  3u, sv1.rfind(Helper::abcd()[0], 4));
	EXPECT_EQ(  4u, sv1.rfind(Helper::abcd()[1], 4));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[2], 4));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[3], 4));
	EXPECT_EQ(  3u, sv1.rfind(Helper::abcd()[0], 5));
	EXPECT_EQ(  4u, sv1.rfind(Helper::abcd()[1], 5));
	EXPECT_EQ(  5u, sv1.rfind(Helper::abcd()[2], 5));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()[3], 5));

	// (3)
	EXPECT_EQ(  0u, sv1.rfind(Helper::abcd(), 0, 0));
	EXPECT_EQ(  0u, sv1.rfind(Helper::abcd(), 0, 1));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd(), 0, 2));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd(), 0, 3));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd(), 0, 4));
	EXPECT_EQ(  1u, sv1.rfind(Helper::abcd(), 1, 0));
	EXPECT_EQ(  1u, sv1.rfind(Helper::abcd(), 1, 1));
	EXPECT_EQ(  1u, sv1.rfind(Helper::abcd(), 1, 2));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd(), 1, 3));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd(), 1, 4));
	EXPECT_EQ(  5u, sv1.rfind(Helper::abcd(), 5, 0));
	EXPECT_EQ(  3u, sv1.rfind(Helper::abcd(), 5, 1));
	EXPECT_EQ(  3u, sv1.rfind(Helper::abcd(), 5, 2));
	EXPECT_EQ(  3u, sv1.rfind(Helper::abcd(), 5, 3));
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd(), 5, 4));

	// (4)
	EXPECT_EQ(npos, sv1.rfind(Helper::abcd()));
	EXPECT_EQ(  3u, sv1.rfind(Helper::ab()));
	EXPECT_EQ(npos, sv1.rfind(Helper::ab(), 0));
	EXPECT_EQ(  1u, sv1.rfind(Helper::ab(), 1));
	EXPECT_EQ(  1u, sv1.rfind(Helper::ab(), 2));
	EXPECT_EQ(  3u, sv1.rfind(Helper::ab(), 3));
	EXPECT_EQ(  3u, sv1.rfind(Helper::ab(), 4));
	EXPECT_EQ(  3u, sv1.rfind(Helper::ab(), 5));
	EXPECT_EQ(  3u, sv1.rfind(Helper::ab(), 6));
}

TYPED_TEST(StringViewTest, FindFirstOfTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;

	BKSGE_CONSTEXPR_OR_CONST string_view sv1{Helper::with_nulls(), 28};	// "This contains \0 a zero byte."
	BKSGE_CONSTEXPR_OR_CONST string_view sv2{Helper::abcd(), 1};	// "a"
	BKSGE_CONSTEXPR_OR_CONST string_view sv3{Helper::abcd(), 2};	// "ab"
	BKSGE_CONSTEXPR_OR_CONST string_view sv4{Helper::abcd(), 3};	// "abc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv5{Helper::abcd(), 0};	// ""

	// (1)
	EXPECT_EQ(  9u, sv1.find_first_of(sv2));
	EXPECT_EQ(  9u, sv1.find_first_of(sv3));
	EXPECT_EQ(  5u, sv1.find_first_of(sv4));
	EXPECT_EQ(npos, sv1.find_first_of(sv5));
	EXPECT_EQ(  9u, sv1.find_first_of(sv2, 1));
	EXPECT_EQ(  9u, sv1.find_first_of(sv3, 1));
	EXPECT_EQ(  5u, sv1.find_first_of(sv4, 1));
	EXPECT_EQ(npos, sv1.find_first_of(sv5, 1));
	EXPECT_EQ(  9u, sv1.find_first_of(sv2, 5));
	EXPECT_EQ(  9u, sv1.find_first_of(sv3, 5));
	EXPECT_EQ(  5u, sv1.find_first_of(sv4, 5));
	EXPECT_EQ(npos, sv1.find_first_of(sv5, 5));
	EXPECT_EQ(  9u, sv1.find_first_of(sv2, 6));
	EXPECT_EQ(  9u, sv1.find_first_of(sv3, 6));
	EXPECT_EQ(  9u, sv1.find_first_of(sv4, 6));
	EXPECT_EQ(npos, sv1.find_first_of(sv5, 6));
	EXPECT_EQ( 16u, sv1.find_first_of(sv2, 10));
	EXPECT_EQ( 16u, sv1.find_first_of(sv3, 10));
	EXPECT_EQ( 16u, sv1.find_first_of(sv4, 10));
	EXPECT_EQ(npos, sv1.find_first_of(sv5, 10));
	EXPECT_EQ(npos, sv1.find_first_of(sv2, 17));
	EXPECT_EQ( 23u, sv1.find_first_of(sv3, 17));
	EXPECT_EQ( 23u, sv1.find_first_of(sv4, 17));
	EXPECT_EQ(npos, sv1.find_first_of(sv5, 17));

	// (2)
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd()[0]));
	EXPECT_EQ( 23u, sv1.find_first_of(Helper::abcd()[1]));
	EXPECT_EQ(  5u, sv1.find_first_of(Helper::abcd()[2]));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd()[3]));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd()[0], 1));
	EXPECT_EQ( 23u, sv1.find_first_of(Helper::abcd()[1], 1));
	EXPECT_EQ(  5u, sv1.find_first_of(Helper::abcd()[2], 1));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd()[3], 1));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd()[0], 6));
	EXPECT_EQ( 23u, sv1.find_first_of(Helper::abcd()[1], 6));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd()[2], 6));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd()[3], 6));
	EXPECT_EQ( 16u, sv1.find_first_of(Helper::abcd()[0], 10));
	EXPECT_EQ( 23u, sv1.find_first_of(Helper::abcd()[1], 10));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd()[2], 10));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd()[3], 10));

	// (3)
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd(),  0, 0));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  0, 1));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  0, 2));
	EXPECT_EQ(  5u, sv1.find_first_of(Helper::abcd(),  0, 3));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd(),  5, 0));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  5, 1));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  5, 2));
	EXPECT_EQ(  5u, sv1.find_first_of(Helper::abcd(),  5, 3));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd(),  6, 0));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  6, 1));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  6, 2));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  6, 3));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd(),  9, 0));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  9, 1));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  9, 2));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::abcd(),  9, 3));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::abcd(), 10, 0));
	EXPECT_EQ( 16u, sv1.find_first_of(Helper::abcd(), 10, 1));
	EXPECT_EQ( 16u, sv1.find_first_of(Helper::abcd(), 10, 2));
	EXPECT_EQ( 16u, sv1.find_first_of(Helper::abcd(), 10, 3));

	// (4)
	EXPECT_EQ(  5u, sv1.find_first_of(Helper::abcd()));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::ab()));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::ab(),  0));
	EXPECT_EQ(  9u, sv1.find_first_of(Helper::ab(),  9));
	EXPECT_EQ( 16u, sv1.find_first_of(Helper::ab(), 10));
	EXPECT_EQ( 16u, sv1.find_first_of(Helper::ab(), 16));
	EXPECT_EQ( 23u, sv1.find_first_of(Helper::ab(), 17));
	EXPECT_EQ( 23u, sv1.find_first_of(Helper::ab(), 23));
	EXPECT_EQ(npos, sv1.find_first_of(Helper::ab(), 24));
}

TYPED_TEST(StringViewTest, FindLastOfTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;

	BKSGE_CONSTEXPR_OR_CONST string_view sv1{Helper::with_nulls(), 28};	// "This contains \0 a zero byte."
	BKSGE_CONSTEXPR_OR_CONST string_view sv2{Helper::abcd(), 1};	// "a"
	BKSGE_CONSTEXPR_OR_CONST string_view sv3{Helper::abcd(), 2};	// "ab"
	BKSGE_CONSTEXPR_OR_CONST string_view sv4{Helper::abcd(), 3};	// "abc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv5{Helper::abcd(), 0};	// ""

	// (1)
	EXPECT_EQ( 16u, sv1.find_last_of(sv2));
	EXPECT_EQ( 23u, sv1.find_last_of(sv3));
	EXPECT_EQ( 23u, sv1.find_last_of(sv4));
	EXPECT_EQ(npos, sv1.find_last_of(sv5));
	EXPECT_EQ(npos, sv1.find_last_of(sv2, 1));
	EXPECT_EQ(npos, sv1.find_last_of(sv3, 1));
	EXPECT_EQ(npos, sv1.find_last_of(sv4, 1));
	EXPECT_EQ(npos, sv1.find_last_of(sv5, 1));
	EXPECT_EQ(npos, sv1.find_last_of(sv2, 5));
	EXPECT_EQ(npos, sv1.find_last_of(sv3, 5));
	EXPECT_EQ(  5u, sv1.find_last_of(sv4, 5));
	EXPECT_EQ(npos, sv1.find_last_of(sv5, 5));
	EXPECT_EQ(npos, sv1.find_last_of(sv2, 6));
	EXPECT_EQ(npos, sv1.find_last_of(sv3, 6));
	EXPECT_EQ(  5u, sv1.find_last_of(sv4, 6));
	EXPECT_EQ(npos, sv1.find_last_of(sv5, 6));
	EXPECT_EQ(  9u, sv1.find_last_of(sv2, 10));
	EXPECT_EQ(  9u, sv1.find_last_of(sv3, 10));
	EXPECT_EQ(  9u, sv1.find_last_of(sv4, 10));
	EXPECT_EQ(npos, sv1.find_last_of(sv5, 10));
	EXPECT_EQ( 16u, sv1.find_last_of(sv2, 17));
	EXPECT_EQ( 16u, sv1.find_last_of(sv3, 17));
	EXPECT_EQ( 16u, sv1.find_last_of(sv4, 17));
	EXPECT_EQ(npos, sv1.find_last_of(sv5, 17));

	// (2)
	EXPECT_EQ( 16u, sv1.find_last_of(Helper::abcd()[0]));
	EXPECT_EQ( 23u, sv1.find_last_of(Helper::abcd()[1]));
	EXPECT_EQ(  5u, sv1.find_last_of(Helper::abcd()[2]));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[3]));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[0], 1));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[1], 1));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[2], 1));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[3], 1));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[0], 6));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[1], 6));
	EXPECT_EQ(  5u, sv1.find_last_of(Helper::abcd()[2], 6));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[3], 6));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::abcd()[0], 10));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[1], 10));
	EXPECT_EQ(  5u, sv1.find_last_of(Helper::abcd()[2], 10));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd()[3], 10));

	// (3)
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  0, 0));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  0, 1));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  0, 2));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  0, 3));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  5, 0));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  5, 1));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  5, 2));
	EXPECT_EQ(  5u, sv1.find_last_of(Helper::abcd(),  5, 3));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  6, 0));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  6, 1));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  6, 2));
	EXPECT_EQ(  5u, sv1.find_last_of(Helper::abcd(),  6, 3));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(),  9, 0));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::abcd(),  9, 1));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::abcd(),  9, 2));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::abcd(),  9, 3));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::abcd(), 10, 0));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::abcd(), 10, 1));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::abcd(), 10, 2));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::abcd(), 10, 3));

	// (4)
	EXPECT_EQ( 23u, sv1.find_last_of(Helper::abcd()));
	EXPECT_EQ( 23u, sv1.find_last_of(Helper::ab()));
	EXPECT_EQ(npos, sv1.find_last_of(Helper::ab(),  0));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::ab(),  9));
	EXPECT_EQ(  9u, sv1.find_last_of(Helper::ab(), 10));
	EXPECT_EQ( 16u, sv1.find_last_of(Helper::ab(), 16));
	EXPECT_EQ( 16u, sv1.find_last_of(Helper::ab(), 17));
	EXPECT_EQ( 23u, sv1.find_last_of(Helper::ab(), 23));
	EXPECT_EQ( 23u, sv1.find_last_of(Helper::ab(), 24));
}

TYPED_TEST(StringViewTest, FindFirstNotOfTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;

	BKSGE_CONSTEXPR_OR_CONST string_view sv1{Helper::aababc(), 6};	// "aababc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv2{Helper::abcd(), 1};	// "a"
	BKSGE_CONSTEXPR_OR_CONST string_view sv3{Helper::abcd(), 2};	// "ab"
	BKSGE_CONSTEXPR_OR_CONST string_view sv4{Helper::abcd(), 3};	// "abc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv5{Helper::abcd(), 0};	// ""

	// (1)
	EXPECT_EQ(  2u, sv1.find_first_not_of(sv2));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv3));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv4));
	EXPECT_EQ(  0u, sv1.find_first_not_of(sv5));
	EXPECT_EQ(  2u, sv1.find_first_not_of(sv2, 1));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv3, 1));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv4, 1));
	EXPECT_EQ(  1u, sv1.find_first_not_of(sv5, 1));
	EXPECT_EQ(  2u, sv1.find_first_not_of(sv2, 2));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv3, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv4, 2));
	EXPECT_EQ(  2u, sv1.find_first_not_of(sv5, 2));
	EXPECT_EQ(  4u, sv1.find_first_not_of(sv2, 3));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv3, 3));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv4, 3));
	EXPECT_EQ(  3u, sv1.find_first_not_of(sv5, 3));
	EXPECT_EQ(  4u, sv1.find_first_not_of(sv2, 4));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv3, 4));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv4, 4));
	EXPECT_EQ(  4u, sv1.find_first_not_of(sv5, 4));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv2, 5));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv3, 5));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv4, 5));
	EXPECT_EQ(  5u, sv1.find_first_not_of(sv5, 5));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv2, 6));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv3, 6));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv4, 6));
	EXPECT_EQ(npos, sv1.find_first_not_of(sv5, 6));

	// (2)
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd()[0]));
	EXPECT_EQ(  0u, sv1.find_first_not_of(Helper::abcd()[1]));
	EXPECT_EQ(  0u, sv1.find_first_not_of(Helper::abcd()[2]));
	EXPECT_EQ(  0u, sv1.find_first_not_of(Helper::abcd()[3]));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd()[0], 1));
	EXPECT_EQ(  1u, sv1.find_first_not_of(Helper::abcd()[1], 1));
	EXPECT_EQ(  1u, sv1.find_first_not_of(Helper::abcd()[2], 1));
	EXPECT_EQ(  1u, sv1.find_first_not_of(Helper::abcd()[3], 1));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd()[0], 2));
	EXPECT_EQ(  3u, sv1.find_first_not_of(Helper::abcd()[1], 2));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd()[2], 2));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd()[3], 2));
	EXPECT_EQ(  4u, sv1.find_first_not_of(Helper::abcd()[0], 3));
	EXPECT_EQ(  3u, sv1.find_first_not_of(Helper::abcd()[1], 3));
	EXPECT_EQ(  3u, sv1.find_first_not_of(Helper::abcd()[2], 3));
	EXPECT_EQ(  3u, sv1.find_first_not_of(Helper::abcd()[3], 3));
	EXPECT_EQ(  4u, sv1.find_first_not_of(Helper::abcd()[0], 4));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd()[1], 4));
	EXPECT_EQ(  4u, sv1.find_first_not_of(Helper::abcd()[2], 4));
	EXPECT_EQ(  4u, sv1.find_first_not_of(Helper::abcd()[3], 4));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd()[0], 5));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd()[1], 5));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd()[2], 5));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd()[3], 5));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd()[0], 6));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd()[1], 6));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd()[2], 6));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd()[3], 6));

	// (3)
	EXPECT_EQ(  0u, sv1.find_first_not_of(Helper::abcd(), 0, 0));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd(), 0, 1));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 0, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 0, 3));
	EXPECT_EQ(  1u, sv1.find_first_not_of(Helper::abcd(), 1, 0));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd(), 1, 1));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 1, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 1, 3));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd(), 2, 0));
	EXPECT_EQ(  2u, sv1.find_first_not_of(Helper::abcd(), 2, 1));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 2, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 2, 3));
	EXPECT_EQ(  3u, sv1.find_first_not_of(Helper::abcd(), 3, 0));
	EXPECT_EQ(  4u, sv1.find_first_not_of(Helper::abcd(), 3, 1));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 3, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 3, 3));
	EXPECT_EQ(  4u, sv1.find_first_not_of(Helper::abcd(), 4, 0));
	EXPECT_EQ(  4u, sv1.find_first_not_of(Helper::abcd(), 4, 1));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 4, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 4, 3));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 5, 0));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 5, 1));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::abcd(), 5, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 5, 3));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 6, 0));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 6, 1));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 6, 2));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd(), 6, 3));

	// (4)
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::abcd()));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::ab()));
	EXPECT_EQ(  5u, sv1.find_first_not_of(Helper::ab(), 0));
	EXPECT_EQ(npos, sv1.find_first_not_of(Helper::ab(), 6));
}

TYPED_TEST(StringViewTest, FindLastNotOfTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;

	BKSGE_CONSTEXPR_OR_CONST string_view sv1{Helper::aababc(), 6};	// "aababc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv2{Helper::abcd(), 1};	// "a"
	BKSGE_CONSTEXPR_OR_CONST string_view sv3{Helper::abcd(), 2};	// "ab"
	BKSGE_CONSTEXPR_OR_CONST string_view sv4{Helper::abcd(), 3};	// "abc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv5{Helper::abcd(), 0};	// ""

	// (1)
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv2));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv3));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv4));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv5));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv2, 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv3, 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv4, 1));
	EXPECT_EQ(  1u, sv1.find_last_not_of(sv5, 1));
	EXPECT_EQ(  2u, sv1.find_last_not_of(sv2, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv3, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv4, 2));
	EXPECT_EQ(  2u, sv1.find_last_not_of(sv5, 2));
	EXPECT_EQ(  2u, sv1.find_last_not_of(sv2, 3));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv3, 3));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv4, 3));
	EXPECT_EQ(  3u, sv1.find_last_not_of(sv5, 3));
	EXPECT_EQ(  4u, sv1.find_last_not_of(sv2, 4));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv3, 4));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv4, 4));
	EXPECT_EQ(  4u, sv1.find_last_not_of(sv5, 4));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv2, 5));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv3, 5));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv4, 5));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv5, 5));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv2, 6));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv3, 6));
	EXPECT_EQ(npos, sv1.find_last_not_of(sv4, 6));
	EXPECT_EQ(  5u, sv1.find_last_not_of(sv5, 6));

	// (2)
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[0]));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[1]));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd()[2]));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[3]));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd()[0], 1));
	EXPECT_EQ(  1u, sv1.find_last_not_of(Helper::abcd()[1], 1));
	EXPECT_EQ(  1u, sv1.find_last_not_of(Helper::abcd()[2], 1));
	EXPECT_EQ(  1u, sv1.find_last_not_of(Helper::abcd()[3], 1));
	EXPECT_EQ(  2u, sv1.find_last_not_of(Helper::abcd()[0], 2));
	EXPECT_EQ(  1u, sv1.find_last_not_of(Helper::abcd()[1], 2));
	EXPECT_EQ(  2u, sv1.find_last_not_of(Helper::abcd()[2], 2));
	EXPECT_EQ(  2u, sv1.find_last_not_of(Helper::abcd()[3], 2));
	EXPECT_EQ(  2u, sv1.find_last_not_of(Helper::abcd()[0], 3));
	EXPECT_EQ(  3u, sv1.find_last_not_of(Helper::abcd()[1], 3));
	EXPECT_EQ(  3u, sv1.find_last_not_of(Helper::abcd()[2], 3));
	EXPECT_EQ(  3u, sv1.find_last_not_of(Helper::abcd()[3], 3));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd()[0], 4));
	EXPECT_EQ(  3u, sv1.find_last_not_of(Helper::abcd()[1], 4));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd()[2], 4));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd()[3], 4));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[0], 5));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[1], 5));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd()[2], 5));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[3], 5));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[0], 6));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[1], 6));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd()[2], 6));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd()[3], 6));

	// (3)
	EXPECT_EQ(  0u, sv1.find_last_not_of(Helper::abcd(), 0, 0));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 0, 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 0, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 0, 3));
	EXPECT_EQ(  1u, sv1.find_last_not_of(Helper::abcd(), 1, 0));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 1, 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 1, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 1, 3));
	EXPECT_EQ(  2u, sv1.find_last_not_of(Helper::abcd(), 2, 0));
	EXPECT_EQ(  2u, sv1.find_last_not_of(Helper::abcd(), 2, 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 2, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 2, 3));
	EXPECT_EQ(  3u, sv1.find_last_not_of(Helper::abcd(), 3, 0));
	EXPECT_EQ(  2u, sv1.find_last_not_of(Helper::abcd(), 3, 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 3, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 3, 3));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd(), 4, 0));
	EXPECT_EQ(  4u, sv1.find_last_not_of(Helper::abcd(), 4, 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 4, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 4, 3));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd(), 5, 0));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd(), 5, 1));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd(), 5, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 5, 3));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd(), 6, 0));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd(), 6, 1));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::abcd(), 6, 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd(), 6, 3));

	// (4)
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::abcd()));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::ab()));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::ab(), 0));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::ab(), 1));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::ab(), 2));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::ab(), 3));
	EXPECT_EQ(npos, sv1.find_last_not_of(Helper::ab(), 4));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::ab(), 5));
	EXPECT_EQ(  5u, sv1.find_last_not_of(Helper::ab(), 6));
}

TYPED_TEST(StringViewTest, OperatorCompareTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	BKSGE_CONSTEXPR_OR_CONST auto npos = string_view::npos;
	(void)npos;

	BKSGE_CONSTEXPR_OR_CONST string_view sv1{Helper::aababc(), 6};	// "aababc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv2 = sv1;					// "aababc"
	BKSGE_CONSTEXPR_OR_CONST string_view sv3 = sv1.substr(0, 5);	// "aabab"
	BKSGE_CONSTEXPR_OR_CONST string_view sv4 = sv1.substr(1, 5);	// "ababc"

	EXPECT_TRUE (sv1 == sv1);
	EXPECT_TRUE (sv1 == sv2);
	EXPECT_FALSE(sv1 == sv3);
	EXPECT_FALSE(sv1 == sv4);

	EXPECT_FALSE(sv1 != sv1);
	EXPECT_FALSE(sv1 != sv2);
	EXPECT_TRUE (sv1 != sv3);
	EXPECT_TRUE (sv1 != sv4);

	EXPECT_FALSE(sv1 <  sv1);
	EXPECT_FALSE(sv1 <  sv2);
	EXPECT_FALSE(sv1 <  sv3);
	EXPECT_TRUE (sv1 <  sv4);

	EXPECT_FALSE(sv1 >  sv1);
	EXPECT_FALSE(sv1 >  sv2);
	EXPECT_TRUE (sv1 >  sv3);
	EXPECT_FALSE(sv1 >  sv4);

	EXPECT_TRUE (sv1 <= sv1);
	EXPECT_TRUE (sv1 <= sv2);
	EXPECT_FALSE(sv1 <= sv3);
	EXPECT_TRUE (sv1 <= sv4);

	EXPECT_TRUE (sv1 >= sv1);
	EXPECT_TRUE (sv1 >= sv2);
	EXPECT_TRUE (sv1 >= sv3);
	EXPECT_FALSE(sv1 >= sv4);
}

TYPED_TEST(StringViewTest, OutputStreamTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using stringstream = bksge::basic_stringstream<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	string_view sv{Helper::aababc(), 6};	// "aababc"

	{
		stringstream ss;
		ss << sv;
		EXPECT_EQ(Helper::aababc(), ss.str());
	}
}

}	// namespace bksge_string_view_string_view_test
