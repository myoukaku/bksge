/**
 *	@file	unit_test_fnd_string_view.cpp
 *
 *	@brief	basic_string_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/string_view/string_view.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace bksge_string_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
class StringViewTest : public ::testing::Test {};

using StringViewTestTypes =
::testing::Types<
	  char
	, wchar_t
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	, char8_t
#endif
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
	BKSGE_CONSTEXPR static bksge::basic_string_view<char> abcd_sv()
	{
		using namespace bksge::literals;
		return "abcd"sv;
	}
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
	BKSGE_CONSTEXPR static bksge::basic_string_view<wchar_t> abcd_sv()
	{
		using namespace bksge::literals::string_view_literals;
		return L"abcd"sv;
	}
};

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
template <>
struct StringViewTestHelper<char8_t>
{
	BKSGE_CONSTEXPR static const char8_t* foo_bar()    { return u8"foo bar"; }
	BKSGE_CONSTEXPR static const char8_t* with_nulls() { return u8"This contains \0 a zero byte."; }
	BKSGE_CONSTEXPR static const char8_t* aababc()     { return u8"aababc"; }
	BKSGE_CONSTEXPR static const char8_t* abcd()       { return u8"abcd"; }
	BKSGE_CONSTEXPR static const char8_t* ab()         { return u8"ab"; }
	BKSGE_CONSTEXPR static const char8_t* cd()         { return u8"cd"; }
	BKSGE_CONSTEXPR static bksge::basic_string_view<char8_t> abcd_sv()
	{
		using namespace bksge::literals;
		return u8"abcd"sv;
	}
};
#endif

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
	BKSGE_CONSTEXPR static bksge::basic_string_view<char16_t> abcd_sv()
	{
		using namespace bksge::literals::string_view_literals;
		return u"abcd"sv;
	}
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
	BKSGE_CONSTEXPR static bksge::basic_string_view<char32_t> abcd_sv()
	{
		using namespace bksge::string_view_literals;
		return U"abcd"sv;
	}
};
#endif

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorDefaultTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	{
		string_view sv;
		VERIFY(sv.length() == 0);
		VERIFY(sv.size()   == 0);
		VERIFY(sv.data()   == nullptr);
		VERIFY(sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		string_view sv{};
		VERIFY(sv.length() == 0);
		VERIFY(sv.size()   == 0);
		VERIFY(sv.data()   == nullptr);
		VERIFY(sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		string_view sv = {};
		VERIFY(sv.length() == 0);
		VERIFY(sv.size()   == 0);
		VERIFY(sv.data()   == nullptr);
		VERIFY(sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorCopyTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv1{str, 7};
		string_view sv2{sv1};

		VERIFY(sv2.size()   == sv1.size());
		VERIFY(sv2.data()   == sv1.data());

		VERIFY(sv2.length() == 7);
		VERIFY(sv2.size()   == 7);
		VERIFY(sv2.data()   == str);
		VERIFY(!sv2.empty());
		VERIFY(sv2.max_size() >= sv2.size());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrCountTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		VERIFY(sv.length() == 7);
		VERIFY(sv.size()   == 7);
		VERIFY(sv.data()   == str);
		VERIFY(!sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		string_view sv{nullptr, 0};
		VERIFY(sv.length() == 0);
		VERIFY(sv.size()   == 0);
		VERIFY(sv.data()   == nullptr);
		VERIFY(sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		auto str = StringViewTestHelper<CharT>::with_nulls();
		string_view sv{str, 28};
		VERIFY(sv.length() == 28);
		VERIFY(sv.size()   == 28);
		VERIFY(sv.data()   == str);
		VERIFY(!sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str};
		VERIFY(sv.length() == 7);
		VERIFY(sv.size()   == 7);
		VERIFY(sv.data()   == str);
		VERIFY(!sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		auto str = StringViewTestHelper<CharT>::with_nulls();
		const string_view sv{str};
		VERIFY(sv.length() == 14);
		VERIFY(sv.size()   == 14);
		VERIFY(sv.data()   == str);
		VERIFY(!sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorRangeTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv{str, str + 3};
		VERIFY(sv.length() == 3);
		VERIFY(sv.size()   == 3);
		VERIFY(sv.data()   == str);
		VERIFY(!sv.empty());
		VERIFY(sv.max_size() >= sv.size());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorDeductionTest()
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	using Helper = StringViewTestHelper<CharT>;
	{
		bksge::basic_string_view sv{Helper::abcd()};
		static_assert(bksge::is_same<decltype(sv), bksge::basic_string_view<CharT>>::value, "");
	}
	{
		bksge::basic_string_view sv{Helper::abcd(), 3};
		static_assert(bksge::is_same<decltype(sv), bksge::basic_string_view<CharT>>::value, "");
	}
	{
		auto str = Helper::abcd();
		bksge::basic_string_view sv{str, str + 2};
		static_assert(bksge::is_same<decltype(sv), bksge::basic_string_view<CharT>>::value, "");
	}
#endif
	return true;
}

TYPED_TEST(StringViewTest, CtorTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrCountTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCharPtrTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorRangeTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDeductionTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv2{str};
	
		string_view sv1;
		VERIFY(sv1.length() == 0);
		VERIFY(sv1.data() == nullptr);
		VERIFY(sv1.empty());

		sv1 = sv2;
		VERIFY(sv1.length() == 7);
		VERIFY(sv1.data() == str);
		VERIFY(!sv1.empty());
	}
	return true;
}
TYPED_TEST(StringViewTest, AssignTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool BeginEndTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using iterator = typename string_view::iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const iterator first = sv.begin();
		const iterator last = sv.end();
		iterator it = first;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[0] == first[0]);
		VERIFY(str[1] == first[1]);
		VERIFY(str[2] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[4] == first[4]);
		VERIFY(str[5] == first[5]);
		VERIFY(str[6] == first[6]);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CBeginCEndTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using const_iterator = typename string_view::const_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const const_iterator first = sv.cbegin();
		const const_iterator last = sv.cend();
		const_iterator it = first;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[0] == first[0]);
		VERIFY(str[1] == first[1]);
		VERIFY(str[2] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[4] == first[4]);
		VERIFY(str[5] == first[5]);
		VERIFY(str[6] == first[6]);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool RBeginREndTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using reverse_iterator = typename string_view::reverse_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const reverse_iterator first = sv.rbegin();
		const reverse_iterator last = sv.rend();
		reverse_iterator it = first;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[6] == first[0]);
		VERIFY(str[5] == first[1]);
		VERIFY(str[4] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[2] == first[4]);
		VERIFY(str[1] == first[5]);
		VERIFY(str[0] == first[6]);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CRBeginCREndTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using const_reverse_iterator = typename string_view::const_reverse_iterator;

	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str, 7};
		const const_reverse_iterator first = sv.crbegin();
		const const_reverse_iterator last = sv.crend();
		const_reverse_iterator it = first;
		VERIFY(*it == str[6]);
		VERIFY(it != last);
		++it;
		VERIFY(*it == str[5]);
		VERIFY(it != last);
		it++;
		VERIFY(*it == str[4]);
		VERIFY(it != last);
		it += 4;
		VERIFY(*it == str[0]);
		VERIFY(it != last);
		it--;
		VERIFY(*it == str[1]);
		VERIFY(it != last);
		--it;
		VERIFY(*it == str[2]);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == str[3]);
		VERIFY(it != last);
		it += 4;
		VERIFY(it == last);

		VERIFY(str[6] == first[0]);
		VERIFY(str[5] == first[1]);
		VERIFY(str[4] == first[2]);
		VERIFY(str[3] == first[3]);
		VERIFY(str[2] == first[4]);
		VERIFY(str[1] == first[5]);
		VERIFY(str[0] == first[6]);
	}
	return true;
}

TYPED_TEST(StringViewTest, IteratorTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BeginEndTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CBeginCEndTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RBeginREndTest<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CRBeginCREndTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorBracketTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
		const_reference r0 = sv[0];
		const_reference r1 = sv[1];
		const_reference r2 = sv[2];
		const_reference r3 = sv[3];
		const_reference r4 = sv[4];
		const_reference r5 = sv[5];
		const_reference r6 = sv[6];
		VERIFY(str[0] == r0);
		VERIFY(str[1] == r1);
		VERIFY(str[2] == r2);
		VERIFY(str[3] == r3);
		VERIFY(str[4] == r4);
		VERIFY(str[5] == r5);
		VERIFY(str[6] == r6);
	}
	return true;
}
TYPED_TEST(StringViewTest, OperatorBracketTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorBracketTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
		const_reference r0 = sv.at(0);
		const_reference r1 = sv.at(1);
		const_reference r2 = sv.at(2);
		const_reference r3 = sv.at(3);
		const_reference r4 = sv.at(4);
		const_reference r5 = sv.at(5);
		const_reference r6 = sv.at(6);
		VERIFY(str[0] == r0);
		VERIFY(str[1] == r1);
		VERIFY(str[2] == r2);
		VERIFY(str[3] == r3);
		VERIFY(str[4] == r4);
		VERIFY(str[5] == r5);
		VERIFY(str[6] == r6);
	}
	return true;
}
TYPED_TEST(StringViewTest, AtTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<CharT>());
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
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

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FrontTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
		const_reference r = sv.front();
		VERIFY(r == str[0]);
	}
	{
		auto str = StringViewTestHelper<CharT>::abcd();
		string_view sv{str};
		const_reference r = sv.front();
		VERIFY(r == str[0]);
	}
	return true;
}
TYPED_TEST(StringViewTest, FrontTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FrontTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool BackTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using const_reference = typename string_view::const_reference;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
		const_reference r = sv.back();
		VERIFY(r == str[6]);
	}
	{
		auto str = StringViewTestHelper<CharT>::abcd();
		string_view sv{str};
		const_reference r = sv.back();
		VERIFY(r == str[3]);
	}
	return true;
}
TYPED_TEST(StringViewTest, BackTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(BackTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		VERIFY(sv.data() == Helper::foo_bar());
	}
	{
		string_view sv{Helper::aababc()};
		VERIFY(sv.data() == Helper::aababc());
	}
	{
		string_view sv{Helper::abcd()};
		VERIFY(sv.data() == Helper::abcd());
	}
	{
		string_view sv;
		VERIFY(sv.data() == nullptr);
	}
	return true;
}
TYPED_TEST(StringViewTest, DataTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		VERIFY(sv.size() == 7);
	}
	{
		string_view sv{Helper::aababc()};
		VERIFY(sv.size() == 6);
	}
	{
		string_view sv{Helper::abcd()};
		VERIFY(sv.size() == 4);
	}
	{
		string_view sv;
		VERIFY(sv.size() == 0);
	}
	return true;
}
TYPED_TEST(StringViewTest, SizeTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool LengthTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		VERIFY(sv.length() == 7);
	}
	{
		string_view sv{Helper::aababc()};
		VERIFY(sv.length() == 6);
	}
	{
		string_view sv{Helper::abcd()};
		VERIFY(sv.length() == 4);
	}
	{
		string_view sv;
		VERIFY(sv.length() == 0);
	}
	return true;
}
TYPED_TEST(StringViewTest, LengthTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LengthTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		string_view sv{Helper::aababc()};
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		string_view sv{Helper::abcd()};
		VERIFY(sv.max_size() >= sv.size());
	}
	{
		string_view sv;
		VERIFY(sv.max_size() >= sv.size());
	}
	return true;
}
TYPED_TEST(StringViewTest, MaxSizeTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view sv{Helper::foo_bar()};
		VERIFY(!sv.empty());
	}
	{
		string_view sv{Helper::aababc()};
		VERIFY(!sv.empty());
	}
	{
		string_view sv{Helper::abcd()};
		VERIFY(!sv.empty());
	}
	{
		string_view sv;
		VERIFY(sv.empty());
	}
	return true;
}
TYPED_TEST(StringViewTest, EmptyTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool RemovePrefixTest()
{
	using string_view = bksge::basic_string_view<CharT>;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};

		VERIFY(sv.data() == str);
		VERIFY(sv.length() == 7);

		sv.remove_prefix(1);

		VERIFY(sv.data() == str + 1);
		VERIFY(sv.length() == 6);

		sv.remove_prefix(2);

		VERIFY(sv.data() == str + 3);
		VERIFY(sv.length() == 4);
	}
	return true;
}
TYPED_TEST(StringViewTest, RemovePrefixTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RemovePrefixTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool RemoveSuffixTest()
{
	using string_view = bksge::basic_string_view<CharT>;

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};

		VERIFY(sv.data() == str);
		VERIFY(sv.length() == 7);

		sv.remove_suffix(1);

		VERIFY(sv.data() == str);
		VERIFY(sv.length() == 6);

		sv.remove_suffix(2);

		VERIFY(sv.data() == str);
		VERIFY(sv.length() == 4);
	}
	return true;
}
TYPED_TEST(StringViewTest, RemoveSuffixTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveSuffixTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	string_view sv1{Helper::aababc()};
	string_view sv2{Helper::foo_bar()};

	VERIFY(sv1.data() == Helper::aababc());
	VERIFY(sv2.data() == Helper::foo_bar());
	VERIFY(sv1.length() == 6);
	VERIFY(sv2.length() == 7);

	sv1.swap(sv2);

	VERIFY(sv1.data() == Helper::foo_bar());
	VERIFY(sv2.data() == Helper::aababc());
	VERIFY(sv1.length() == 7);
	VERIFY(sv2.length() == 6);

	bksge::swap(sv1, sv2);

	VERIFY(sv1.data() == Helper::aababc());
	VERIFY(sv2.data() == Helper::foo_bar());
	VERIFY(sv1.length() == 6);
	VERIFY(sv2.length() == 7);

	return true;
}
TYPED_TEST(StringViewTest, SwapTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CopyTest()
{
	using string_view = bksge::basic_string_view<CharT>;

	auto str = StringViewTestHelper<CharT>::foo_bar();
	string_view sv{str};

	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7);
		VERIFY(len == 7);
		VERIFY(str[0] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 1);
		VERIFY(len == 6);
		VERIFY(str[1] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 3, 1);
		VERIFY(len == 3);
		VERIFY(str[1] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 6);
		VERIFY(len == 1);
		VERIFY(str[6] == buffer[0]);
	}
	{
		CharT buffer[16] {};
		auto len = sv.copy(buffer, 7, 7);
		VERIFY(len == 0);
		VERIFY(str[7] == buffer[0]);
	}
	return true;
}
TYPED_TEST(StringViewTest, CopyTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTest<CharT>());

	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv{str};
		CharT buffer[16] {};
		EXPECT_THROW(sv.copy(buffer, 7, 8), bksge::out_of_range);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool SubStrTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	
	const auto str = StringViewTestHelper<CharT>::foo_bar();
	const string_view sv1{str};
	{
		const string_view sv2 = sv1.substr();
		VERIFY(sv2.data() == str);
		VERIFY(sv2.length() == 7);
	}
	{
		const string_view sv2 = sv1.substr(2);
		VERIFY(sv2.data() == str + 2);
		VERIFY(sv2.length() == 5);
	}
	{
		const string_view sv2 = sv1.substr(2, 3);
		VERIFY(sv2.data() == str + 2);
		VERIFY(sv2.length() == 3);
	}
	{
		const string_view sv2 = sv1.substr(7, 10);
		VERIFY(sv2.data() == str + 7);
		VERIFY(sv2.length() == 0);
	}
	return true;
}
TYPED_TEST(StringViewTest, SubStrTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubStrTest<CharT>());
	
	{
		const auto str = StringViewTestHelper<CharT>::foo_bar();
		const string_view sv1{str};
		EXPECT_THROW((void)sv1.substr(8), bksge::out_of_range);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using string_view = bksge::basic_string_view<CharT>;

	auto const str = StringViewTestHelper<CharT>::foo_bar();
	string_view const sv1{str, 7};
	string_view const sv2{str, 6};
	string_view const sv3{str, 6};
	string_view const sv4{str, 5};
	string_view const sv5{str + 1, 2};
	string_view const sv6{str + 1, 3};
	string_view const sv7{str + 1, 3};
	string_view const sv8{str + 1, 4};

	// (1)
	VERIFY(sv2.compare(sv1) <  0);
	VERIFY(sv2.compare(sv2) == 0);
	VERIFY(sv2.compare(sv3) == 0);
	VERIFY(sv2.compare(sv4) >  0);
	VERIFY(sv2.compare(sv5) <  0);
	VERIFY(sv2.compare(sv6) <  0);
	VERIFY(sv2.compare(sv7) <  0);
	VERIFY(sv2.compare(sv8) <  0);

	VERIFY(sv6.compare(sv1) >  0);
	VERIFY(sv6.compare(sv2) >  0);
	VERIFY(sv6.compare(sv3) >  0);
	VERIFY(sv6.compare(sv4) >  0);
	VERIFY(sv6.compare(sv5) >  0);
	VERIFY(sv6.compare(sv6) == 0);
	VERIFY(sv6.compare(sv7) == 0);
	VERIFY(sv6.compare(sv8) <  0);

	// (2)
	VERIFY(sv1.compare(0, 8, sv1) == 0);
	VERIFY(sv1.compare(0, 6, sv1) <  0);
	VERIFY(sv1.compare(1, 3, sv1) >  0);
	VERIFY(sv1.compare(0, 6, sv2) == 0);
	VERIFY(sv1.compare(1, 3, sv6) == 0);

	// (3)
	VERIFY(sv1.compare(0, 7, sv1, 0, 7) == 0);
	VERIFY(sv1.compare(0, 6, sv1, 0, 6) == 0);
	VERIFY(sv1.compare(0, 7, sv1, 0, 8) == 0);
	VERIFY(sv1.compare(0, 6, sv1, 0, 7) <  0);
	VERIFY(sv1.compare(0, 7, sv1, 0, 6) >  0);
	VERIFY(sv1.compare(1, 6, sv1, 0, 6) >  0);
	VERIFY(sv1.compare(0, 6, sv1, 1, 6) <  0);
	VERIFY(sv1.compare(2, 2, sv6, 1, 2) == 0);

	// (4)
	VERIFY(sv1.compare(str) == 0);
	VERIFY(sv1.compare(str + 1) < 0);
	VERIFY(sv1.compare(str + 4) > 0);

	// (5)
	VERIFY(sv1.compare(1, 7, str + 1) == 0);
	VERIFY(sv1.compare(1, 6, str + 1) == 0);
	VERIFY(sv1.compare(1, 5, str + 1) <  0);
	VERIFY(sv1.compare(1, 5, str)     >  0);

	// (6)
	VERIFY(sv1.compare(1, 6, str + 1, 6) == 0);
	VERIFY(sv1.compare(1, 5, str + 1, 6) <  0);
	VERIFY(sv1.compare(1, 6, str + 1, 5) >  0);
	VERIFY(sv1.compare(0, 6, str + 1, 6) <  0);
	VERIFY(sv1.compare(1, 6, str + 0, 6) >  0);

	return true;
}
TYPED_TEST(StringViewTest, CompareTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool StartsWithTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view const sv{Helper::abcd()};

		// (1)
		VERIFY( (sv.starts_with(string_view{Helper::aababc(), 1})));
		VERIFY(!(sv.starts_with(string_view{Helper::aababc(), 2})));
		VERIFY( (sv.starts_with(string_view{Helper::ab()})));
		VERIFY(!(sv.starts_with(string_view{Helper::cd()})));

		// (2)
		VERIFY( (sv.starts_with(Helper::aababc()[0])));
		VERIFY( (sv.starts_with(Helper::aababc()[1])));
		VERIFY(!(sv.starts_with(Helper::aababc()[2])));
		VERIFY(!(sv.starts_with(Helper::cd()[0])));

		// (3)
		VERIFY( (sv.starts_with(Helper::abcd())));
		VERIFY( (sv.starts_with(Helper::ab())));
		VERIFY(!(sv.starts_with(Helper::cd())));
		VERIFY(!(sv.starts_with(Helper::aababc())));
	}
	return true;
}
TYPED_TEST(StringViewTest, StartsWithTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(StartsWithTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EndsWithTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		string_view const sv{Helper::abcd()};

		// (1)
		VERIFY(!(sv.ends_with(string_view{Helper::aababc(), 1})));
		VERIFY(!(sv.ends_with(string_view{Helper::aababc(), 2})));
		VERIFY(!(sv.ends_with(string_view{Helper::ab()})));
		VERIFY( (sv.ends_with(string_view{Helper::cd()})));

		// (2)
		VERIFY(!(sv.ends_with(Helper::aababc()[0])));
		VERIFY(!(sv.ends_with(Helper::aababc()[2])));
		VERIFY(!(sv.ends_with(Helper::abcd()[2])));
		VERIFY( (sv.ends_with(Helper::abcd()[3])));

		// (3)
		VERIFY( (sv.ends_with(Helper::abcd())));
		VERIFY(!(sv.ends_with(Helper::ab())));
		VERIFY( (sv.ends_with(Helper::cd())));
		VERIFY(!(sv.ends_with(Helper::aababc())));
	}
	return true;
}
TYPED_TEST(StringViewTest, EndsWithTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EndsWithTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ContainsTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	string_view const sv1{Helper::aababc(), 6};	// "aababc"

	// (1)
	VERIFY( sv1.contains(string_view{Helper::abcd(), 2}));	// "ab"
	VERIFY( sv1.contains(string_view{Helper::abcd(), 3}));	// "abc"
	VERIFY(!sv1.contains(string_view{Helper::abcd(), 4}));	// "abcd"
	VERIFY( sv1.contains(string_view{Helper::aababc()}));	// "aababc"

	// (2)
	VERIFY( sv1.contains(Helper::abcd()[0]));	// 'a'
	VERIFY( sv1.contains(Helper::abcd()[1]));	// 'b'
	VERIFY( sv1.contains(Helper::abcd()[2]));	// 'c'
	VERIFY(!sv1.contains(Helper::abcd()[3]));	// 'd'

	// (3)
	VERIFY( sv1.contains(Helper::ab()));		// "ab"
	VERIFY(!sv1.contains(Helper::cd()));		// "cd"
	VERIFY(!sv1.contains(Helper::abcd()));		// "abcd"
	VERIFY( sv1.contains(Helper::aababc()));	// "aababc"

	return true;
}
TYPED_TEST(StringViewTest, ContainsTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ContainsTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto const npos = string_view::npos;

	string_view const sv1{Helper::aababc(), 6};	// "aababc"
	string_view const sv2{Helper::abcd(), 1};	// "a"
	string_view const sv3{Helper::abcd(), 2};	// "ab"
	string_view const sv4{Helper::abcd(), 3};	// "abc"
	string_view const sv5{Helper::abcd(), 4};	// "abcd"

	// (1)
	VERIFY(  0u == sv1.find(sv2));
	VERIFY(  1u == sv1.find(sv3));
	VERIFY(  3u == sv1.find(sv4));
	VERIFY(npos == sv1.find(sv5));
	VERIFY(  1u == sv1.find(sv2, 1));
	VERIFY(  1u == sv1.find(sv3, 1));
	VERIFY(  3u == sv1.find(sv4, 1));
	VERIFY(npos == sv1.find(sv5, 1));
	VERIFY(  3u == sv1.find(sv2, 2));
	VERIFY(  3u == sv1.find(sv3, 2));
	VERIFY(  3u == sv1.find(sv4, 2));
	VERIFY(npos == sv1.find(sv5, 2));

	// (2)
	VERIFY(  0u == sv1.find(Helper::abcd()[0]));
	VERIFY(  2u == sv1.find(Helper::abcd()[1]));
	VERIFY(  5u == sv1.find(Helper::abcd()[2]));
	VERIFY(npos == sv1.find(Helper::abcd()[3]));
	VERIFY(  2u == sv1.find(Helper::abcd()[1], 2));
	VERIFY(  4u == sv1.find(Helper::abcd()[1], 3));
	VERIFY(  4u == sv1.find(Helper::abcd()[1], 4));
	VERIFY(npos == sv1.find(Helper::abcd()[1], 5));

	// (3)
	VERIFY(  0u == sv1.find(Helper::abcd(), 0, 0));
	VERIFY(  0u == sv1.find(Helper::abcd(), 0, 1));
	VERIFY(  1u == sv1.find(Helper::abcd(), 0, 2));
	VERIFY(  3u == sv1.find(Helper::abcd(), 0, 3));
	VERIFY(npos == sv1.find(Helper::abcd(), 0, 4));
	VERIFY(  2u == sv1.find(Helper::abcd(), 2, 0));
	VERIFY(  3u == sv1.find(Helper::abcd(), 2, 1));
	VERIFY(  3u == sv1.find(Helper::abcd(), 2, 2));
	VERIFY(  3u == sv1.find(Helper::abcd(), 2, 3));
	VERIFY(npos == sv1.find(Helper::abcd(), 2, 4));

	// (4)
	VERIFY(npos == sv1.find(Helper::abcd()));
	VERIFY(  1u == sv1.find(Helper::ab()));
	VERIFY(  1u == sv1.find(Helper::ab(), 1));
	VERIFY(  3u == sv1.find(Helper::ab(), 2));
	VERIFY(  3u == sv1.find(Helper::ab(), 3));
	VERIFY(npos == sv1.find(Helper::ab(), 4));
	VERIFY(npos == sv1.find(Helper::ab(), 5));

	return true;
}
TYPED_TEST(StringViewTest, FindTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool RFindTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto const npos = string_view::npos;

	string_view const sv1{Helper::aababc(), 6};	// "aababc"
	string_view const sv2{Helper::abcd(), 1};	// "a"
	string_view const sv3{Helper::abcd(), 2};	// "ab"
	string_view const sv4{Helper::abcd(), 3};	// "abc"
	string_view const sv5{Helper::abcd(), 4};	// "abcd"

	// (1)
	VERIFY(  0u == sv1.rfind(sv1));
	VERIFY(  3u == sv1.rfind(sv2));
	VERIFY(  3u == sv1.rfind(sv3));
	VERIFY(  3u == sv1.rfind(sv4));
	VERIFY(npos == sv1.rfind(sv5));
	VERIFY(  0u == sv1.rfind(sv1, 0));
	VERIFY(  0u == sv1.rfind(sv2, 0));
	VERIFY(npos == sv1.rfind(sv3, 0));
	VERIFY(npos == sv1.rfind(sv4, 0));
	VERIFY(npos == sv1.rfind(sv5, 0));
	VERIFY(  0u == sv1.rfind(sv1, 1));
	VERIFY(  1u == sv1.rfind(sv2, 1));
	VERIFY(  1u == sv1.rfind(sv3, 1));
	VERIFY(npos == sv1.rfind(sv4, 1));
	VERIFY(npos == sv1.rfind(sv5, 1));
	VERIFY(  0u == sv1.rfind(sv1, 3));
	VERIFY(  3u == sv1.rfind(sv2, 3));
	VERIFY(  3u == sv1.rfind(sv3, 3));
	VERIFY(  3u == sv1.rfind(sv4, 3));
	VERIFY(npos == sv1.rfind(sv5, 3));

	// (2)
	VERIFY(  3u == sv1.rfind(Helper::abcd()[0]));
	VERIFY(  4u == sv1.rfind(Helper::abcd()[1]));
	VERIFY(  5u == sv1.rfind(Helper::abcd()[2]));
	VERIFY(npos == sv1.rfind(Helper::abcd()[3]));
	VERIFY(  0u == sv1.rfind(Helper::abcd()[0], 0));
	VERIFY(npos == sv1.rfind(Helper::abcd()[1], 0));
	VERIFY(npos == sv1.rfind(Helper::abcd()[2], 0));
	VERIFY(npos == sv1.rfind(Helper::abcd()[3], 0));
	VERIFY(  1u == sv1.rfind(Helper::abcd()[0], 1));
	VERIFY(npos == sv1.rfind(Helper::abcd()[1], 1));
	VERIFY(npos == sv1.rfind(Helper::abcd()[2], 1));
	VERIFY(npos == sv1.rfind(Helper::abcd()[3], 1));
	VERIFY(  1u == sv1.rfind(Helper::abcd()[0], 2));
	VERIFY(  2u == sv1.rfind(Helper::abcd()[1], 2));
	VERIFY(npos == sv1.rfind(Helper::abcd()[2], 2));
	VERIFY(npos == sv1.rfind(Helper::abcd()[3], 2));
	VERIFY(  3u == sv1.rfind(Helper::abcd()[0], 4));
	VERIFY(  4u == sv1.rfind(Helper::abcd()[1], 4));
	VERIFY(npos == sv1.rfind(Helper::abcd()[2], 4));
	VERIFY(npos == sv1.rfind(Helper::abcd()[3], 4));
	VERIFY(  3u == sv1.rfind(Helper::abcd()[0], 5));
	VERIFY(  4u == sv1.rfind(Helper::abcd()[1], 5));
	VERIFY(  5u == sv1.rfind(Helper::abcd()[2], 5));
	VERIFY(npos == sv1.rfind(Helper::abcd()[3], 5));

	// (3)
	VERIFY(  0u == sv1.rfind(Helper::abcd(), 0, 0));
	VERIFY(  0u == sv1.rfind(Helper::abcd(), 0, 1));
	VERIFY(npos == sv1.rfind(Helper::abcd(), 0, 2));
	VERIFY(npos == sv1.rfind(Helper::abcd(), 0, 3));
	VERIFY(npos == sv1.rfind(Helper::abcd(), 0, 4));
	VERIFY(  1u == sv1.rfind(Helper::abcd(), 1, 0));
	VERIFY(  1u == sv1.rfind(Helper::abcd(), 1, 1));
	VERIFY(  1u == sv1.rfind(Helper::abcd(), 1, 2));
	VERIFY(npos == sv1.rfind(Helper::abcd(), 1, 3));
	VERIFY(npos == sv1.rfind(Helper::abcd(), 1, 4));
	VERIFY(  5u == sv1.rfind(Helper::abcd(), 5, 0));
	VERIFY(  3u == sv1.rfind(Helper::abcd(), 5, 1));
	VERIFY(  3u == sv1.rfind(Helper::abcd(), 5, 2));
	VERIFY(  3u == sv1.rfind(Helper::abcd(), 5, 3));
	VERIFY(npos == sv1.rfind(Helper::abcd(), 5, 4));

	// (4)
	VERIFY(npos == sv1.rfind(Helper::abcd()));
	VERIFY(  3u == sv1.rfind(Helper::ab()));
	VERIFY(npos == sv1.rfind(Helper::ab(), 0));
	VERIFY(  1u == sv1.rfind(Helper::ab(), 1));
	VERIFY(  1u == sv1.rfind(Helper::ab(), 2));
	VERIFY(  3u == sv1.rfind(Helper::ab(), 3));
	VERIFY(  3u == sv1.rfind(Helper::ab(), 4));
	VERIFY(  3u == sv1.rfind(Helper::ab(), 5));
	VERIFY(  3u == sv1.rfind(Helper::ab(), 6));

	return true;
}
TYPED_TEST(StringViewTest, RFindTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RFindTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto const npos = string_view::npos;

	string_view const sv1{Helper::with_nulls(), 28};	// "This contains \0 a zero byte."
	string_view const sv2{Helper::abcd(), 1};	// "a"
	string_view const sv3{Helper::abcd(), 2};	// "ab"
	string_view const sv4{Helper::abcd(), 3};	// "abc"
	string_view const sv5{Helper::abcd(), 0};	// ""

	// (1)
	VERIFY(  9u == sv1.find_first_of(sv2));
	VERIFY(  9u == sv1.find_first_of(sv3));
	VERIFY(  5u == sv1.find_first_of(sv4));
	VERIFY(npos == sv1.find_first_of(sv5));
	VERIFY(  9u == sv1.find_first_of(sv2, 1));
	VERIFY(  9u == sv1.find_first_of(sv3, 1));
	VERIFY(  5u == sv1.find_first_of(sv4, 1));
	VERIFY(npos == sv1.find_first_of(sv5, 1));
	VERIFY(  9u == sv1.find_first_of(sv2, 5));
	VERIFY(  9u == sv1.find_first_of(sv3, 5));
	VERIFY(  5u == sv1.find_first_of(sv4, 5));
	VERIFY(npos == sv1.find_first_of(sv5, 5));
	VERIFY(  9u == sv1.find_first_of(sv2, 6));
	VERIFY(  9u == sv1.find_first_of(sv3, 6));
	VERIFY(  9u == sv1.find_first_of(sv4, 6));
	VERIFY(npos == sv1.find_first_of(sv5, 6));
	VERIFY( 16u == sv1.find_first_of(sv2, 10));
	VERIFY( 16u == sv1.find_first_of(sv3, 10));
	VERIFY( 16u == sv1.find_first_of(sv4, 10));
	VERIFY(npos == sv1.find_first_of(sv5, 10));
	VERIFY(npos == sv1.find_first_of(sv2, 17));
	VERIFY( 23u == sv1.find_first_of(sv3, 17));
	VERIFY( 23u == sv1.find_first_of(sv4, 17));
	VERIFY(npos == sv1.find_first_of(sv5, 17));

	// (2)
	VERIFY(  9u == sv1.find_first_of(Helper::abcd()[0]));
	VERIFY( 23u == sv1.find_first_of(Helper::abcd()[1]));
	VERIFY(  5u == sv1.find_first_of(Helper::abcd()[2]));
	VERIFY(npos == sv1.find_first_of(Helper::abcd()[3]));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd()[0], 1));
	VERIFY( 23u == sv1.find_first_of(Helper::abcd()[1], 1));
	VERIFY(  5u == sv1.find_first_of(Helper::abcd()[2], 1));
	VERIFY(npos == sv1.find_first_of(Helper::abcd()[3], 1));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd()[0], 6));
	VERIFY( 23u == sv1.find_first_of(Helper::abcd()[1], 6));
	VERIFY(npos == sv1.find_first_of(Helper::abcd()[2], 6));
	VERIFY(npos == sv1.find_first_of(Helper::abcd()[3], 6));
	VERIFY( 16u == sv1.find_first_of(Helper::abcd()[0], 10));
	VERIFY( 23u == sv1.find_first_of(Helper::abcd()[1], 10));
	VERIFY(npos == sv1.find_first_of(Helper::abcd()[2], 10));
	VERIFY(npos == sv1.find_first_of(Helper::abcd()[3], 10));

	// (3)
	VERIFY(npos == sv1.find_first_of(Helper::abcd(),  0, 0));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  0, 1));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  0, 2));
	VERIFY(  5u == sv1.find_first_of(Helper::abcd(),  0, 3));
	VERIFY(npos == sv1.find_first_of(Helper::abcd(),  5, 0));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  5, 1));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  5, 2));
	VERIFY(  5u == sv1.find_first_of(Helper::abcd(),  5, 3));
	VERIFY(npos == sv1.find_first_of(Helper::abcd(),  6, 0));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  6, 1));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  6, 2));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  6, 3));
	VERIFY(npos == sv1.find_first_of(Helper::abcd(),  9, 0));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  9, 1));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  9, 2));
	VERIFY(  9u == sv1.find_first_of(Helper::abcd(),  9, 3));
	VERIFY(npos == sv1.find_first_of(Helper::abcd(), 10, 0));
	VERIFY( 16u == sv1.find_first_of(Helper::abcd(), 10, 1));
	VERIFY( 16u == sv1.find_first_of(Helper::abcd(), 10, 2));
	VERIFY( 16u == sv1.find_first_of(Helper::abcd(), 10, 3));

	// (4)
	VERIFY(  5u == sv1.find_first_of(Helper::abcd()));
	VERIFY(  9u == sv1.find_first_of(Helper::ab()));
	VERIFY(  9u == sv1.find_first_of(Helper::ab(),  0));
	VERIFY(  9u == sv1.find_first_of(Helper::ab(),  9));
	VERIFY( 16u == sv1.find_first_of(Helper::ab(), 10));
	VERIFY( 16u == sv1.find_first_of(Helper::ab(), 16));
	VERIFY( 23u == sv1.find_first_of(Helper::ab(), 17));
	VERIFY( 23u == sv1.find_first_of(Helper::ab(), 23));
	VERIFY(npos == sv1.find_first_of(Helper::ab(), 24));

	return true;
}
TYPED_TEST(StringViewTest, FindFirstOfTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto const npos = string_view::npos;

	string_view const sv1{Helper::with_nulls(), 28};	// "This contains \0 a zero byte."
	string_view const sv2{Helper::abcd(), 1};	// "a"
	string_view const sv3{Helper::abcd(), 2};	// "ab"
	string_view const sv4{Helper::abcd(), 3};	// "abc"
	string_view const sv5{Helper::abcd(), 0};	// ""

	// (1)
	VERIFY( 16u == sv1.find_last_of(sv2));
	VERIFY( 23u == sv1.find_last_of(sv3));
	VERIFY( 23u == sv1.find_last_of(sv4));
	VERIFY(npos == sv1.find_last_of(sv5));
	VERIFY(npos == sv1.find_last_of(sv2, 1));
	VERIFY(npos == sv1.find_last_of(sv3, 1));
	VERIFY(npos == sv1.find_last_of(sv4, 1));
	VERIFY(npos == sv1.find_last_of(sv5, 1));
	VERIFY(npos == sv1.find_last_of(sv2, 5));
	VERIFY(npos == sv1.find_last_of(sv3, 5));
	VERIFY(  5u == sv1.find_last_of(sv4, 5));
	VERIFY(npos == sv1.find_last_of(sv5, 5));
	VERIFY(npos == sv1.find_last_of(sv2, 6));
	VERIFY(npos == sv1.find_last_of(sv3, 6));
	VERIFY(  5u == sv1.find_last_of(sv4, 6));
	VERIFY(npos == sv1.find_last_of(sv5, 6));
	VERIFY(  9u == sv1.find_last_of(sv2, 10));
	VERIFY(  9u == sv1.find_last_of(sv3, 10));
	VERIFY(  9u == sv1.find_last_of(sv4, 10));
	VERIFY(npos == sv1.find_last_of(sv5, 10));
	VERIFY( 16u == sv1.find_last_of(sv2, 17));
	VERIFY( 16u == sv1.find_last_of(sv3, 17));
	VERIFY( 16u == sv1.find_last_of(sv4, 17));
	VERIFY(npos == sv1.find_last_of(sv5, 17));

	// (2)
	VERIFY( 16u == sv1.find_last_of(Helper::abcd()[0]));
	VERIFY( 23u == sv1.find_last_of(Helper::abcd()[1]));
	VERIFY(  5u == sv1.find_last_of(Helper::abcd()[2]));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[3]));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[0], 1));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[1], 1));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[2], 1));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[3], 1));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[0], 6));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[1], 6));
	VERIFY(  5u == sv1.find_last_of(Helper::abcd()[2], 6));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[3], 6));
	VERIFY(  9u == sv1.find_last_of(Helper::abcd()[0], 10));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[1], 10));
	VERIFY(  5u == sv1.find_last_of(Helper::abcd()[2], 10));
	VERIFY(npos == sv1.find_last_of(Helper::abcd()[3], 10));

	// (3)
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  0, 0));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  0, 1));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  0, 2));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  0, 3));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  5, 0));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  5, 1));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  5, 2));
	VERIFY(  5u == sv1.find_last_of(Helper::abcd(),  5, 3));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  6, 0));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  6, 1));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  6, 2));
	VERIFY(  5u == sv1.find_last_of(Helper::abcd(),  6, 3));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(),  9, 0));
	VERIFY(  9u == sv1.find_last_of(Helper::abcd(),  9, 1));
	VERIFY(  9u == sv1.find_last_of(Helper::abcd(),  9, 2));
	VERIFY(  9u == sv1.find_last_of(Helper::abcd(),  9, 3));
	VERIFY(npos == sv1.find_last_of(Helper::abcd(), 10, 0));
	VERIFY(  9u == sv1.find_last_of(Helper::abcd(), 10, 1));
	VERIFY(  9u == sv1.find_last_of(Helper::abcd(), 10, 2));
	VERIFY(  9u == sv1.find_last_of(Helper::abcd(), 10, 3));

	// (4)
	VERIFY( 23u == sv1.find_last_of(Helper::abcd()));
	VERIFY( 23u == sv1.find_last_of(Helper::ab()));
	VERIFY(npos == sv1.find_last_of(Helper::ab(),  0));
	VERIFY(  9u == sv1.find_last_of(Helper::ab(),  9));
	VERIFY(  9u == sv1.find_last_of(Helper::ab(), 10));
	VERIFY( 16u == sv1.find_last_of(Helper::ab(), 16));
	VERIFY( 16u == sv1.find_last_of(Helper::ab(), 17));
	VERIFY( 23u == sv1.find_last_of(Helper::ab(), 23));
	VERIFY( 23u == sv1.find_last_of(Helper::ab(), 24));

	return true;
}
TYPED_TEST(StringViewTest, FindLastOfTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto const npos = string_view::npos;

	string_view const sv1{Helper::aababc(), 6};	// "aababc"
	string_view const sv2{Helper::abcd(), 1};	// "a"
	string_view const sv3{Helper::abcd(), 2};	// "ab"
	string_view const sv4{Helper::abcd(), 3};	// "abc"
	string_view const sv5{Helper::abcd(), 0};	// ""

	// (1)
	VERIFY(  2u == sv1.find_first_not_of(sv2));
	VERIFY(  5u == sv1.find_first_not_of(sv3));
	VERIFY(npos == sv1.find_first_not_of(sv4));
	VERIFY(  0u == sv1.find_first_not_of(sv5));
	VERIFY(  2u == sv1.find_first_not_of(sv2, 1));
	VERIFY(  5u == sv1.find_first_not_of(sv3, 1));
	VERIFY(npos == sv1.find_first_not_of(sv4, 1));
	VERIFY(  1u == sv1.find_first_not_of(sv5, 1));
	VERIFY(  2u == sv1.find_first_not_of(sv2, 2));
	VERIFY(  5u == sv1.find_first_not_of(sv3, 2));
	VERIFY(npos == sv1.find_first_not_of(sv4, 2));
	VERIFY(  2u == sv1.find_first_not_of(sv5, 2));
	VERIFY(  4u == sv1.find_first_not_of(sv2, 3));
	VERIFY(  5u == sv1.find_first_not_of(sv3, 3));
	VERIFY(npos == sv1.find_first_not_of(sv4, 3));
	VERIFY(  3u == sv1.find_first_not_of(sv5, 3));
	VERIFY(  4u == sv1.find_first_not_of(sv2, 4));
	VERIFY(  5u == sv1.find_first_not_of(sv3, 4));
	VERIFY(npos == sv1.find_first_not_of(sv4, 4));
	VERIFY(  4u == sv1.find_first_not_of(sv5, 4));
	VERIFY(  5u == sv1.find_first_not_of(sv2, 5));
	VERIFY(  5u == sv1.find_first_not_of(sv3, 5));
	VERIFY(npos == sv1.find_first_not_of(sv4, 5));
	VERIFY(  5u == sv1.find_first_not_of(sv5, 5));
	VERIFY(npos == sv1.find_first_not_of(sv2, 6));
	VERIFY(npos == sv1.find_first_not_of(sv3, 6));
	VERIFY(npos == sv1.find_first_not_of(sv4, 6));
	VERIFY(npos == sv1.find_first_not_of(sv5, 6));

	// (2)
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd()[0]));
	VERIFY(  0u == sv1.find_first_not_of(Helper::abcd()[1]));
	VERIFY(  0u == sv1.find_first_not_of(Helper::abcd()[2]));
	VERIFY(  0u == sv1.find_first_not_of(Helper::abcd()[3]));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd()[0], 1));
	VERIFY(  1u == sv1.find_first_not_of(Helper::abcd()[1], 1));
	VERIFY(  1u == sv1.find_first_not_of(Helper::abcd()[2], 1));
	VERIFY(  1u == sv1.find_first_not_of(Helper::abcd()[3], 1));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd()[0], 2));
	VERIFY(  3u == sv1.find_first_not_of(Helper::abcd()[1], 2));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd()[2], 2));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd()[3], 2));
	VERIFY(  4u == sv1.find_first_not_of(Helper::abcd()[0], 3));
	VERIFY(  3u == sv1.find_first_not_of(Helper::abcd()[1], 3));
	VERIFY(  3u == sv1.find_first_not_of(Helper::abcd()[2], 3));
	VERIFY(  3u == sv1.find_first_not_of(Helper::abcd()[3], 3));
	VERIFY(  4u == sv1.find_first_not_of(Helper::abcd()[0], 4));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd()[1], 4));
	VERIFY(  4u == sv1.find_first_not_of(Helper::abcd()[2], 4));
	VERIFY(  4u == sv1.find_first_not_of(Helper::abcd()[3], 4));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd()[0], 5));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd()[1], 5));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd()[2], 5));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd()[3], 5));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd()[0], 6));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd()[1], 6));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd()[2], 6));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd()[3], 6));

	// (3)
	VERIFY(  0u == sv1.find_first_not_of(Helper::abcd(), 0, 0));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd(), 0, 1));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 0, 2));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 0, 3));
	VERIFY(  1u == sv1.find_first_not_of(Helper::abcd(), 1, 0));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd(), 1, 1));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 1, 2));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 1, 3));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd(), 2, 0));
	VERIFY(  2u == sv1.find_first_not_of(Helper::abcd(), 2, 1));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 2, 2));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 2, 3));
	VERIFY(  3u == sv1.find_first_not_of(Helper::abcd(), 3, 0));
	VERIFY(  4u == sv1.find_first_not_of(Helper::abcd(), 3, 1));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 3, 2));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 3, 3));
	VERIFY(  4u == sv1.find_first_not_of(Helper::abcd(), 4, 0));
	VERIFY(  4u == sv1.find_first_not_of(Helper::abcd(), 4, 1));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 4, 2));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 4, 3));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 5, 0));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 5, 1));
	VERIFY(  5u == sv1.find_first_not_of(Helper::abcd(), 5, 2));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 5, 3));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 6, 0));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 6, 1));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 6, 2));
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd(), 6, 3));

	// (4)
	VERIFY(npos == sv1.find_first_not_of(Helper::abcd()));
	VERIFY(  5u == sv1.find_first_not_of(Helper::ab()));
	VERIFY(  5u == sv1.find_first_not_of(Helper::ab(), 0));
	VERIFY(npos == sv1.find_first_not_of(Helper::ab(), 6));

	return true;
}
TYPED_TEST(StringViewTest, FindFirstNotOfTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindFirstNotOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto const npos = string_view::npos;

	string_view const sv1{Helper::aababc(), 6};	// "aababc"
	string_view const sv2{Helper::abcd(), 1};	// "a"
	string_view const sv3{Helper::abcd(), 2};	// "ab"
	string_view const sv4{Helper::abcd(), 3};	// "abc"
	string_view const sv5{Helper::abcd(), 0};	// ""

	// (1)
	VERIFY(  5u == sv1.find_last_not_of(sv2));
	VERIFY(  5u == sv1.find_last_not_of(sv3));
	VERIFY(npos == sv1.find_last_not_of(sv4));
	VERIFY(  5u == sv1.find_last_not_of(sv5));
	VERIFY(npos == sv1.find_last_not_of(sv2, 1));
	VERIFY(npos == sv1.find_last_not_of(sv3, 1));
	VERIFY(npos == sv1.find_last_not_of(sv4, 1));
	VERIFY(  1u == sv1.find_last_not_of(sv5, 1));
	VERIFY(  2u == sv1.find_last_not_of(sv2, 2));
	VERIFY(npos == sv1.find_last_not_of(sv3, 2));
	VERIFY(npos == sv1.find_last_not_of(sv4, 2));
	VERIFY(  2u == sv1.find_last_not_of(sv5, 2));
	VERIFY(  2u == sv1.find_last_not_of(sv2, 3));
	VERIFY(npos == sv1.find_last_not_of(sv3, 3));
	VERIFY(npos == sv1.find_last_not_of(sv4, 3));
	VERIFY(  3u == sv1.find_last_not_of(sv5, 3));
	VERIFY(  4u == sv1.find_last_not_of(sv2, 4));
	VERIFY(npos == sv1.find_last_not_of(sv3, 4));
	VERIFY(npos == sv1.find_last_not_of(sv4, 4));
	VERIFY(  4u == sv1.find_last_not_of(sv5, 4));
	VERIFY(  5u == sv1.find_last_not_of(sv2, 5));
	VERIFY(  5u == sv1.find_last_not_of(sv3, 5));
	VERIFY(npos == sv1.find_last_not_of(sv4, 5));
	VERIFY(  5u == sv1.find_last_not_of(sv5, 5));
	VERIFY(  5u == sv1.find_last_not_of(sv2, 6));
	VERIFY(  5u == sv1.find_last_not_of(sv3, 6));
	VERIFY(npos == sv1.find_last_not_of(sv4, 6));
	VERIFY(  5u == sv1.find_last_not_of(sv5, 6));

	// (2)
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[0]));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[1]));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd()[2]));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[3]));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd()[0], 1));
	VERIFY(  1u == sv1.find_last_not_of(Helper::abcd()[1], 1));
	VERIFY(  1u == sv1.find_last_not_of(Helper::abcd()[2], 1));
	VERIFY(  1u == sv1.find_last_not_of(Helper::abcd()[3], 1));
	VERIFY(  2u == sv1.find_last_not_of(Helper::abcd()[0], 2));
	VERIFY(  1u == sv1.find_last_not_of(Helper::abcd()[1], 2));
	VERIFY(  2u == sv1.find_last_not_of(Helper::abcd()[2], 2));
	VERIFY(  2u == sv1.find_last_not_of(Helper::abcd()[3], 2));
	VERIFY(  2u == sv1.find_last_not_of(Helper::abcd()[0], 3));
	VERIFY(  3u == sv1.find_last_not_of(Helper::abcd()[1], 3));
	VERIFY(  3u == sv1.find_last_not_of(Helper::abcd()[2], 3));
	VERIFY(  3u == sv1.find_last_not_of(Helper::abcd()[3], 3));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd()[0], 4));
	VERIFY(  3u == sv1.find_last_not_of(Helper::abcd()[1], 4));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd()[2], 4));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd()[3], 4));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[0], 5));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[1], 5));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd()[2], 5));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[3], 5));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[0], 6));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[1], 6));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd()[2], 6));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd()[3], 6));

	// (3)
	VERIFY(  0u == sv1.find_last_not_of(Helper::abcd(), 0, 0));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 0, 1));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 0, 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 0, 3));
	VERIFY(  1u == sv1.find_last_not_of(Helper::abcd(), 1, 0));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 1, 1));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 1, 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 1, 3));
	VERIFY(  2u == sv1.find_last_not_of(Helper::abcd(), 2, 0));
	VERIFY(  2u == sv1.find_last_not_of(Helper::abcd(), 2, 1));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 2, 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 2, 3));
	VERIFY(  3u == sv1.find_last_not_of(Helper::abcd(), 3, 0));
	VERIFY(  2u == sv1.find_last_not_of(Helper::abcd(), 3, 1));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 3, 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 3, 3));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd(), 4, 0));
	VERIFY(  4u == sv1.find_last_not_of(Helper::abcd(), 4, 1));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 4, 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 4, 3));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd(), 5, 0));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd(), 5, 1));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd(), 5, 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 5, 3));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd(), 6, 0));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd(), 6, 1));
	VERIFY(  5u == sv1.find_last_not_of(Helper::abcd(), 6, 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd(), 6, 3));

	// (4)
	VERIFY(npos == sv1.find_last_not_of(Helper::abcd()));
	VERIFY(  5u == sv1.find_last_not_of(Helper::ab()));
	VERIFY(npos == sv1.find_last_not_of(Helper::ab(), 0));
	VERIFY(npos == sv1.find_last_not_of(Helper::ab(), 1));
	VERIFY(npos == sv1.find_last_not_of(Helper::ab(), 2));
	VERIFY(npos == sv1.find_last_not_of(Helper::ab(), 3));
	VERIFY(npos == sv1.find_last_not_of(Helper::ab(), 4));
	VERIFY(  5u == sv1.find_last_not_of(Helper::ab(), 5));
	VERIFY(  5u == sv1.find_last_not_of(Helper::ab(), 6));

	return true;
}
TYPED_TEST(StringViewTest, FindLastNotOfTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(FindLastNotOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorCompareTest1()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	string_view const sv1{Helper::aababc(), 6};	// "aababc"
	string_view const sv2 = sv1;				// "aababc"
	string_view const sv3 = sv1.substr(0, 5);	// "aabab"
	string_view const sv4 = sv1.substr(1, 5);	// "ababc"

	VERIFY( (sv1 == sv1));
	VERIFY( (sv1 == sv2));
	VERIFY(!(sv1 == sv3));
	VERIFY(!(sv1 == sv4));

	VERIFY(!(sv1 != sv1));
	VERIFY(!(sv1 != sv2));
	VERIFY( (sv1 != sv3));
	VERIFY( (sv1 != sv4));

	VERIFY(!(sv1 <  sv1));
	VERIFY(!(sv1 <  sv2));
	VERIFY(!(sv1 <  sv3));
	VERIFY( (sv1 <  sv4));

	VERIFY(!(sv1 >  sv1));
	VERIFY(!(sv1 >  sv2));
	VERIFY( (sv1 >  sv3));
	VERIFY(!(sv1 >  sv4));

	VERIFY( (sv1 <= sv1));
	VERIFY( (sv1 <= sv2));
	VERIFY(!(sv1 <= sv3));
	VERIFY( (sv1 <= sv4));

	VERIFY( (sv1 >= sv1));
	VERIFY( (sv1 >= sv2));
	VERIFY( (sv1 >= sv3));
	VERIFY(!(sv1 >= sv4));

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(bksge::is_eq(sv1 <=> sv1));
	VERIFY(bksge::is_eq(sv1 <=> sv2));
	VERIFY(bksge::is_gt(sv1 <=> sv3));
	VERIFY(bksge::is_lt(sv1 <=> sv4));
#endif

	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorCompareTest2()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	string_view const sv1{Helper::abcd()};	// "abcd"
	CharT const* s1 = Helper::abcd();		// "abcd"
	CharT const* s2 = Helper::aababc();		// "aababc"
	CharT const* s3 = Helper::cd();			// "cd"

	VERIFY( (sv1 == s1));
	VERIFY(!(sv1 == s2));
	VERIFY(!(sv1 == s3));

	VERIFY(!(sv1 != s1));
	VERIFY( (sv1 != s2));
	VERIFY( (sv1 != s3));

	VERIFY(!(sv1 <  s1));
	VERIFY(!(sv1 <  s2));
	VERIFY( (sv1 <  s3));

	VERIFY(!(sv1 >  s1));
	VERIFY( (sv1 >  s2));
	VERIFY(!(sv1 >  s3));

	VERIFY( (sv1 <= s1));
	VERIFY(!(sv1 <= s2));
	VERIFY( (sv1 <= s3));

	VERIFY( (sv1 >= s1));
	VERIFY( (sv1 >= s2));
	VERIFY(!(sv1 >= s3));

	VERIFY( (s1 == sv1));
	VERIFY(!(s2 == sv1));
	VERIFY(!(s3 == sv1));

	VERIFY(!(s1 != sv1));
	VERIFY( (s2 != sv1));
	VERIFY( (s3 != sv1));

	VERIFY(!(s1 <  sv1));
	VERIFY( (s2 <  sv1));
	VERIFY(!(s3 <  sv1));

	VERIFY(!(s1 >  sv1));
	VERIFY(!(s2 >  sv1));
	VERIFY( (s3 >  sv1));

	VERIFY( (s1 <= sv1));
	VERIFY( (s2 <= sv1));
	VERIFY(!(s3 <= sv1));

	VERIFY( (s1 >= sv1));
	VERIFY(!(s2 >= sv1));
	VERIFY( (s3 >= sv1));

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(bksge::is_eq(sv1 <=> s1));
	VERIFY(bksge::is_gt(sv1 <=> s2));
	VERIFY(bksge::is_lt(sv1 <=> s3));

	VERIFY(bksge::is_eq(s1 <=> sv1));
	VERIFY(bksge::is_lt(s2 <=> sv1));
	VERIFY(bksge::is_gt(s3 <=> sv1));
#endif

	return true;
}

TYPED_TEST(StringViewTest, OperatorCompareTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorCompareTest1<CharT>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorCompareTest2<CharT>());
}

TYPED_TEST(StringViewTest, OutputStreamTest)
{
	using CharT = TypeParam;
	using string_view = bksge::basic_string_view<CharT>;
	using stringstream = std::basic_stringstream<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	string_view sv{Helper::aababc(), 6};	// "aababc"

	{
		stringstream ss;
		ss << sv;
		EXPECT_TRUE(Helper::aababc() == ss.str());
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool HashTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;
	using Hash = bksge::hash<string_view>;

	string_view const sv1{Helper::aababc()};
	string_view const sv2{Helper::aababc(), 5};
	string_view const sv3{Helper::aababc(), 4};
	string_view const sv4{Helper::abcd()};

	Hash h;

	VERIFY(h(sv1) == h(sv1));
	VERIFY(h(sv1) != h(sv2));
	VERIFY(h(sv1) != h(sv3));
	VERIFY(h(sv1) != h(sv4));

	VERIFY(h(sv2) == h(sv2));
	VERIFY(h(sv2) != h(sv3));
	VERIFY(h(sv2) != h(sv4));

	VERIFY(h(sv3) == h(sv3));
	VERIFY(h(sv3) != h(sv4));

	VERIFY(h(sv4) == h(sv4));

	return true;
}
TYPED_TEST(StringViewTest, HashTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool LiteralTest()
{
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	auto sv = Helper::abcd_sv();
	static_assert(bksge::is_same<decltype(sv), string_view>::value, "");

	VERIFY(sv == Helper::abcd());
	VERIFY(sv != Helper::ab());
	VERIFY(sv != Helper::cd());

	return true;
}
TYPED_TEST(StringViewTest, LiteralTest)
{
	using CharT = TypeParam;
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LiteralTest<CharT>());
}

#undef VERIFY

}	// namespace bksge_string_view_test
