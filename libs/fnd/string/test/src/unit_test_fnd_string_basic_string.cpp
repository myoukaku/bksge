/**
 *	@file	unit_test_fnd_string_basic_string.cpp
 *
 *	@brief	bksge::basic_string のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH();
// GCC: -O2, -O3 のとき、不要な警告が出てしまう
BKSGE_WARNING_DISABLE_GCC("-Wstringop-overflow");
BKSGE_WARNING_DISABLE_GCC("-Warray-bounds");

#include <bksge/fnd/string.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/stdexcept/length_error.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <new>
#include <cstddef>
#include <utility>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace bksge_string_test
{

namespace basic_string_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
class BasicStringTest : public ::testing::Test {};

using BasicStringTestTypes = ::testing::Types<
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

TYPED_TEST_SUITE(BasicStringTest, BasicStringTestTypes);

template <typename CharT>
struct StringTestHelper;

template <>
struct StringTestHelper<char>
{
	BKSGE_CONSTEXPR static char  null_char()    { return '\0'; }
	BKSGE_CONSTEXPR static const char* null_str()    { return ""; }
	BKSGE_CONSTEXPR static const char* long_str()    { return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; }
	BKSGE_CONSTEXPR static const char* multi_line_str()    { return "abc\nbcd\ncd"; }
	BKSGE_CONSTEXPR static const char* csv_str()    { return "abc,bcd,cd"; }
	BKSGE_CONSTEXPR static char comma_char()    { return ','; }
	BKSGE_CONSTEXPR static const char* acdcabe()    { return "acdcabe"; }
	BKSGE_CONSTEXPR static const char* abcccde()    { return "abcccde"; }
	BKSGE_CONSTEXPR static const char* aababc()    { return "aababc"; }
	BKSGE_CONSTEXPR static const char* abaaae()    { return "abaaae"; }
	BKSGE_CONSTEXPR static const char* abbccc()    { return "abbccc"; }
	BKSGE_CONSTEXPR static const char* acdbc()    { return "acdbc"; }
	BKSGE_CONSTEXPR static const char* accaa()    { return "accaa"; }
	BKSGE_CONSTEXPR static const char* abcde()    { return "abcde"; }
	BKSGE_CONSTEXPR static const char* abcb()    { return "abcb"; }
	BKSGE_CONSTEXPR static const char* abcd()    { return "abcd"; }
	BKSGE_CONSTEXPR static const char* abad()    { return "abad"; }
	BKSGE_CONSTEXPR static const char* abb()    { return "abb"; }
	BKSGE_CONSTEXPR static const char* abc()    { return "abc"; }
	BKSGE_CONSTEXPR static const char* ab()    { return "ab"; }
	BKSGE_CONSTEXPR static const char* ac()    { return "ac"; }
	BKSGE_CONSTEXPR static const char* ace()    { return "ace"; }
	BKSGE_CONSTEXPR static const char* a()    { return "a"; }
	BKSGE_CONSTEXPR static const char* aaa()    { return "aaa"; }
	BKSGE_CONSTEXPR static const char* bc()    { return "bc"; }
	BKSGE_CONSTEXPR static const char* bcd()    { return "bcd"; }
	BKSGE_CONSTEXPR static const char* bcde()    { return "bcde"; }
	BKSGE_CONSTEXPR static const char* bbcd()    { return "bbcd"; }
	BKSGE_CONSTEXPR static const char* c()    { return "c"; }
	BKSGE_CONSTEXPR static const char* cb()    { return "cb"; }
	BKSGE_CONSTEXPR static const char* cd()    { return "cd"; }
	BKSGE_CONSTEXPR static const char* cba()    { return "cba"; }
	BKSGE_CONSTEXPR static const char* cde()    { return "cde"; }
	BKSGE_CONSTEXPR static const char* cdede()    { return "cdede"; }
#if (BKSGE_CXX_STANDARD >= 14)
	/*BKSGE_CONSTEXPR*/ static bksge::basic_string<char> abcd_s()
	{
		using namespace bksge::literals;
		return "abcd"s;
	}
#endif
};

template <>
struct StringTestHelper<wchar_t>
{
	BKSGE_CONSTEXPR static wchar_t  null_char()    { return L'\0'; }
	BKSGE_CONSTEXPR static const wchar_t* null_str()    { return L""; }
	BKSGE_CONSTEXPR static const wchar_t* long_str()    { return L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; }
	BKSGE_CONSTEXPR static const wchar_t* multi_line_str()    { return L"abc\nbcd\ncd"; }
	BKSGE_CONSTEXPR static const wchar_t* csv_str()    { return L"abc,bcd,cd"; }
	BKSGE_CONSTEXPR static wchar_t comma_char()    { return L','; }
	BKSGE_CONSTEXPR static const wchar_t* acdcabe()    { return L"acdcabe"; }
	BKSGE_CONSTEXPR static const wchar_t* abcccde()    { return L"abcccde"; }
	BKSGE_CONSTEXPR static const wchar_t* aababc()    { return L"aababc"; }
	BKSGE_CONSTEXPR static const wchar_t* abaaae()    { return L"abaaae"; }
	BKSGE_CONSTEXPR static const wchar_t* abbccc()    { return L"abbccc"; }
	BKSGE_CONSTEXPR static const wchar_t* acdbc()    { return L"acdbc"; }
	BKSGE_CONSTEXPR static const wchar_t* accaa()    { return L"accaa"; }
	BKSGE_CONSTEXPR static const wchar_t* abcde()    { return L"abcde"; }
	BKSGE_CONSTEXPR static const wchar_t* abcb()    { return L"abcb"; }
	BKSGE_CONSTEXPR static const wchar_t* abcd()    { return L"abcd"; }
	BKSGE_CONSTEXPR static const wchar_t* abad()    { return L"abad"; }
	BKSGE_CONSTEXPR static const wchar_t* abb()    { return L"abb"; }
	BKSGE_CONSTEXPR static const wchar_t* abc()    { return L"abc"; }
	BKSGE_CONSTEXPR static const wchar_t* ab()    { return L"ab"; }
	BKSGE_CONSTEXPR static const wchar_t* ac()    { return L"ac"; }
	BKSGE_CONSTEXPR static const wchar_t* ace()    { return L"ace"; }
	BKSGE_CONSTEXPR static const wchar_t* a()    { return L"a"; }
	BKSGE_CONSTEXPR static const wchar_t* aaa()    { return L"aaa"; }
	BKSGE_CONSTEXPR static const wchar_t* bc()    { return L"bc"; }
	BKSGE_CONSTEXPR static const wchar_t* bcd()    { return L"bcd"; }
	BKSGE_CONSTEXPR static const wchar_t* bcde()    { return L"bcde"; }
	BKSGE_CONSTEXPR static const wchar_t* bbcd()    { return L"bbcd"; }
	BKSGE_CONSTEXPR static const wchar_t* c()    { return L"c"; }
	BKSGE_CONSTEXPR static const wchar_t* cb()    { return L"cb"; }
	BKSGE_CONSTEXPR static const wchar_t* cd()    { return L"cd"; }
	BKSGE_CONSTEXPR static const wchar_t* cba()    { return L"cba"; }
	BKSGE_CONSTEXPR static const wchar_t* cde()    { return L"cde"; }
	BKSGE_CONSTEXPR static const wchar_t* cdede()    { return L"cdede"; }
#if (BKSGE_CXX_STANDARD >= 14)
	/*BKSGE_CONSTEXPR*/ static bksge::basic_string<wchar_t> abcd_s()
	{
		using namespace bksge::string_literals;
		return L"abcd"s;
	}
#endif
};

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
template <>
struct StringTestHelper<char8_t>
{
	BKSGE_CONSTEXPR static char8_t  null_char()    { return u8'\0'; }
	BKSGE_CONSTEXPR static const char8_t* null_str()    { return u8""; }
	BKSGE_CONSTEXPR static const char8_t* long_str()    { return u8"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; }
	BKSGE_CONSTEXPR static const char8_t* multi_line_str()    { return u8"abc\nbcd\ncd"; }
	BKSGE_CONSTEXPR static const char8_t* csv_str()    { return u8"abc,bcd,cd"; }
	BKSGE_CONSTEXPR static char8_t comma_char()    { return u8','; }
	BKSGE_CONSTEXPR static const char8_t* acdcabe()    { return u8"acdcabe"; }
	BKSGE_CONSTEXPR static const char8_t* abcccde()    { return u8"abcccde"; }
	BKSGE_CONSTEXPR static const char8_t* aababc()    { return u8"aababc"; }
	BKSGE_CONSTEXPR static const char8_t* abaaae()    { return u8"abaaae"; }
	BKSGE_CONSTEXPR static const char8_t* abbccc()    { return u8"abbccc"; }
	BKSGE_CONSTEXPR static const char8_t* acdbc()    { return u8"acdbc"; }
	BKSGE_CONSTEXPR static const char8_t* accaa()    { return u8"accaa"; }
	BKSGE_CONSTEXPR static const char8_t* abcde()    { return u8"abcde"; }
	BKSGE_CONSTEXPR static const char8_t* abcb()    { return u8"abcb"; }
	BKSGE_CONSTEXPR static const char8_t* abcd()    { return u8"abcd"; }
	BKSGE_CONSTEXPR static const char8_t* abad()    { return u8"abad"; }
	BKSGE_CONSTEXPR static const char8_t* abb()    { return u8"abb"; }
	BKSGE_CONSTEXPR static const char8_t* abc()    { return u8"abc"; }
	BKSGE_CONSTEXPR static const char8_t* ab()    { return u8"ab"; }
	BKSGE_CONSTEXPR static const char8_t* ac()    { return u8"ac"; }
	BKSGE_CONSTEXPR static const char8_t* ace()    { return u8"ace"; }
	BKSGE_CONSTEXPR static const char8_t* a()    { return u8"a"; }
	BKSGE_CONSTEXPR static const char8_t* aaa()    { return u8"aaa"; }
	BKSGE_CONSTEXPR static const char8_t* bc()    { return u8"bc"; }
	BKSGE_CONSTEXPR static const char8_t* bcd()    { return u8"bcd"; }
	BKSGE_CONSTEXPR static const char8_t* bcde()    { return u8"bcde"; }
	BKSGE_CONSTEXPR static const char8_t* bbcd()    { return u8"bbcd"; }
	BKSGE_CONSTEXPR static const char8_t* c()    { return u8"c"; }
	BKSGE_CONSTEXPR static const char8_t* cb()    { return u8"cb"; }
	BKSGE_CONSTEXPR static const char8_t* cd()    { return u8"cd"; }
	BKSGE_CONSTEXPR static const char8_t* cba()    { return u8"cba"; }
	BKSGE_CONSTEXPR static const char8_t* cde()    { return u8"cde"; }
	BKSGE_CONSTEXPR static const char8_t* cdede()    { return u8"cdede"; }
#if (BKSGE_CXX_STANDARD >= 14)
	/*BKSGE_CONSTEXPR*/ static bksge::basic_string<char8_t> abcd_s()
	{
		using namespace bksge::literals::string_literals;
		return u8"abcd"s;
	}
#endif
};
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
template <>
struct StringTestHelper<char16_t>
{
	BKSGE_CONSTEXPR static char16_t  null_char()    { return u'\0'; }
	BKSGE_CONSTEXPR static const char16_t* null_str()    { return u""; }
	BKSGE_CONSTEXPR static const char16_t* long_str()    { return u"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; }
	BKSGE_CONSTEXPR static const char16_t* multi_line_str()    { return u"abc\nbcd\ncd"; }
	BKSGE_CONSTEXPR static const char16_t* csv_str()    { return u"abc,bcd,cd"; }
	BKSGE_CONSTEXPR static char16_t comma_char()    { return u','; }
	BKSGE_CONSTEXPR static const char16_t* acdcabe()    { return u"acdcabe"; }
	BKSGE_CONSTEXPR static const char16_t* abcccde()    { return u"abcccde"; }
	BKSGE_CONSTEXPR static const char16_t* aababc()    { return u"aababc"; }
	BKSGE_CONSTEXPR static const char16_t* abaaae()    { return u"abaaae"; }
	BKSGE_CONSTEXPR static const char16_t* abbccc()    { return u"abbccc"; }
	BKSGE_CONSTEXPR static const char16_t* acdbc()    { return u"acdbc"; }
	BKSGE_CONSTEXPR static const char16_t* accaa()    { return u"accaa"; }
	BKSGE_CONSTEXPR static const char16_t* abcde()    { return u"abcde"; }
	BKSGE_CONSTEXPR static const char16_t* abcb()    { return u"abcb"; }
	BKSGE_CONSTEXPR static const char16_t* abcd()    { return u"abcd"; }
	BKSGE_CONSTEXPR static const char16_t* abad()    { return u"abad"; }
	BKSGE_CONSTEXPR static const char16_t* abb()    { return u"abb"; }
	BKSGE_CONSTEXPR static const char16_t* abc()    { return u"abc"; }
	BKSGE_CONSTEXPR static const char16_t* ab()    { return u"ab"; }
	BKSGE_CONSTEXPR static const char16_t* ac()    { return u"ac"; }
	BKSGE_CONSTEXPR static const char16_t* ace()    { return u"ace"; }
	BKSGE_CONSTEXPR static const char16_t* a()    { return u"a"; }
	BKSGE_CONSTEXPR static const char16_t* aaa()    { return u"aaa"; }
	BKSGE_CONSTEXPR static const char16_t* bc()    { return u"bc"; }
	BKSGE_CONSTEXPR static const char16_t* bcd()    { return u"bcd"; }
	BKSGE_CONSTEXPR static const char16_t* bcde()    { return u"bcde"; }
	BKSGE_CONSTEXPR static const char16_t* bbcd()    { return u"bbcd"; }
	BKSGE_CONSTEXPR static const char16_t* c()    { return u"c"; }
	BKSGE_CONSTEXPR static const char16_t* cb()    { return u"cb"; }
	BKSGE_CONSTEXPR static const char16_t* cd()    { return u"cd"; }
	BKSGE_CONSTEXPR static const char16_t* cba()    { return u"cba"; }
	BKSGE_CONSTEXPR static const char16_t* cde()    { return u"cde"; }
	BKSGE_CONSTEXPR static const char16_t* cdede()    { return u"cdede"; }
#if (BKSGE_CXX_STANDARD >= 14)
	/*BKSGE_CONSTEXPR*/ static bksge::basic_string<char16_t> abcd_s()
	{
		using namespace bksge::literals::string_literals;
		return u"abcd"s;
	}
#endif
};
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
template <>
struct StringTestHelper<char32_t>
{
	BKSGE_CONSTEXPR static char32_t  null_char()    { return U'\0'; }
	BKSGE_CONSTEXPR static const char32_t* null_str()    { return U""; }
	BKSGE_CONSTEXPR static const char32_t* long_str()    { return U"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; }
	BKSGE_CONSTEXPR static const char32_t* multi_line_str()    { return U"abc\nbcd\ncd"; }
	BKSGE_CONSTEXPR static const char32_t* csv_str()    { return U"abc,bcd,cd"; }
	BKSGE_CONSTEXPR static char32_t comma_char()    { return U','; }
	BKSGE_CONSTEXPR static const char32_t* acdcabe()    { return U"acdcabe"; }
	BKSGE_CONSTEXPR static const char32_t* abcccde()    { return U"abcccde"; }
	BKSGE_CONSTEXPR static const char32_t* aababc()    { return U"aababc"; }
	BKSGE_CONSTEXPR static const char32_t* abaaae()    { return U"abaaae"; }
	BKSGE_CONSTEXPR static const char32_t* abbccc()    { return U"abbccc"; }
	BKSGE_CONSTEXPR static const char32_t* acdbc()    { return U"acdbc"; }
	BKSGE_CONSTEXPR static const char32_t* accaa()    { return U"accaa"; }
	BKSGE_CONSTEXPR static const char32_t* abcde()    { return U"abcde"; }
	BKSGE_CONSTEXPR static const char32_t* abcb()    { return U"abcb"; }
	BKSGE_CONSTEXPR static const char32_t* abcd()    { return U"abcd"; }
	BKSGE_CONSTEXPR static const char32_t* abad()    { return U"abad"; }
	BKSGE_CONSTEXPR static const char32_t* abb()    { return U"abb"; }
	BKSGE_CONSTEXPR static const char32_t* abc()    { return U"abc"; }
	BKSGE_CONSTEXPR static const char32_t* ab()    { return U"ab"; }
	BKSGE_CONSTEXPR static const char32_t* ac()    { return U"ac"; }
	BKSGE_CONSTEXPR static const char32_t* ace()    { return U"ace"; }
	BKSGE_CONSTEXPR static const char32_t* a()    { return U"a"; }
	BKSGE_CONSTEXPR static const char32_t* aaa()    { return U"aaa"; }
	BKSGE_CONSTEXPR static const char32_t* bc()    { return U"bc"; }
	BKSGE_CONSTEXPR static const char32_t* bcd()    { return U"bcd"; }
	BKSGE_CONSTEXPR static const char32_t* bcde()    { return U"bcde"; }
	BKSGE_CONSTEXPR static const char32_t* bbcd()    { return U"bbcd"; }
	BKSGE_CONSTEXPR static const char32_t* c()    { return U"c"; }
	BKSGE_CONSTEXPR static const char32_t* cb()    { return U"cb"; }
	BKSGE_CONSTEXPR static const char32_t* cd()    { return U"cd"; }
	BKSGE_CONSTEXPR static const char32_t* cba()    { return U"cba"; }
	BKSGE_CONSTEXPR static const char32_t* cde()    { return U"cde"; }
	BKSGE_CONSTEXPR static const char32_t* cdede()    { return U"cdede"; }
#if (BKSGE_CXX_STANDARD >= 14)
	/*BKSGE_CONSTEXPR*/ static bksge::basic_string<char32_t> abcd_s()
	{
		using namespace bksge::literals::string_literals;
		return U"abcd"s;
	}
#endif
};
#endif

template <typename T>
class MyAllocator
{
public:
	using value_type                             = T;
	using size_type                              = std::size_t;
	using difference_type                        = std::ptrdiff_t;
	using propagate_on_container_copy_assignment = bksge::true_type;
	using propagate_on_container_move_assignment = bksge::true_type;
	using is_always_equal                        = bksge::false_type;

	constexpr MyAllocator() noexcept {}

	constexpr MyAllocator(MyAllocator const&) noexcept = default;

	template <typename U>
	constexpr MyAllocator(MyAllocator<U> const&) noexcept {}

	BKSGE_NODISCARD T* allocate(std::size_t count)
	{
		return (T*)std::malloc(sizeof(T) * count);
	}

	void deallocate(T* ptr, std::size_t count)
	{
		(void)count;
		std::free(ptr);
	}
};

template <typename T, typename U>
BKSGE_NODISCARD bool operator==(MyAllocator<T> const&, MyAllocator<U> const&) noexcept
{
    return false;
}

template <typename T, typename U>
BKSGE_NODISCARD bool operator!=(MyAllocator<T> const&, MyAllocator<U> const&) noexcept
{
    return true;
}

template <typename T>
class MyAllocator2
{
public:
	using value_type                             = T;
	using size_type                              = std::size_t;
	using difference_type                        = std::ptrdiff_t;
	using propagate_on_container_copy_assignment = bksge::true_type;
	using propagate_on_container_move_assignment = bksge::true_type;
	using is_always_equal                        = bksge::false_type;

	constexpr MyAllocator2() noexcept {}

	constexpr MyAllocator2(MyAllocator2 const&) noexcept = default;

	template <typename U>
	constexpr MyAllocator2(MyAllocator2<U> const&) noexcept {}

	BKSGE_NODISCARD T* allocate(std::size_t count)
	{
		return (T*)std::malloc(sizeof(T) * count);
	}

	void deallocate(T* ptr, std::size_t count)
	{
		(void)count;
		std::free(ptr);
	}
};

template <typename T, typename U>
BKSGE_NODISCARD bool operator==(MyAllocator2<T> const&, MyAllocator2<U> const&) noexcept
{
    return true;
}

template <typename T, typename U>
BKSGE_NODISCARD bool operator!=(MyAllocator2<T> const&, MyAllocator2<U> const&) noexcept
{
    return false;
}

template <typename T>
class MyAllocator3
{
public:
	using value_type                             = T;
	using size_type                              = std::size_t;
	using difference_type                        = std::ptrdiff_t;
	using propagate_on_container_copy_assignment = bksge::true_type;
	using propagate_on_container_move_assignment = bksge::false_type;
	using is_always_equal                        = bksge::false_type;

	constexpr MyAllocator3() noexcept {}

	constexpr MyAllocator3(MyAllocator3 const&) noexcept = default;

	template <typename U>
	constexpr MyAllocator3(MyAllocator3<U> const&) noexcept {}

	BKSGE_NODISCARD T* allocate(std::size_t count)
	{
		return (T*)std::malloc(sizeof(T) * count);
	}

	void deallocate(T* ptr, std::size_t count)
	{
		(void)count;
		std::free(ptr);
	}
};

template <typename T, typename U>
BKSGE_NODISCARD bool operator==(MyAllocator3<T> const&, MyAllocator3<U> const&) noexcept
{
    return false;
}

template <typename T, typename U>
BKSGE_NODISCARD bool operator!=(MyAllocator3<T> const&, MyAllocator3<U> const&) noexcept
{
    return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorDefaultTest()
{
	using string = bksge::basic_string<CharT>;

	// (1) basic_string::basic_string()
	{
		string s;
		VERIFY(s.length() == 0);
		VERIFY(s.size()   == 0);
		VERIFY(s.data()   != nullptr);
		VERIFY(s.empty());
		VERIFY(s.max_size() >= s.size());
	}
	{
		string s{};
		VERIFY(s.length() == 0);
		VERIFY(s.size()   == 0);
		VERIFY(s.data()   != nullptr);
		VERIFY(s.empty());
		VERIFY(s.max_size() >= s.size());
	}
	{
		string s = {};
		VERIFY(s.length() == 0);
		VERIFY(s.size()   == 0);
		VERIFY(s.data()   != nullptr);
		VERIFY(s.empty());
		VERIFY(s.max_size() >= s.size());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorAllocatorTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;

	// (1) basic_string::basic_string(Allocator const&)
	{
		string s{Allocator()};
		VERIFY(s.length() == 0);
		VERIFY(s.size()   == 0);
		VERIFY(s.data()   != nullptr);
		VERIFY(s.empty());
		VERIFY(s.max_size() >= s.size());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorCountCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (2) basic_string::basic_string(size_type count, CharT)
	{
		CharT c = Helper::abc()[0];	// 'a'
		string s(3, c);
		VERIFY(s.length() == 3);
		VERIFY(s.size()   == 3);
		VERIFY(!s.empty());
		VERIFY(s[0] == c);
		VERIFY(s[1] == c);
		VERIFY(s[2] == c);
	}
	// (2) basic_string::basic_string(size_type count, CharT, Allocator const&)
	{
		CharT c = Helper::abc()[1];	// 'b'
		string s(4, c, Allocator());
		VERIFY(s.length() == 4);
		VERIFY(s.size()   == 4);
		VERIFY(!s.empty());
		VERIFY(s[0] == c);
		VERIFY(s[1] == c);
		VERIFY(s[2] == c);
		VERIFY(s[3] == c);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringPosTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (3) basic_string::basic_string(basic_string const&, size_type pos)
	{
		auto p = Helper::abc();
		string const s1(p);
		string const s2(s1, 1);
		VERIFY(s2.length() == 2);
		VERIFY(s2.size()   == 2);
		VERIFY(!s2.empty());
		VERIFY(s2 == Helper::bc());
		VERIFY(s2 != Helper::abc());
	}
	// (3) basic_string::basic_string(basic_string const&, size_type pos, Allocator const&)
	{
		auto p = Helper::abc();
		string const s1(p);
		string const s2(s1, 3, Allocator());
		VERIFY(s2.length() == 0);
		VERIFY(s2.size()   == 0);
		VERIFY(s2.empty());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (3) basic_string::basic_string(basic_string const&, size_type pos, size_type count)
	{
		auto p = Helper::abcde();
		string const s1(p);
		string const s2(s1, 1, 3);
		VERIFY(s2.length() == 3);
		VERIFY(s2.size()   == 3);
		VERIFY(!s2.empty());
		VERIFY(s2 == Helper::bcd());
		VERIFY(s2 != Helper::abcde());
	}
	// (3) basic_string::basic_string(basic_string const&, size_type pos, size_type count, Allocator const&)
	{
		auto p = Helper::abcde();
		string const s1(p);
		string const s2(s1, 1, 4, Allocator());
		VERIFY(s2.length() == 4);
		VERIFY(s2.size()   == 4);
		VERIFY(!s2.empty());
		VERIFY(s2 == Helper::bcde());
		VERIFY(s2 != Helper::abcde());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (4) basic_string::basic_string(CharT* const, size_type count)
	{
		string const s(Helper::abcde(), 3);
		VERIFY(s.length() == 3);
		VERIFY(s.size()   == 3);
		VERIFY(!s.empty());
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcde());
	}
	// (4) basic_string::basic_string(CharT* const, size_type count, Allocator const&)
	{
		string const s(Helper::abcde(), 4, Allocator());
		VERIFY(s.length() == 4);
		VERIFY(s.size()   == 4);
		VERIFY(!s.empty());
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abcde());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (5) basic_string::basic_string(CharT* const)
	{
		string const s(Helper::abcde());
		VERIFY(s.length() == 5);
		VERIFY(s.size()   == 5);
		VERIFY(!s.empty());
		VERIFY(s == Helper::abcde());
		VERIFY(s != Helper::abcd());
	}
	{
		string const s(Helper::long_str());
		VERIFY(s == Helper::long_str());
	}
	// (5) basic_string::basic_string(CharT* const, Allocator const&)
	{
		string const s(Helper::abcd(), Allocator());
		VERIFY(s.length() == 4);
		VERIFY(s.size()   == 4);
		VERIFY(!s.empty());
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abcde());
	}
	{
		string const s(Helper::long_str(), Allocator());
		VERIFY(s == Helper::long_str());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorIteratorTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (6) basic_string::basic_string(InputIt first, InputIt last)
	{
		string const s(Helper::abcde(), Helper::abcde()+2);
		VERIFY(s.length() == 2);
		VERIFY(s.size()   == 2);
		VERIFY(!s.empty());
		VERIFY(s == Helper::ab());
		VERIFY(s != Helper::abcde());
	}
	{
		//input_iterator_wrapper<CharT const> first {Helper::abcde()};
		//input_iterator_wrapper<CharT const> last  {Helper::abcde()+5};
		//string const s(first, last);
		//VERIFY(s == Helper::abcde());
	}
	// (6) basic_string::basic_string(InputIt first, InputIt last, Allocator const&)
	{
		string const s(Helper::abcde(), Helper::abcde()+3, Allocator());
		VERIFY(s.length() == 3);
		VERIFY(s.size()   == 3);
		VERIFY(!s.empty());
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcde());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorCopyTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (7) basic_string::basic_string(basic_string const&)
	{
		string const s1(Helper::abcde());
		string const s2(s1);
		VERIFY(s2.length() == 5);
		VERIFY(s2.size()   == 5);
		VERIFY(!s2.empty());
		VERIFY(s2 == Helper::abcde());
		VERIFY(s2 != Helper::abcd());
	}
	{
		string const s1(Helper::long_str());
		string const s2(s1);
		VERIFY(s2 == Helper::long_str());
	}
	// (7) basic_string::basic_string(basic_string const&, Allocator const&)
	{
		string const s1(Helper::abcd());
		string const s2(s1, Allocator());
		VERIFY(s2.length() == 4);
		VERIFY(s2.size()   == 4);
		VERIFY(!s2.empty());
		VERIFY(s2 == Helper::abcd());
		VERIFY(s2 != Helper::abcde());
	}
	{
		string const s1(Helper::long_str());
		string const s2(s1, Allocator());
		VERIFY(s2 == Helper::long_str());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorMoveTest()
{
	using string = bksge::basic_string<CharT>;
	using string2 = bksge::basic_string<CharT, bksge::char_traits<CharT>, MyAllocator<CharT>>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (8) basic_string::basic_string(basic_string&&)
	{
		string s1(Helper::abcde());
		string const s2(std::move(s1));
		VERIFY(s2.length() == 5);
		VERIFY(s2.size()   == 5);
		VERIFY(!s2.empty());
		VERIFY(s2 == Helper::abcde());
		VERIFY(s2 != Helper::abcd());
	}
	{
		string s1(Helper::long_str());
		string const s2(std::move(s1));
		VERIFY(s2 == Helper::long_str());
	}
	// (8) basic_string::basic_string(basic_string&&, Allocator const&)
	{
		string s1(Helper::abcd());
		string const s2(std::move(s1), Allocator());
		VERIFY(s2.length() == 4);
		VERIFY(s2.size()   == 4);
		VERIFY(!s2.empty());
		VERIFY(s2 == Helper::abcd());
		VERIFY(s2 != Helper::abcde());
	}
	{
		string s1(Helper::long_str(), Allocator());
		string const s2(std::move(s1));
		VERIFY(s2 == Helper::long_str());
	}
	{
		string2 s1(Helper::long_str());
		string2 const s2(std::move(s1), MyAllocator<CharT>());
		VERIFY(s2 == Helper::long_str());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorInitializerListTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (9) basic_string::basic_string(initializer_list<CharT>)
	{
		auto p = Helper::abcde();
		string const s({p[2], p[1], p[0]});	// { 'c', 'b', 'a' }
		VERIFY(s.length() == 3);
		VERIFY(s.size()   == 3);
		VERIFY(!s.empty());
		VERIFY(s == Helper::cba());
		VERIFY(s != Helper::abcde());
	}
	// (9) basic_string::basic_string(initializer_list<CharT>, Allocator const&)
	{
		auto p = Helper::abcde();
		string const s({p[2], p[3], p[4]}, Allocator());	// { 'c', 'd', 'e' }
		VERIFY(s.length() == 3);
		VERIFY(s.size()   == 3);
		VERIFY(!s.empty());
		VERIFY(s == Helper::cde());
		VERIFY(s != Helper::abcde());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (10) basic_string::basic_string(T const& sv)
	{
		string_view const s1(Helper::abcde());
		string const s2(s1);
		VERIFY(s2.length() == 5);
		VERIFY(s2 == Helper::abcde());
	}
	{
		string_view const s1(Helper::long_str());
		string const s2(s1);
		VERIFY(s2 == Helper::long_str());
	}
	// (10) basic_string::basic_string(T const& sv, Allocator const&)
	{
		string_view const s1(Helper::abcd());
		string const s2(s1, Allocator());
		VERIFY(s2.length() == 4);
		VERIFY(s2 == Helper::abcd());
	}
	{
		string_view const s1(Helper::long_str());
		string const s2(s1, Allocator());
		VERIFY(s2 == Helper::long_str());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorStringViewPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (11) basic_string::basic_string(T const& sv, size_type pos, size_type n)
	{
		string_view const s1(Helper::abcde());
		string const s2(s1, 1, 3);
		VERIFY(s2.length() == 3);
		VERIFY(s2 == Helper::bcd());
		VERIFY(s2 != Helper::abcde());
	}
	// (11) basic_string::basic_string(T const& sv, size_type pos, size_type n, Allocator const&)
	{
		string_view const s1(Helper::abcde());
		string const s2(s1, 1, 3, Allocator());
		VERIFY(s2.length() == 3);
		VERIFY(s2 == Helper::bcd());
		VERIFY(s2 != Helper::abcde());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CtorDeductionTest()
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// (1) basic_string(InputIt first, InputIt last, alloc = Alloc())
	{
		auto p = Helper::abcd();
		bksge::basic_string s(p, p + 2);
		static_assert(bksge::is_same<decltype(s), string>::value, "");
		VERIFY(s == Helper::ab());
	}
	{
		auto p = Helper::abcd();
		bksge::basic_string s(p, p + 2, Allocator());
		static_assert(bksge::is_same<decltype(s), string>::value, "");
		VERIFY(s == Helper::ab());
	}
	// (2) basic_string(basic_string_view, alloc = Alloc())
	{
		string_view const sv(Helper::abcde());
		bksge::basic_string s(sv);
		static_assert(bksge::is_same<decltype(s), string>::value, "");
		VERIFY(s == Helper::abcde());
	}
	{
		string_view const sv(Helper::abcde());
		bksge::basic_string s(sv, Allocator());
		static_assert(bksge::is_same<decltype(s), string>::value, "");
		VERIFY(s == Helper::abcde());
	}
	// (3) basic_string(basic_string_view, size_type pos, size_type n, alloc = Alloc())
	{
		// TODO
		//string_view const sv(Helper::abcde());
		//bksge::basic_string s(sv, 1, 3);
		//static_assert(bksge::is_same<decltype(s), string>::value, "");
		//VERIFY(s == Helper::bcd());
	}
	{
		string_view const sv(Helper::abcde());
		bksge::basic_string s(sv, 1, 3, Allocator());
		static_assert(bksge::is_same<decltype(s), string>::value, "");
		VERIFY(s == Helper::bcd());
	}
#endif
	return true;
}

TYPED_TEST(BasicStringTest, CtorTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorDefaultTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorAllocatorTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorCountCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringPosTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringPosCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorCharPtrCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorIteratorTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorCopyTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorMoveTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorInitializerListTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringViewPosCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorDeductionTest<CharT>());

	// (6) basic_string::basic_string(InputIt first, InputIt last)
	{
		std::vector<CharT> vec;
		vec.push_back(Helper::abcde()[0]);
		vec.push_back(Helper::abcde()[1]);
		vec.push_back(Helper::abcde()[2]);
		vec.push_back(Helper::abcde()[3]);
		vec.push_back(Helper::abcde()[4]);

		string const s(vec.begin(), vec.end());
		EXPECT_TRUE(s == Helper::abcde());
	}

	// Exceptions Test

	// 3) Throws out_of_range if pos > other.size()
	{
		string const s1(Helper::abc());
		EXPECT_THROW(string s2(s1, 4); (void)s2;, bksge::out_of_range);
	}
	{
		string const s1(Helper::abc());
		EXPECT_THROW(string s2(s1, 4, Allocator()); (void)s2;, bksge::out_of_range);
	}

	// TODO
	// 8) Throws nothing if alloc == str.get_allocator()
	{
	}

	// 11) Throws out_of_range if pos is out of range
	{
		string_view const sv(Helper::abcde());
		EXPECT_THROW(string const s2(sv, 6, 1, Allocator()); (void)s2;, bksge::out_of_range);
	}

	// Throws length_error if the length of the constructed string woule exceed max_size()
	{
		string const s1;
		auto const c = Helper::abc()[0];	// 'a'
		EXPECT_THROW(string const s2(s1.max_size() + 1, c); (void)s2;, bksge::length_error);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignOperatorCopyTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) operator=(basic_string const&)
	{
		string s;
		VERIFY(s.empty());

		string const t1(Helper::abcd());
		s = t1;
		VERIFY(!s.empty());
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abc());
		VERIFY(s == t1);

		string const t2(Helper::abc());
		s = t2;
		VERIFY(!s.empty());
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcd());
		VERIFY(s == t2);
		VERIFY(s != t1);
	}
	{
		string s;
		VERIFY(s.empty());

		string const t1(Helper::long_str());
		s = t1;
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());
		VERIFY(s == t1);

		string const t2(Helper::null_str());
		s = t2;
		VERIFY(s.empty());
		VERIFY(s == t2);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignOperatorMoveTest()
{
	using string = bksge::basic_string<CharT>;
	using string2 = bksge::basic_string<CharT, bksge::char_traits<CharT>, MyAllocator<CharT>>;
	using string3 = bksge::basic_string<CharT, bksge::char_traits<CharT>, MyAllocator2<CharT>>;
	using string4 = bksge::basic_string<CharT, bksge::char_traits<CharT>, MyAllocator3<CharT>>;
	using Helper = StringTestHelper<CharT>;

	// (2) operator=(basic_string &&)
	{
		string s;
		VERIFY(s.empty());

		s = string(Helper::abcd());
		VERIFY(!s.empty());
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abc());

		s = string(Helper::abc());
		VERIFY(!s.empty());
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcd());
	}
	{
		string s;
		VERIFY(s.empty());

		s = string(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string(Helper::null_str());
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
	}
	{
		string2 s;
		VERIFY(s.empty());

		s = string2(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string2(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string2(Helper::null_str());
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
	}
	{
		string3 s;
		VERIFY(s.empty());

		s = string3(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string3(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string3(Helper::null_str());
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
	}
	{
		string4 s;
		VERIFY(s.empty());

		s = string4(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string4(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = string4(Helper::null_str());
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignOperatorCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) operator=(CharT const*)
	{
		string s;
		VERIFY(s.empty());

		s = Helper::abcde();
		VERIFY(!s.empty());
		VERIFY(s == Helper::abcde());
		VERIFY(s != Helper::cde());

		s = Helper::cde();
		VERIFY(!s.empty());
		VERIFY(s == Helper::cde());
		VERIFY(s != Helper::abcde());
	}
	{
		string s;
		VERIFY(s.empty());

		s = Helper::long_str();
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());

		s = Helper::null_str();
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignOperatorCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) operator=(CharT)
	{
		string s;
		VERIFY(s.empty());

		s = Helper::abcde()[0];	// 'a'
		VERIFY(!s.empty());
		VERIFY(s.length() == 1);
		VERIFY(s[0] == Helper::abcde()[0]);

		s = Helper::abcde()[2];	// 'c'
		VERIFY(!s.empty());
		VERIFY(s.length() == 1);
		VERIFY(s[0] == Helper::abcde()[2]);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignOperatorInitializerListTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) operator=(initializer_list<CharT>)
	{
		string s;
		VERIFY(s.empty());

		auto p = Helper::abcde();
		s = { p[0], p[2], p[4] };	// { 'a', 'c', 'e' }
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::ace());

		s = { p[2], p[1] };	// { 'c', 'b' }
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::cb());
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignOperatorStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (6) operator=(T const& sv)
	{
		string s;
		VERIFY(s.empty());

		string_view const t1(Helper::abcd());
		s = t1;
		VERIFY(!s.empty());
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abc());
		VERIFY(s == t1);

		string_view const t2(Helper::abc());
		s = t2;
		VERIFY(!s.empty());
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcd());
		VERIFY(s == t2);
		VERIFY(s != t1);
	}
	{
		string s;
		VERIFY(s.empty());

		string_view const t1(Helper::long_str());
		s = t1;
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());
		VERIFY(s == t1);

		string_view const t2(Helper::null_str());
		s = t2;
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
		VERIFY(s == t2);
	}
	return true;
}

TYPED_TEST(BasicStringTest, AssignOperatorTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignOperatorCopyTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignOperatorMoveTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignOperatorCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignOperatorCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignOperatorInitializerListTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignOperatorStringViewTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignCountCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) assign(size_type count, CharT)
	{
		string s;
		VERIFY(s.empty());

		auto const c1 = Helper::abcd()[0];	// 'a'
		auto r1 = s.assign(1, c1);
		VERIFY(s.length() == 1);
		VERIFY(s == Helper::a());
		VERIFY(s != Helper::abcd());
		VERIFY(s[0] == c1);
		VERIFY(r1 == s);

		auto const c2 = Helper::abcd()[1];	// 'b'
		auto r2 = s.assign(3, c2);
		VERIFY(s.length() == 3);
		VERIFY(s != Helper::abcd());
		VERIFY(s[0] == c2);
		VERIFY(s[1] == c2);
		VERIFY(s[2] == c2);
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignCopyTest()
{
	using string = bksge::basic_string<CharT>;
	using string2 = bksge::basic_string<CharT, bksge::char_traits<CharT>, MyAllocator<CharT>>;
	using Helper = StringTestHelper<CharT>;

	// (2) assign(basic_string const&)
	{
		string s;
		VERIFY(s.empty());

		string const t1(Helper::abcd());
		auto r1 = s.assign(t1);
		VERIFY(s.length() == 4);
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abc());
		VERIFY(s == t1);
		VERIFY(r1 == s);

		string const t2(Helper::abc());
		auto r2 = s.assign(t2);
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcd());
		VERIFY(s == t2);
		VERIFY(s != t1);
		VERIFY(r2 == s);
	}
	{
		string s;
		VERIFY(s.empty());

		string const t1(Helper::long_str());
		auto r1 = s.assign(t1);
		VERIFY(s == Helper::long_str());
		VERIFY(s == t1);
		VERIFY(r1 == s);

		string const t2(Helper::null_str());
		auto r2 = s.assign(t2);
		VERIFY(s == Helper::null_str());
		VERIFY(s == t2);
		VERIFY(r2 == s);
	}
	{
		string2 s;
		VERIFY(s.empty());

		string2 const t1(Helper::long_str());
		auto r1 = s.assign(t1);
		VERIFY(s == Helper::long_str());
		VERIFY(s == t1);
		VERIFY(r1 == s);

		s.assign(t1);
		VERIFY(s == Helper::long_str());

		string2 const t2(Helper::null_str());
		auto r2 = s.assign(t2);
		VERIFY(s == Helper::null_str());
		VERIFY(s == t2);
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignCopyPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) assign(basic_string const&, size_type pos)
	{
		string s;
		VERIFY(s.empty());

		string const t(Helper::abcd());

		auto r1 = s.assign(t, 1);
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::bcd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r1 == s);

		auto r2 = s.assign(t, 2);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::cd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r2 == s);
	}
	// (3) assign(basic_string const&, size_type pos, size_type count)
	{
		string s;
		VERIFY(s.empty());

		string const t(Helper::abcd());

		auto r1 = s.assign(t, 1, 2);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::bc());
		VERIFY(s != Helper::bcd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r1 == s);

		auto r2 = s.assign(t, 2, 5);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::cd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignMoveTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) assign(basic_string &&)
	{
		string s;
		VERIFY(s.empty());

		auto r1 = s.assign(string(Helper::abcd()));
		VERIFY(s.length() == 4);
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abc());
		VERIFY(r1 == s);

		auto r2 = s.assign(string(Helper::abc()));
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcd());
		VERIFY(r2 == s);
	}
	{
		string s;
		VERIFY(s.empty());

		auto r1 = s.assign(string(Helper::long_str()));
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());
		VERIFY(r1 == s);

		auto r2 = s.assign(string(Helper::null_str()));
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharPtrCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) assign(CharT const*, size_type count)
	{
		string s;
		VERIFY(s.empty());

		auto r1 = s.assign(Helper::abcde(), 3);
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcde());
		VERIFY(r1 == s);

		auto r2 = s.assign(Helper::cde(), 2);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::cd());
		VERIFY(s != Helper::cde());
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (6) assign(CharT const*)
	{
		string s;
		VERIFY(s.empty());

		auto r1 = s.assign(Helper::abcde());
		VERIFY(s.length() == 5);
		VERIFY(s == Helper::abcde());
		VERIFY(s != Helper::cde());
		VERIFY(r1 == s);

		auto r2 = s.assign(Helper::cde());
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::cde());
		VERIFY(s != Helper::abcde());
		VERIFY(r2 == s);
	}
	{
		string s;
		VERIFY(s.empty());

		auto r1 = s.assign(Helper::long_str());
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());
		VERIFY(r1 == s);

		auto r2 = s.assign(Helper::null_str());
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignIteratorTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (7) assign(InputIt first, InputIt last)
	{
		string s;
		VERIFY(s.empty());

		auto p = Helper::abcde();
		auto r1 = s.assign(p, p + 2);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::ab());
		VERIFY(s != p);
		VERIFY(r1 == s);

		auto r2 = s.assign(p + 1, p + 5);
		VERIFY(s.length() == 4);
		VERIFY(s == Helper::bcde());
		VERIFY(s != p);
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignInitializerListTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (8) assign(initializer_list<CharT>)
	{
		string s;
		VERIFY(s.empty());

		auto p = Helper::abcde();
		auto r1 = s.assign({ p[0], p[2], p[4] });	// { 'a', 'c', 'e' }
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::ace());
		VERIFY(s != p);
		VERIFY(r1 == s);

		auto r2 = s.assign({ p[2], p[1] });	// { 'c', 'b' }
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::cb());
		VERIFY(s != p);
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (9) assign(T const& sv)
	{
		string s;
		VERIFY(s.empty());

		string_view const t1(Helper::abcd());
		auto r1 = s.assign(t1);
		VERIFY(s.length() == 4);
		VERIFY(s == Helper::abcd());
		VERIFY(s != Helper::abc());
		VERIFY(s == t1);
		VERIFY(r1 == s);

		string_view const t2(Helper::abc());
		auto r2 = s.assign(t2);
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::abc());
		VERIFY(s != Helper::abcd());
		VERIFY(s == t2);
		VERIFY(s != t1);
		VERIFY(r2 == s);
	}
	{
		string s;
		VERIFY(s.empty());

		string_view const t1(Helper::long_str());
		auto r1 = s.assign(t1);
		VERIFY(!s.empty());
		VERIFY(s == Helper::long_str());
		VERIFY(s == t1);
		VERIFY(r1 == s);

		string_view const t2(Helper::null_str());
		auto r2 = s.assign(t2);
		VERIFY(s.empty());
		VERIFY(s == Helper::null_str());
		VERIFY(s == t2);
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AssignStringViewPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (10) assign(T const& sv, size_type pos)
	{
		string s;
		VERIFY(s.empty());

		string_view const t(Helper::abcd());

		auto r1 = s.assign(t, 1);
		VERIFY(s.length() == 3);
		VERIFY(s == Helper::bcd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r1 == s);

		auto r2 = s.assign(t, 2);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::cd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r2 == s);
	}
	// (10) assign(T const& sv, size_type pos, size_type count)
	{
		string s;
		VERIFY(s.empty());

		string_view const t(Helper::abcd());

		auto r1 = s.assign(t, 1, 2);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::bc());
		VERIFY(s != Helper::bcd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r1 == s);

		auto r2 = s.assign(t, 2, 5);
		VERIFY(s.length() == 2);
		VERIFY(s == Helper::cd());
		VERIFY(s != Helper::abcd());
		VERIFY(s != t);
		VERIFY(r2 == s);
	}
	return true;
}

TYPED_TEST(BasicStringTest, AssignTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignCountCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignCopyTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignCopyPosCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignMoveTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignCharPtrCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignIteratorTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignInitializerListTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AssignStringViewPosCountTest<CharT>());

	// Exceptions Test
	// If an exception is thrown for any reason, this function has no effect

	// 3) If pos > str.size(), out_of_range is thrown.
	{
		string const s1 = Helper::abcd();
		string s2 = Helper::abc();
		EXPECT_THROW(s2.assign(s1, 5), bksge::out_of_range);
		EXPECT_TRUE(s2 == Helper::abc());
	}
	{
		string const s1 = Helper::abcd();
		string s2 = Helper::abc();
		EXPECT_THROW(s2.assign(s1, 5, 1), bksge::out_of_range);
		EXPECT_TRUE(s2 == Helper::abc());
	}

	// 10) If pos > sv.size(), out_of_range is thrown
	{
		string_view const s1 = Helper::abcd();
		string s2 = Helper::abc();
		EXPECT_THROW(s2.assign(s1, 5), bksge::out_of_range);
		EXPECT_TRUE(s2 == Helper::abc());
	}
	{
		string_view const s1 = Helper::abcd();
		string s2 = Helper::abc();
		EXPECT_THROW(s2.assign(s1, 5, 1), bksge::out_of_range);
		EXPECT_TRUE(s2 == Helper::abc());
	}

	// Throws length_error if the length of the constructed string woule exceed max_size()
	{
		string s = Helper::abcd();
		auto const c = Helper::abc()[0];	// 'a'
		EXPECT_THROW(s.assign(s.max_size() + 1, c), bksge::length_error);
		EXPECT_TRUE(s == Helper::abcd());
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool GetAllocatorTest()
{
	using string = bksge::basic_string<CharT>;
	using Allocator = typename string::allocator_type;

	{
		string const s1;
		string const s2{Allocator()};
		VERIFY(s1.get_allocator() == s2.get_allocator());
		VERIFY(s1.get_allocator() == Allocator());
	}

	return true;
}
TYPED_TEST(BasicStringTest, GetAllocatorTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(GetAllocatorTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		VERIFY(s.at(0) == p[0]);
		VERIFY(s.at(1) == p[1]);
		VERIFY(s.at(2) == p[2]);
		VERIFY(s.at(3) == p[3]);
		s.at(2) = p[0];
		VERIFY(s == Helper::abad());
	}
	{
		auto p = Helper::cde();
		string const s = p;
		VERIFY(s.at(0) == p[0]);
		VERIFY(s.at(1) == p[1]);
		VERIFY(s.at(2) == p[2]);
	}

	return true;
}
TYPED_TEST(BasicStringTest, AtTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AtTest<CharT>());

	// Exceptions Test
	// Throws out_of_range if pos >= size().
	{
		string s = Helper::abcd();
		EXPECT_THROW((void)s.at(4), bksge::out_of_range);
	}
	{
		string const s = Helper::cde();
		EXPECT_THROW((void)s.at(3), bksge::out_of_range);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorBracketTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
		s[2] = p[0];
		VERIFY(s == Helper::abad());
	}
	{
		auto p = Helper::cde();
		string const s = p;
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
	}

	return true;
}
TYPED_TEST(BasicStringTest, OperatorBracketTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorBracketTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FrontTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		VERIFY(s.front() == p[0]);
		s.front() = p[1];
		VERIFY(s == Helper::bbcd());
	}
	{
		auto p = Helper::cde();
		string const s = p;
		VERIFY(s.front() == p[0]);
	}

	return true;
}
TYPED_TEST(BasicStringTest, FrontTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(FrontTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool BackTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		VERIFY(s.back() == p[3]);
		s.back() = p[1];
		VERIFY(s == Helper::abcb());
	}
	{
		auto p = Helper::cde();
		string const s = p;
		VERIFY(s.back() == p[2]);
	}

	return true;
}
TYPED_TEST(BasicStringTest, BackTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(BackTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		VERIFY(s.data() != p);
		VERIFY(s.data()[0] == p[0]);
		VERIFY(s.data()[1] == p[1]);
		VERIFY(s.data()[2] == p[2]);
		VERIFY(s.data()[3] == p[3]);
		VERIFY(s.data()[4] == p[4]);
		VERIFY(s.data() + 0 == bksge::addressof(s[0]));
		VERIFY(s.data() + 1 == bksge::addressof(s[1]));
		VERIFY(s.data() + 2 == bksge::addressof(s[2]));
		VERIFY(s.data() + 3 == bksge::addressof(s[3]));
		VERIFY(s.data() + 4 == bksge::addressof(s[4]));
	}
	{
		auto p = Helper::cde();
		string const s = p;
		VERIFY(s.data() != p);
		VERIFY(s.data()[0] == p[0]);
		VERIFY(s.data()[1] == p[1]);
		VERIFY(s.data()[2] == p[2]);
		VERIFY(s.data()[3] == p[3]);
		VERIFY(s.data() + 0 == bksge::addressof(s[0]));
		VERIFY(s.data() + 1 == bksge::addressof(s[1]));
		VERIFY(s.data() + 2 == bksge::addressof(s[2]));
		VERIFY(s.data() + 3 == bksge::addressof(s[3]));
	}
	{
		auto p = Helper::long_str();
		string s = p;
		VERIFY(s.data() != p);
		VERIFY(s.data()[0] == p[0]);
		VERIFY(s.data() + 0 == bksge::addressof(s[0]));
	}
	{
		string s;
		VERIFY(s.data()[0] == Helper::null_char());
	}
	{
		string const s;
		VERIFY(s.data()[0] == Helper::null_char());
	}

	return true;
}
TYPED_TEST(BasicStringTest, DataTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(DataTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CStrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		VERIFY(s.c_str() != p);
		VERIFY(s.c_str()[0] == p[0]);
		VERIFY(s.c_str()[1] == p[1]);
		VERIFY(s.c_str()[2] == p[2]);
		VERIFY(s.c_str()[3] == p[3]);
		VERIFY(s.c_str()[4] == p[4]);
		VERIFY(s.c_str() + 0 == bksge::addressof(s[0]));
		VERIFY(s.c_str() + 1 == bksge::addressof(s[1]));
		VERIFY(s.c_str() + 2 == bksge::addressof(s[2]));
		VERIFY(s.c_str() + 3 == bksge::addressof(s[3]));
		VERIFY(s.c_str() + 4 == bksge::addressof(s[4]));
	}
	{
		auto p = Helper::cde();
		string const s = p;
		VERIFY(s.c_str() != p);
		VERIFY(s.c_str()[0] == p[0]);
		VERIFY(s.c_str()[1] == p[1]);
		VERIFY(s.c_str()[2] == p[2]);
		VERIFY(s.c_str()[3] == p[3]);
		VERIFY(s.c_str() + 0 == bksge::addressof(s[0]));
		VERIFY(s.c_str() + 1 == bksge::addressof(s[1]));
		VERIFY(s.c_str() + 2 == bksge::addressof(s[2]));
		VERIFY(s.c_str() + 3 == bksge::addressof(s[3]));
	}
	{
		string s;
		VERIFY(s.c_str()[0] == 0);
	}
	{
		string const s;
		VERIFY(s.c_str()[0] == 0);
	}

	return true;
}
TYPED_TEST(BasicStringTest, CStrTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CStrTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcd();
		string_view sv = s;
		VERIFY(sv == Helper::abcd());
	}
	{
		string s = Helper::long_str();
		string_view sv = s;
		VERIFY(sv == Helper::long_str());
	}
	return true;
}
TYPED_TEST(BasicStringTest, OperatorStringViewTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorStringViewTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool BeginEndTest()
{
	using string = bksge::basic_string<CharT>;
	using iterator = typename string::iterator;
	using const_iterator = typename string::const_iterator;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		auto first = s.begin();
		auto last  = s.end();
		static_assert(bksge::is_same<decltype(first), iterator>::value, "");
		static_assert(bksge::is_same<decltype(last),  iterator>::value, "");

		auto it = first;
		VERIFY(*it == p[0]);
		VERIFY(it == first);
		VERIFY(it != last);
		++it;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it++;
		VERIFY(*it == p[2]);
		*it = p[0];
		VERIFY(it != first);
		VERIFY(it != last);
		it += 2;
		VERIFY(it != first);
		VERIFY(it == last);
		it--;
		VERIFY(*it == p[3]);
		VERIFY(it != first);
		VERIFY(it != last);
		--it;
		VERIFY(*it != p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		VERIFY(s == Helper::abad());
	}
	{
		auto p = Helper::abcd();
		string const s = p;
		auto first = s.begin();
		auto last  = s.end();
		static_assert(bksge::is_same<decltype(first), const_iterator>::value, "");
		static_assert(bksge::is_same<decltype(last),  const_iterator>::value, "");

		auto it = first;
		VERIFY(*it == p[0]);
		VERIFY(it == first);
		VERIFY(it != last);
		++it;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it++;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		it += 2;
		VERIFY(it != first);
		VERIFY(it == last);
		it--;
		VERIFY(*it == p[3]);
		VERIFY(it != first);
		VERIFY(it != last);
		--it;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CBeginCEndTest()
{
	using string = bksge::basic_string<CharT>;
	using const_iterator = typename string::const_iterator;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		auto first = s.cbegin();
		auto last  = s.cend();
		static_assert(bksge::is_same<decltype(first), const_iterator>::value, "");
		static_assert(bksge::is_same<decltype(last),  const_iterator>::value, "");

		auto it = first;
		VERIFY(*it == p[0]);
		VERIFY(it == first);
		VERIFY(it != last);
		++it;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it++;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		it += 2;
		VERIFY(it != first);
		VERIFY(it == last);
		it--;
		VERIFY(*it == p[3]);
		VERIFY(it != first);
		VERIFY(it != last);
		--it;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool RBeginREndTest()
{
	using string = bksge::basic_string<CharT>;
	using reverse_iterator = typename string::reverse_iterator;
	using const_reverse_iterator = typename string::const_reverse_iterator;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		auto first = s.rbegin();
		auto last  = s.rend();
		static_assert(bksge::is_same<decltype(first), reverse_iterator>::value, "");
		static_assert(bksge::is_same<decltype(last),  reverse_iterator>::value, "");

		auto it = first;
		VERIFY(*it == p[3]);
		VERIFY(it == first);
		VERIFY(it != last);
		++it;
		VERIFY(*it == p[2]);
		*it = p[0];
		VERIFY(it != first);
		VERIFY(it != last);
		it++;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it += 2;
		VERIFY(it != first);
		VERIFY(it == last);
		it--;
		VERIFY(*it == p[0]);
		VERIFY(it != first);
		VERIFY(it != last);
		--it;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it != p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		VERIFY(s == Helper::abad());
	}
	{
		auto p = Helper::abcd();
		string const s = p;
		auto first = s.rbegin();
		auto last  = s.rend();
		static_assert(bksge::is_same<decltype(first), const_reverse_iterator>::value, "");
		static_assert(bksge::is_same<decltype(last),  const_reverse_iterator>::value, "");

		auto it = first;
		VERIFY(*it == p[3]);
		VERIFY(it == first);
		VERIFY(it != last);
		++it;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		it++;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it += 2;
		VERIFY(it != first);
		VERIFY(it == last);
		it--;
		VERIFY(*it == p[0]);
		VERIFY(it != first);
		VERIFY(it != last);
		--it;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CRBeginCREndTest()
{
	using string = bksge::basic_string<CharT>;
	using const_reverse_iterator = typename string::const_reverse_iterator;
	using Helper = StringTestHelper<CharT>;

	{
		auto p = Helper::abcd();
		string s = p;
		auto first = s.crbegin();
		auto last  = s.crend();
		static_assert(bksge::is_same<decltype(first), const_reverse_iterator>::value, "");
		static_assert(bksge::is_same<decltype(last),  const_reverse_iterator>::value, "");

		auto it = first;
		VERIFY(*it == p[3]);
		VERIFY(it == first);
		VERIFY(it != last);
		++it;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
		it++;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it += 2;
		VERIFY(it != first);
		VERIFY(it == last);
		it--;
		VERIFY(*it == p[0]);
		VERIFY(it != first);
		VERIFY(it != last);
		--it;
		VERIFY(*it == p[1]);
		VERIFY(it != first);
		VERIFY(it != last);
		it -= 1;
		VERIFY(*it == p[2]);
		VERIFY(it != first);
		VERIFY(it != last);
	}
	return true;
}
TYPED_TEST(BasicStringTest, IteratorTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(BeginEndTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CBeginCEndTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(RBeginREndTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CRBeginCREndTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s;
		static_assert(bksge::is_same<decltype(s.empty()), bool>::value, "");
		VERIFY(s.empty());

		s = Helper::abc();
		VERIFY(!s.empty());

		s = string();
		VERIFY(s.empty());

		s = Helper::cd();
		VERIFY(!s.empty());

		s = Helper::null_str();
		VERIFY(s.empty());
	}
	return true;
}
TYPED_TEST(BasicStringTest, EmptyTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EmptyTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using string = bksge::basic_string<CharT>;
	using size_type = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	{
		string const s;
		static_assert(bksge::is_same<decltype(s.size()), size_type>::value, "");
		VERIFY(s.size() == 0);
	}
	{
		string const s = Helper::a();
		VERIFY(s.size() == 1);
	}
	{
		string const s = Helper::cb();
		VERIFY(s.size() == 2);
	}
	{
		string const s = Helper::bcd();
		VERIFY(s.size() == 3);
	}
	{
		string const s = Helper::abcd();
		VERIFY(s.size() == 4);
	}
	return true;
}
TYPED_TEST(BasicStringTest, SizeTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(SizeTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool LengthTest()
{
	using string = bksge::basic_string<CharT>;
	using size_type = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	{
		string const s;
		static_assert(bksge::is_same<decltype(s.length()), size_type>::value, "");
		VERIFY(s.length() == 0);
	}
	{
		string const s = Helper::a();
		VERIFY(s.length() == 1);
	}
	{
		string const s = Helper::cb();
		VERIFY(s.length() == 2);
	}
	{
		string const s = Helper::bcd();
		VERIFY(s.length() == 3);
	}
	{
		string const s = Helper::abcd();
		VERIFY(s.length() == 4);
	}
	return true;
}
TYPED_TEST(BasicStringTest, LengthTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(LengthTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using string = bksge::basic_string<CharT>;
	using size_type = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	{
		string const s1;
		string const s2;
		static_assert(bksge::is_same<decltype(s1.max_size()), size_type>::value, "");
		VERIFY(s1.max_size() == s2.max_size());
		VERIFY(s1.max_size() >= s1.size());
	}
	{
		string const s1 = Helper::abcde();
		string const s2;
		VERIFY(s1.max_size() == s2.max_size());
		VERIFY(s1.max_size() >= s1.size());
	}
	return true;
}
TYPED_TEST(BasicStringTest, MaxSizeTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MaxSizeTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CapacityTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string const s1;
		string const s2;
		VERIFY(s1.capacity() == s2.capacity());
		VERIFY(s1.capacity() >= s1.size());
	}
	{
		string const s1 = Helper::abcde();
		string const s2;
		VERIFY(s1.capacity() >= s2.capacity());
		VERIFY(s1.capacity() >= s1.size());
	}
	{
		string const s1 = Helper::long_str();
		string const s2 = Helper::abcde();
		VERIFY(s1.capacity() >= s2.capacity());
		VERIFY(s1.capacity() >= s1.size());
	}
	return true;
}
TYPED_TEST(BasicStringTest, CapacityTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CapacityTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReserveTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abc();
		auto cap = s.capacity();
		static_assert(bksge::is_same<decltype(cap), typename string::size_type>::value, "");
		VERIFY(cap > 0);

		// If new_cap is greater than the current capacity(), new storage is allocated,
		// and capacity() is made equal or greater than new_cap.
		s.reserve(cap + 1);
		auto cap2 = s.capacity();
		VERIFY(cap2 > cap);

		// If new_cap is less than or equal to the current capacity(), there is no effect.
		s.reserve(cap2);
		VERIFY(s.capacity() == cap2);
		s.reserve(cap2 - 1);
		VERIFY(s.capacity() == cap2);

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4996);
BKSGE_WARNING_DISABLE_CLANG("-Wdeprecated-declarations");
BKSGE_WARNING_DISABLE_GCC("-Wdeprecated-declarations");

		// A call to reserve with no argument is a non-binding shrink-to-fit request.
		// After this call, capacity() has an unspecified value greater than or equal to size().
		s.reserve();
		VERIFY(s.capacity() >= s.size());

		s = Helper::long_str();
		s.reserve(s.capacity() + 1);
		s.reserve();
		VERIFY(s.capacity() >= s.size());

BKSGE_WARNING_POP();
	}
	return true;
}
TYPED_TEST(BasicStringTest, ReserveTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReserveTest<CharT>());

	// Exceptions Test

	// Throws length_error if new_cap is greater than max_size()
	{
		string s;
		EXPECT_THROW(s.reserve(s.max_size() + 1), bksge::length_error);
	}

	// May throw any exceptions thrown by allocator_traits<Allocator>::allocate(), such as bad_alloc.
	{
		string s;
		EXPECT_THROW(s.reserve(s.max_size()), std::bad_alloc);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ShrinkToFitTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcde();
		auto cap = s.capacity();

		s.shrink_to_fit();
		auto cap2 = s.capacity();
		VERIFY(cap2 <= cap);
	}
	{
		string s = Helper::long_str();
		auto cap = s.capacity();

		s.shrink_to_fit();
		auto cap2 = s.capacity();
		VERIFY(cap2 <= cap);
	}
	return true;
}
TYPED_TEST(BasicStringTest, ShrinkToFitTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShrinkToFitTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ClearTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s = Helper::abcde();
		auto cap = s.capacity();
		auto p   = s.data();

		s.clear();
		VERIFY(s.empty());
		VERIFY(s.size() == 0);

		// The C++ standard does not explicitly require that capacity is unchanged by clear(),
		// but existing implementations do not change capacity.
		VERIFY(s.capacity() == cap);
		// This means that they do not release the allocated memory.
		VERIFY(s.data() == p);
	}
	{
		string s = Helper::long_str();
		auto cap = s.capacity();
		auto p   = s.data();

		s.clear();
		VERIFY(s.empty());
		VERIFY(s.size() == 0);

		// The C++ standard does not explicitly require that capacity is unchanged by clear(),
		// but existing implementations do not change capacity.
		VERIFY(s.capacity() == cap);
		// This means that they do not release the allocated memory.
		VERIFY(s.data() == p);
	}
	return true;
}
TYPED_TEST(BasicStringTest, ClearTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ClearTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertIndexCountCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) basic_string& insert(size_type index, size_type count, CharT)
	{
		string s;
		auto r1 = s.insert(0, 3, Helper::a()[0]);	// 'a' * 3
		VERIFY(s == Helper::aaa());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, 2, Helper::c()[0]);	// 'c' * 2
		VERIFY(s == Helper::accaa());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertIndexCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) basic_string& insert(size_type index, const CharT*)
	{
		string s;
		auto r1 = s.insert(0, Helper::abc());		// "abc"
		VERIFY(s == Helper::abc());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, Helper::cd());		// "cd"
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	{
		string s;
		auto r1 = s.insert(0, Helper::long_str());
		VERIFY(s == Helper::long_str());
		VERIFY(r1 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertIndexCharPtrCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) basic_string& insert(size_type index, const CharT*, size_type count)
	{
		string s;
		auto r1 = s.insert(0, Helper::abcde(), 3);		// "abc"
		VERIFY(s == Helper::abc());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, Helper::cde(), 2);		// "cd"
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertIndexStringTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) basic_string& insert(size_type index, const basic_string&)
	{
		string s;
		auto r1 = s.insert(0, string(Helper::abc()));	// "abc"
		VERIFY(s == Helper::abc());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, string(Helper::cd()));	// "cd"
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	{
		string s;
		auto r1 = s.insert(0, string(Helper::long_str()));
		VERIFY(s == Helper::long_str());
		VERIFY(r1 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertIndexStringPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) basic_string& insert(size_type index, const basic_string&,
	//                          size_type index_str)
	{
		string s;
		string const s2 = Helper::cde();
		auto r1 = s.insert(0, s2, 0);		// "cde"
		VERIFY(s == Helper::cde());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, s2, 1);		// "de"
		VERIFY(s == Helper::cdede());
		VERIFY(r2 == s);
	}
	// (5) basic_string& insert(size_type index, const basic_string&,
	//                          size_type index_str, size_type count)
	{
		string s;
		string const s2 = Helper::abcde();
		auto r1 = s.insert(0, s2, 0, 3);		// "abc"
		VERIFY(s == Helper::abc());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, s2, 2, 2);		// "cd"
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertPosCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (6) iterator insert(const_iterator pos, CharT);
	{
		string s;
		auto r1 = s.insert(s.cbegin(), Helper::abcde()[2]);	// 'c'
		VERIFY(s == Helper::c());
		VERIFY(r1 == s.cbegin());
		auto r2 = s.insert(s.cbegin(), Helper::abcde()[1]);	// 'b'
		VERIFY(s == Helper::bc());
		VERIFY(r2 == s.cbegin());
		auto r3 = s.insert(s.cend(), Helper::abcde()[3]);	// 'd'
		VERIFY(s == Helper::bcd());
		VERIFY(r3 == s.cbegin() + 2);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertPosCountCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (7) iterator insert(const_iterator pos, size_type count, CharT)
	{
		string s;
		auto r1 = s.insert(s.cbegin(), 3, Helper::a()[0]);		// 'a' * 3
		VERIFY(s == Helper::aaa());
		VERIFY(r1 == s.cbegin());
		auto r2 = s.insert(s.cbegin() + 1, 2, Helper::c()[0]);	// 'c' * 2
		VERIFY(s == Helper::accaa());
		VERIFY(r2 == s.cbegin() + 1);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertPosIteratorTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (8) iterator insert(const_iterator pos, InputIt first, InputIt last)
	{
		string s;
		auto p = Helper::abcde();
		auto r1 = s.insert(s.cbegin(), p, p + 3);			// "abc"
		VERIFY(s == Helper::abc());
		VERIFY(r1 == s.cbegin());
		auto r2 = s.insert(s.cbegin() + 1, p + 2, p + 4);	// "cd"
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s.cbegin() + 1);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertPosInitializerListTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (9) iterator insert(const_iterator pos, initializer_list<CharT>)
	{
		string s;
		auto p = Helper::abcde();
		auto r1 = s.insert(s.cbegin(), { p[0], p[2], p[4] });	// { 'a', 'c', 'e' }
		VERIFY(s == Helper::ace());
		VERIFY(r1 == s.cbegin());
		auto r2 = s.insert(s.cbegin() + 2, { p[3], p[2], p[0], p[1] });	// { 'd', 'c', 'a', 'b' }
		VERIFY(s == Helper::acdcabe());
		VERIFY(r2 == s.cbegin() + 2);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertPosStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (10) basic_string& insert(size_type index, const T& sv)
	{
		string s;

		string_view sv1 = Helper::abc();
		auto r1 = s.insert(0, sv1);
		VERIFY(s == Helper::abc());
		VERIFY(r1 == s);

		string_view sv2 = Helper::cd();
		auto r2 = s.insert(1, sv2);
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	{
		string s;

		string_view sv1 = Helper::long_str();
		auto r1 = s.insert(0, sv1);
		VERIFY(s == Helper::long_str());
		VERIFY(r1 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool InsertIndexStringViewPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (11) basic_string& insert(size_type index, const T& sv,
    //                           size_type index_str)
	{
		string s;
		string_view const s2 = Helper::cde();
		auto r1 = s.insert(0, s2, 0);		// "cde"
		VERIFY(s == Helper::cde());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, s2, 1);		// "de"
		VERIFY(s == Helper::cdede());
		VERIFY(r2 == s);
	}
	// (11) basic_string& insert(size_type index, const T& sv,
    //                           size_type index_str, size_type count)
	{
		string s;
		string_view const s2 = Helper::abcde();
		auto r1 = s.insert(0, s2, 0, 3);		// "abc"
		VERIFY(s == Helper::abc());
		VERIFY(r1 == s);
		auto r2 = s.insert(1, s2, 2, 2);		// "cd"
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	return true;
}
TYPED_TEST(BasicStringTest, InsertTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertIndexCountCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertIndexCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertIndexCharPtrCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertIndexStringTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertIndexStringPosCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertPosCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertPosCountCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertPosIteratorTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertPosInitializerListTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertPosStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(InsertIndexStringViewPosCountTest<CharT>());

	// Exceptions Test
	// In any case, if an exception is thrown for any reason, this function has no effect.

	// 1) Throws out_of_range if index > size().
	{
		string s = Helper::abc();
		EXPECT_THROW(s.insert(4, 3, Helper::a()[0]), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abc());
	}
	// 2) Throws out_of_range if index > size().
	{
		string s = Helper::abcd();
		EXPECT_THROW(s.insert(5, Helper::cd()), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abcd());
	}
	// 3) Throws out_of_range if index > size().
	{
		string s = Helper::cd();
		EXPECT_THROW(s.insert(3, Helper::abcd(), 2), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::cd());
	}
	// 4) Throws out_of_range if index > size().
	{
		string s = Helper::cd();
		string s2 = Helper::abcd();
		EXPECT_THROW(s.insert(3, s2), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::cd());
	}
	// 5) Throws out_of_range if index > size() or if index_str > str.size().
	{
		string s = Helper::cd();
		string s2 = Helper::abc();
		EXPECT_THROW(s.insert(3, s2, 3), bksge::out_of_range);
		EXPECT_THROW(s.insert(2, s2, 4), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::cd());
	}
	//10) Throws out_of_range if index > size().
	{
		string s = Helper::cd();
		string_view sv = Helper::abcd();
		EXPECT_THROW(s.insert(3, sv), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::cd());
	}
	//11) Throws out_of_range if index > size() or if index_str > sv.size().
	{
		string s = Helper::cd();
		string_view sv = Helper::abc();
		EXPECT_THROW(s.insert(3, sv, 3), bksge::out_of_range);
		EXPECT_THROW(s.insert(2, sv, 4), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::cd());
	}

	// In all cases, throws length_error if size() + ins_count > max_size().
	{
		string s = Helper::abc();
		EXPECT_THROW(s.insert(0, s.max_size(), Helper::a()[0]), bksge::length_error);
		EXPECT_TRUE(s == Helper::abc());
	}
	{
		string s = Helper::abc();
		EXPECT_THROW(s.insert(s.begin(), s.max_size(), Helper::a()[0]), bksge::length_error);
		EXPECT_TRUE(s == Helper::abc());
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EraseIndexCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// erase()
	{
		string s = Helper::acdcabe();
		auto r = s.erase();
		VERIFY(s.empty());
		VERIFY(r == s);
	}
	{
		string s = Helper::long_str();
		auto r = s.erase();
		VERIFY(s.empty());
		VERIFY(r == s);
	}
	// erase(size_type index)
	{
		string s = Helper::abcde();
		auto r = s.erase(3);
		VERIFY(s == Helper::abc());
		VERIFY(r == s);
	}
	// erase(size_type index, size_type count)
	{
		string s = Helper::acdcabe();
		auto r = s.erase(2, 4);
		VERIFY(s == Helper::ace());
		VERIFY(r == s);
	}
	{
		string s = Helper::abcde();
		auto r = s.erase(2, 10);
		VERIFY(s == Helper::ab());
		VERIFY(r == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ErasePositionTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::abcde();
		auto r = s.erase(s.begin());
		VERIFY(s == Helper::bcde());
		VERIFY(r == s.begin());
	}
	{
		string s = Helper::abcde();
		auto r = s.erase(s.begin() + 4);
		VERIFY(s == Helper::abcd());
		VERIFY(r == s.begin() + 4);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EraseFirstLastTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::acdcabe();
		auto r = s.erase(s.begin() + 2, s.begin() + 6);
		VERIFY(s == Helper::ace());
		VERIFY(r == s.begin() + 2);
	}
	{
		string s = Helper::acdcabe();
		auto r = s.erase(s.begin(), s.end());
		VERIFY(s.empty());
		VERIFY(r == s.begin());
	}
	{
		string s = Helper::acdcabe();
		auto r = s.erase(s.end(), s.end());
		VERIFY(s == Helper::acdcabe());
		VERIFY(r == s.end());
	}
	{
		string s = Helper::abcd();
		auto r = s.erase(s.begin(), s.begin());
		VERIFY(s == Helper::abcd());
		VERIFY(r == s.begin());
	}
	{
		string s = Helper::long_str();
		auto r = s.erase(s.begin(), s.end());
		VERIFY(s.empty());
		VERIFY(r == s.begin());
	}
	return true;
}
TYPED_TEST(BasicStringTest, EraseTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIndexCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ErasePositionTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseFirstLastTest<CharT>());

	// Exceptions Test

	// 1) out_of_range if index > size().
	{
		string s = Helper::abc();
		EXPECT_NO_THROW(s.erase(3));
		EXPECT_THROW(s.erase(4), bksge::out_of_range);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool PushBackTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		auto p = Helper::abcde();
		string s = Helper::a();
		VERIFY(s == Helper::a());
		s.push_back(p[1]);	// 'b'
		VERIFY(s == Helper::ab());
		s.push_back(p[2]);	// 'c'
		VERIFY(s == Helper::abc());
	}
	{
		string s;
		auto c = Helper::abcde()[0];
		for (int i = 0; i < 50; ++i)
		{
			s.push_back(c);
		}
		VERIFY(s.length() == 50);
	}
	return true;
}
TYPED_TEST(BasicStringTest, PushBackTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(PushBackTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool PopBackTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::abc();
		VERIFY(s == Helper::abc());
		s.pop_back();
		VERIFY(s == Helper::ab());
		s.pop_back();
		VERIFY(s == Helper::a());
	}
	return true;
}
TYPED_TEST(BasicStringTest, PopBackTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(PopBackTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendCountCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) basic_string& append(size_type count, CharT)
	{
		auto p = Helper::abcde();
		string s = Helper::a();
		auto r1 = s.append(2, p[1]);	// 'b'
		VERIFY(s == Helper::abb());
		VERIFY(r1 == s);
		auto r2 = s.append(3, p[2]);	// 'c'
		VERIFY(s == Helper::abbccc());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) basic_string& append(basic_string const&)
	{
		string s;
		string const t1 = Helper::ab();
		auto r1 = s.append(t1);
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		string const t2 = Helper::cde();
		auto r2 = s.append(t2);
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) basic_string& append(basic_string const&, size_type pos)
	{
		string const t = Helper::abcde();
		string s;
		auto r1 = s.append(t, 2);
		VERIFY(s == Helper::cde());
		VERIFY(r1 == s);
		auto r2 = s.append(t, 3);
		VERIFY(s == Helper::cdede());
		VERIFY(r2 == s);
	}
	// (3) basic_string& append(basic_string const&, size_type pos, size_type count)
	{
		string const t = Helper::abcde();
		string s;
		auto r1 = s.append(t, 0, 2);
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		auto r2 = s.append(t, 2, 10);
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharPtrCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) basic_string& append(CharT const*, size_type count)
	{
		string s;
		auto r1 = s.append(Helper::abcde(), 2);
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		auto r2 = s.append(Helper::cde(), 3);
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) basic_string& append(CharT const*)
	{
		string s;
		auto r1 = s.append(Helper::ab());
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		auto r2 = s.append(Helper::cde());
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendFirstLastTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (6) basic_string& append(InputIt first, InputIt last)
	{
		auto p = Helper::abcde();
		string s;
		auto r1 = s.append(p, p + 2);
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		auto r2 = s.append(p + 2, p + 5);
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendInitializerListTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (7) basic_string& append(initializer_list<CharT>)
	{
		auto p = Helper::abcde();
		string s;
		auto r1 = s.append({ p[0], p[2] });	// { 'a', 'c' }
		VERIFY(s == Helper::ac());
		VERIFY(r1 == s);
		auto r2 = s.append({ p[3], p[1], p[2] });	// { 'd', 'b', 'c' }
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (8) basic_string& append(T const& sv);
	{
		string s;
		string_view const t1 = Helper::ab();
		auto r1 = s.append(t1);
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		string_view const t2 = Helper::cde();
		auto r2 = s.append(t2);
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool AppendStringViewPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (9) basic_string& append(T const& sv, size_type pos);
	{
		string_view const t = Helper::abcde();
		string s;
		auto r1 = s.append(t, 2);
		VERIFY(s == Helper::cde());
		VERIFY(r1 == s);
		auto r2 = s.append(t, 3);
		VERIFY(s == Helper::cdede());
		VERIFY(r2 == s);
	}
	// (9) basic_string& append(T const& sv, size_type pos, size_type count);
	{
		string_view const t = Helper::abcde();
		string s;
		auto r1 = s.append(t, 0, 2);
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		auto r2 = s.append(t, 2, 10);
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}
TYPED_TEST(BasicStringTest, AppendTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendCountCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendStringTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendStringPosCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendCharPtrCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendFirstLastTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendInitializerListTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AppendStringViewPosCountTest<CharT>());

	// Exceptions Test
	// If an exception is thrown for any reason, this function has no effect.

	// If the operation would result in size() > max_size(), throws length_error.
	{
		auto p = Helper::abcde();
		string s = Helper::abc();
		EXPECT_THROW(s.append(s.max_size(), p[0]), bksge::length_error);
		EXPECT_TRUE(s == Helper::abc());
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorAppendStringTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) basic_string& operator+=(basic_string const&)
	{
		string s;
		string const t1 = Helper::ab();
		auto r1 = s += t1;
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		string const t2 = Helper::cde();
		auto r2 = s += t2;
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorAppendCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) basic_string& operator+=(CharT)
	{
		auto p = Helper::abcde();
		string s = Helper::a();
		auto r1 = s += p[1];	// 'b'
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		auto r2 = s += p[2];	// 'c'
		VERIFY(s == Helper::abc());
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorAppendCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) basic_string& operator+=(CharT const*)
	{
		string s;
		auto r1 = s += Helper::ab();
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		auto r2 = s += Helper::cde();
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorAppendInitializerListTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) basic_string& operator+=(initializer_list<CharT>)
	{
		auto p = Helper::abcde();
		string s;
		auto r1 = s += { p[0], p[2] };	// { 'a', 'c' }
		VERIFY(s == Helper::ac());
		VERIFY(r1 == s);
		auto r2 = s += { p[3], p[1], p[2] };	// { 'd', 'b', 'c' }
		VERIFY(s == Helper::acdbc());
		VERIFY(r2 == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorAppendStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) basic_string& operator+=(T const&)
	{
		string s;
		string_view const t1 = Helper::ab();
		auto r1 = s += t1;
		VERIFY(s == Helper::ab());
		VERIFY(r1 == s);
		string_view const t2 = Helper::cde();
		auto r2 = s += t2;
		VERIFY(s == Helper::abcde());
		VERIFY(r2 == s);
	}
	return true;
}

TYPED_TEST(BasicStringTest, OperatorAppendTest)
{
	using CharT = TypeParam;
	//using string = bksge::basic_string<CharT>;
	//using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorAppendStringTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorAppendCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorAppendCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorAppendInitializerListTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorAppendStringViewTest<CharT>());

	// Exceptions Test
	// If an exception is thrown for any reason, this function has no effect.

	// If the operation would result in size() > max_size(), throws length_error.
	{
		// TODO
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CompareStringTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) int compare(basic_string const&)
	{
		string const s1(Helper::abc());
		string const s2(Helper::abc());
		string const s3(Helper::abcd());
		string const s4(Helper::abb());
		string const s5(Helper::abbccc());
		string const s6(Helper::cd());

		VERIFY(s1.compare(s1) == 0);
		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) <  0);
		VERIFY(s1.compare(s4) >  0);
		VERIFY(s1.compare(s5) >  0);
		VERIFY(s1.compare(s6) <  0);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) int compare(size_type pos, size_type count, basic_string const&)
	{
		string const s1(Helper::abcd());
		string const s2(Helper::abc());

		VERIFY(s1.compare(0, 3, s2) == 0);	// "abc".compare("abc")
		VERIFY(s1.compare(1, 3, s2) >  0);	// "bcd".compare("abc")
		VERIFY(s1.compare(0,10, s2) >  0);	// "abcd".compare("abc")
		VERIFY(s1.compare(0, 2, s2) <  0);	// "ab".compare("abc")
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) int compare(size_type pos1, size_type count1,
	//                 basic_string const&,
	//                 size_type pos2)
	{
		string const s1(Helper::abcd());
		string const s2(Helper::bcd());

		VERIFY(s1.compare(1, 3, s2, 0) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s2, 0) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(2, 2, s2, 1) == 0);	// "cd".compare("cd")
		VERIFY(s1.compare(3, 1, s2, 1) >  0);	// "d".compare("cd")
	}
	// (3) int compare(size_type pos1, size_type count1,
	//                 basic_string const&,
	//                 size_type pos2, size_type count2)
	{
		string const s1(Helper::abcd());
		string const s2(Helper::bcde());

		VERIFY(s1.compare(1, 3, s2, 0, 3) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s2, 0, 3) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(1, 2, s2, 0, 3) <  0);	// "bc".compare("bcd")
		VERIFY(s1.compare(1, 3, s2, 0, 2) >  0);	// "bcd".compare("bc")
		VERIFY(s1.compare(1, 3, s2, 0, 4) <  0);	// "bcd".compare("bcde")
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CompareCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) int compare(CharT const* s)
	{
		string const s(Helper::abcd());

		VERIFY(s.compare(Helper::abcd())  == 0);	// "abcd".compare("abcd")
		VERIFY(s.compare(Helper::abc())   >  0);	// "abcd".compare("abc")
		VERIFY(s.compare(Helper::abcde()) <  0);	// "abcd".compare("abcde")
		VERIFY(s.compare(Helper::abb())   >  0);	// "abcd".compare("abb")
		VERIFY(s.compare(Helper::bc())    <  0);	// "abcd".compare("bc")
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) int compare(size_type pos, size_type count, CharT const*)
	{
		string const s(Helper::abcde());

		VERIFY(s.compare(0, 3, Helper::abc()) == 0);	// "abc".compare("abc")
		VERIFY(s.compare(1, 3, Helper::abc()) >  0);	// "bcd".compare("abc")
		VERIFY(s.compare(0,10, Helper::abc()) >  0);	// "abcde".compare("abc")
		VERIFY(s.compare(0, 2, Helper::abc()) <  0);	// "ab".compare("abc")
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountCharPtrCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (6) int compare(size_type pos1, size_type count1, CharT const*, size_type count2)
	{
		string const s(Helper::abcde());

		VERIFY(s.compare(0, 3, Helper::abcd(), 2) >  0);	// "abc".compare("ab")
		VERIFY(s.compare(0, 3, Helper::abcd(), 3) == 0);	// "abc".compare("abc")
		VERIFY(s.compare(0, 3, Helper::abcd(), 4) <  0);	// "abc".compare("abcd")
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CompareStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (7) int compare(T const& sv)
	{
		string const s1(Helper::abc());
		string_view const s2(Helper::abc());
		string_view const s3(Helper::abcd());
		string_view const s4(Helper::abb());
		string_view const s5(Helper::abbccc());
		string_view const s6(Helper::cd());

		VERIFY(s1.compare(s2) == 0);
		VERIFY(s1.compare(s3) <  0);
		VERIFY(s1.compare(s4) >  0);
		VERIFY(s1.compare(s5) >  0);
		VERIFY(s1.compare(s6) <  0);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (8) int compare(size_type pos, size_type count, T const& sv)
	{
		string const s1(Helper::abcd());
		string_view const s2(Helper::abc());

		VERIFY(s1.compare(0, 3, s2) == 0);	// "abc".compare("abc")
		VERIFY(s1.compare(1, 3, s2) >  0);	// "bcd".compare("abc")
		VERIFY(s1.compare(0,10, s2) >  0);	// "abcd".compare("abc")
		VERIFY(s1.compare(0, 2, s2) <  0);	// "ab".compare("abc")
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ComparePosCountStringViewPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (9) int compare(size_type pos1, size_type count1,
	//                 const T& sv,
	//                 size_type pos2)
	{
		string const s1(Helper::abcd());
		string_view const s2(Helper::bcd());

		VERIFY(s1.compare(1, 3, s2, 0) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s2, 0) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(2, 2, s2, 1) == 0);	// "cd".compare("cd")
		VERIFY(s1.compare(3, 1, s2, 1) >  0);	// "d".compare("cd")
	}
	// (9) int compare(size_type pos1, size_type count1,
	//                 const T& sv,
	//                 size_type pos2, size_type count2)
	{
		string const s1(Helper::abcd());
		string_view const s2(Helper::bcde());

		VERIFY(s1.compare(1, 3, s2, 0, 3) == 0);	// "bcd".compare("bcd")
		VERIFY(s1.compare(0, 3, s2, 0, 3) <  0);	// "abc".compare("bcd")
		VERIFY(s1.compare(1, 2, s2, 0, 3) <  0);	// "bc".compare("bcd")
		VERIFY(s1.compare(1, 3, s2, 0, 2) >  0);	// "bcd".compare("bc")
		VERIFY(s1.compare(1, 3, s2, 0, 4) <  0);	// "bcd".compare("bcde")
	}
	return true;
}

TYPED_TEST(BasicStringTest, CompareTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
//	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareStringTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ComparePosCountStringTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ComparePosCountStringPosCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ComparePosCountCharPtrTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ComparePosCountCharPtrCountTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ComparePosCountStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ComparePosCountStringViewPosCountTest<CharT>());

	// Exceptions Test

	// (2) Throws out_of_range if pos is out of range.
	{
		string const s1(Helper::abcd());
		string const s2(Helper::abc());
		EXPECT_THROW((void)s1.compare(5, 3, s2), bksge::out_of_range);
	}
	// (3) Throws out_of_range if pos is out of range.
	{
		string const s1(Helper::abcd());
		string const s2(Helper::abc());
		EXPECT_THROW((void)s1.compare(5, 3, s2, 0), bksge::out_of_range);
		EXPECT_THROW((void)s1.compare(0, 3, s2, 4), bksge::out_of_range);
		EXPECT_THROW((void)s1.compare(5, 3, s2, 4), bksge::out_of_range);
	}
	// (5) Throws out_of_range if pos is out of range.
	{
		string const s1(Helper::abcd());
		EXPECT_THROW((void)s1.compare(5, 3, Helper::abc()), bksge::out_of_range);
	}
	// (6) Throws out_of_range if pos is out of range.
	{
		string const s1(Helper::abcd());
		EXPECT_THROW((void)s1.compare(5, 3, Helper::abc(), 2), bksge::out_of_range);
	}
	// (8) Throws out_of_range if pos is out of range.
	{
		// TODO
		//string const s1(Helper::abcd());
		//string_view const s2(Helper::abc());
		//EXPECT_THROW((void)s1.compare(5, 3, s2), bksge::out_of_range);
	}
	// (9) Throws out_of_range if pos is out of range.
	{
		// TODO
		//string const s1(Helper::abcd());
		//string_view const s2(Helper::abc());
		//EXPECT_THROW((void)s1.compare(5, 3, s2, 0), bksge::out_of_range);
		//EXPECT_THROW((void)s1.compare(0, 3, s2, 4), bksge::out_of_range);
		//EXPECT_THROW((void)s1.compare(5, 3, s2, 4), bksge::out_of_range);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool StartsWithStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) bool starts_with(basic_string_view<CharT,Traits>)
	{
		string const s = Helper::abcd();
		string_view const sv = Helper::abcde();
		VERIFY(!(s.starts_with(sv.substr(0, 5))));	// "abcde"
		VERIFY( (s.starts_with(sv.substr(0, 4))));	// "abcd"
		VERIFY( (s.starts_with(sv.substr(0, 3))));	// "abc"
		VERIFY( (s.starts_with(sv.substr(0, 2))));	// "ab"
		VERIFY(!(s.starts_with(sv.substr(1, 3))));	// "bcd"
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool StartsWithCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) bool starts_with(CharT)
	{
		string const s = Helper::abcd();
		VERIFY( (s.starts_with(Helper::abcd()[0])));	// 'a'
		VERIFY(!(s.starts_with(Helper::abcd()[1])));	// 'b'
		VERIFY(!(s.starts_with(Helper::abcd()[2])));	// 'c'
	}
	{
		string const s = Helper::bcde();
		VERIFY(!(s.starts_with(Helper::abcd()[0])));	// 'a'
		VERIFY( (s.starts_with(Helper::abcd()[1])));	// 'b'
		VERIFY(!(s.starts_with(Helper::abcd()[2])));	// 'c'
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool StartsWithCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) bool starts_with(CharT const*)
	{
		string const s = Helper::abcd();
		VERIFY(!(s.starts_with(Helper::abcde())));
		VERIFY( (s.starts_with(Helper::abcd())));
		VERIFY( (s.starts_with(Helper::abc())));
		VERIFY( (s.starts_with(Helper::ab())));
		VERIFY(!(s.starts_with(Helper::bcd())));
	}
	return true;
}

TYPED_TEST(BasicStringTest, StartsWithTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(StartsWithStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(StartsWithCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(StartsWithCharPtrTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EndsWithStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) bool ends_with(basic_string_view<CharT,Traits>)
	{
		string const s = Helper::abcd();
		string_view const sv = Helper::abcde();
		VERIFY(!(s.ends_with(sv.substr(0, 5))));	// "abcde"
		VERIFY( (s.ends_with(sv.substr(0, 4))));	// "abcd"
		VERIFY(!(s.ends_with(sv.substr(0, 3))));	// "abc"
		VERIFY(!(s.ends_with(sv.substr(0, 2))));	// "ab"
		VERIFY( (s.ends_with(sv.substr(1, 3))));	// "bcd"
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EndsWithCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) bool ends_with(CharT)
	{
		string const s = Helper::abcd();
		VERIFY(!(s.ends_with(Helper::abcd()[0])));	// 'a'
		VERIFY(!(s.ends_with(Helper::abcd()[1])));	// 'b'
		VERIFY(!(s.ends_with(Helper::abcd()[2])));	// 'c'
		VERIFY( (s.ends_with(Helper::abcd()[3])));	// 'd'
	}
	{
		string const s = Helper::abc();
		VERIFY(!(s.ends_with(Helper::abcd()[0])));	// 'a'
		VERIFY(!(s.ends_with(Helper::abcd()[1])));	// 'b'
		VERIFY( (s.ends_with(Helper::abcd()[2])));	// 'c'
		VERIFY(!(s.ends_with(Helper::abcd()[3])));	// 'd'
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool EndsWithCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) bool ends_with(CharT const*)
	{
		string const s = Helper::abcd();
		VERIFY(!(s.ends_with(Helper::abcde())));
		VERIFY( (s.ends_with(Helper::abcd())));
		VERIFY(!(s.ends_with(Helper::abc())));
		VERIFY(!(s.ends_with(Helper::ab())));
		VERIFY( (s.ends_with(Helper::bcd())));
	}
	return true;
}

TYPED_TEST(BasicStringTest, EndsWithTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EndsWithStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EndsWithCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EndsWithCharPtrTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ContainsStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) bool contains(basic_string_view<CharT,Traits>)
	{
		string const s = Helper::abcd();
		VERIFY(!(s.contains(string_view{Helper::abcde()})));
		VERIFY( (s.contains(string_view{Helper::abcd()})));
		VERIFY( (s.contains(string_view{Helper::abc()})));
		VERIFY( (s.contains(string_view{Helper::ab()})));
		VERIFY( (s.contains(string_view{Helper::bcd()})));
		VERIFY(!(s.contains(string_view{Helper::abb()})));
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ContainsCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) bool contains(CharT)
	{
		string const s = Helper::abc();
		VERIFY( (s.contains(Helper::abcd()[0])));	// 'a'
		VERIFY( (s.contains(Helper::abcd()[1])));	// 'b'
		VERIFY( (s.contains(Helper::abcd()[2])));	// 'c'
		VERIFY(!(s.contains(Helper::abcd()[3])));	// 'd'
	}
	{
		string const s = Helper::bcd();
		VERIFY(!(s.contains(Helper::abcd()[0])));	// 'a'
		VERIFY( (s.contains(Helper::abcd()[1])));	// 'b'
		VERIFY( (s.contains(Helper::abcd()[2])));	// 'c'
		VERIFY( (s.contains(Helper::abcd()[3])));	// 'd'
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ContainsCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) bool contains(CharT const*)
	{
		string const s = Helper::abcd();
		VERIFY(!(s.contains(Helper::abcde())));
		VERIFY( (s.contains(Helper::abcd())));
		VERIFY( (s.contains(Helper::abc())));
		VERIFY( (s.contains(Helper::ab())));
		VERIFY( (s.contains(Helper::bcd())));
		VERIFY(!(s.contains(Helper::abb())));
	}
	return true;
}

TYPED_TEST(BasicStringTest, ContainsTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ContainsStringViewTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ContainsCharTest<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ContainsCharPtrTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) basic_string& replace(size_type pos, size_type count, basic_string const&)
	{
		string s = Helper::abcde();
		string const s2 = Helper::aaa();
		auto r = s.replace(2, 2, s2);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceFirstLastStrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) basic_string& replace(const_iterator first, const_iterator last, basic_string const&)
	{
		string s = Helper::abcde();
		string const s2 = Helper::aaa();
		auto r = s.replace(s.begin() + 2, s.begin() + 4, s2);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStrPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (2) basic_string& replace(size_type pos1, size_type count1,
	//                           basic_string const&,
	//                           size_type pos2)
	{
		string s = Helper::abcde();
		string const s2 = Helper::abbccc();
		auto r = s.replace(1, 2, s2, 2);
		VERIFY(s == Helper::abcccde());
		VERIFY(r == s);
	}
	// (2) basic_string& replace(size_type pos1, size_type count1,
	//                           basic_string const&,
	//                           size_type pos2, size_type count2)
	{
		string s = Helper::abc();
		string const s2 = Helper::abbccc();
		auto r = s.replace(2, 0, s2, 2, 3);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceFirstLastFirstLastTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (3) basic_string& replace(const_iterator first1, const_iterator last1,
	//                           InputIt        first2, InputIt        last2)
	{
		string s = Helper::abc();
		auto const p = Helper::abbccc();
		auto r = s.replace(s.begin() + 2, s.begin() + 2, p + 2, p + 5);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == s);
	}
	{
		string s = Helper::abc();
		auto p = const_cast<CharT*>(Helper::abbccc());
		auto r = s.replace(s.begin() + 2, s.begin() + 2, p + 2, p + 5);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == s);
	}
	{
		string s = Helper::abc();
		string const s2 = Helper::abbccc();
		auto r = s.replace(s.begin() + 2, s.begin() + 2, s2.begin() + 2, s2.begin() + 5);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == s);
	}
	{
		string s = Helper::abc();
		string s2 = Helper::abbccc();
		auto r = s.replace(s.begin() + 2, s.begin() + 2, s2.begin() + 2, s2.begin() + 5);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == s);
	}
	{
		string s = Helper::abc();
		string s2 = Helper::abbccc();
		std::vector<CharT> v(s2.begin(), s2.end());
		auto r = s.replace(s.begin() + 2, s.begin() + 2, v.begin() + 2, v.begin() + 5);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) basic_string& replace(size_type pos, size_type count, CharT const*, size_type count2)
	{
		string s = Helper::abcde();
		auto const p = Helper::abbccc();
		auto r = s.replace(1, 2, p + 2, 4);
		VERIFY(s == Helper::abcccde());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceFirstLastCharPtrCountTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (4) basic_string& replace(const_iterator first, const_iterator last, CharT const*, size_type count2)
	{
		string s = Helper::abcde();
		auto const p = Helper::abbccc();
		auto r = s.replace(s.begin() + 1, s.begin() + 3, p + 2, 4);
		VERIFY(s == Helper::abcccde());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) basic_string& replace(size_type pos, size_type count, CharT const*)
	{
		string s = Helper::abcde();
		auto const p = Helper::aaa();
		auto r = s.replace(2, 2, p);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceFirstLastCharPtrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (5) basic_string& replace(const_iterator first, const_iterator last, CharT const*)
	{
		string s = Helper::abcde();
		auto const p = Helper::aaa();
		auto r = s.replace(s.begin() + 2, s.begin() + 4, p);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountCountCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (6) basic_string& replace(size_type pos, size_type count, size_type count2, CharT)
	{
		string s = Helper::abcde();
		auto const c = Helper::abcde()[0];	// 'a'
		auto r = s.replace(2, 2, 3, c);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceFirstLastCountCharTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (6) basic_string& replace(const_iterator first, const_iterator last, size_type count2, CharT)
	{
		string s = Helper::abcde();
		auto const c = Helper::abcde()[0];	// 'a'
		auto r = s.replace(s.begin() + 2, s.begin() + 4, 3, c);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceFirstLastInitializerListTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (7) basic_string& replace(const_iterator first, const_iterator last, initializer_list<CharT>)
	{
		auto const p = Helper::abcde();
		string s = Helper::abc();
		auto r = s.replace(s.begin() + 1, s.begin() + 2, {p[2], p[3], p[1]});	// { 'c', 'd', 'b' }
		VERIFY(s == Helper::acdbc());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (8) basic_string& replace(size_type pos, size_type count, T const& sv)
	{
		string s = Helper::abcde();
		string_view const s2 = Helper::aaa();
		auto r = s.replace(2, 2, s2);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplaceFirstLastStringViewTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (8) basic_string& replace(const_iterator first, const_iterator last, T const& sv)
	{
		string s = Helper::abcde();
		string_view const s2 = Helper::aaa();
		auto r = s.replace(s.begin() + 2, s.begin() + 4, s2);
		VERIFY(s == Helper::abaaae());
		VERIFY(r == s);
	}
	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ReplacePosCountStringViewPosCountTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (9) basic_string& replace(size_type pos, size_type count,
	//                           T const& sv,
	//                           size_type pos2)
	{
		string s = Helper::abcde();
		string_view const s2 = Helper::abbccc();
		auto r = s.replace(1, 2, s2, 2);
		VERIFY(s == Helper::abcccde());
		VERIFY(r == s);
	}
	// (9) basic_string& replace(size_type pos, size_type count,
	//                           T const& sv,
	//                           size_type pos2, size_type count2)
	{
		string s = Helper::abc();
		string_view const s2 = Helper::abbccc();
		auto r = s.replace(2, 0, s2, 2, 3);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == s);
	}
	return true;
}

TYPED_TEST(BasicStringTest, ReplaceTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplacePosCountStrTest<CharT>());					// (1)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceFirstLastStrTest<CharT>());				// (1)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplacePosCountStrPosCountTest<CharT>());			// (2)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceFirstLastFirstLastTest<CharT>());			// (3)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplacePosCountCharPtrCountTest<CharT>());		// (4)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceFirstLastCharPtrCountTest<CharT>());		// (4)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplacePosCountCharPtrTest<CharT>());				// (5)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceFirstLastCharPtrTest<CharT>());			// (5)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplacePosCountCountCharTest<CharT>());			// (6)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceFirstLastCountCharTest<CharT>());			// (6)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceFirstLastInitializerListTest<CharT>());	// (7)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplacePosCountStringViewTest<CharT>());			// (8)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplaceFirstLastStringViewTest<CharT>());			// (8)
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ReplacePosCountStringViewPosCountTest<CharT>());	// (9)

	// Exceptions Test
	// Throws out_of_range if pos > length() or pos2 > str.length()
	// Throws length_error if the resulting string will exceed maximum possible string length (max_size())
	// In any case, if an exception is thrown for any reason, this function has no effect.

	// (1) Throws out_of_range if pos > length()
	{
		string s = Helper::abcde();
		string const s2 = Helper::aaa();
		EXPECT_THROW(s.replace(6, 2, s2), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abcde());
	}
	// (2) Throws out_of_range if pos > length() or pos2 > str.length()
	{
		string s = Helper::abcd();
		string const s2 = Helper::abbccc();
		EXPECT_THROW(s.replace(5, 2, s2, 2), bksge::out_of_range);
		EXPECT_THROW(s.replace(5, 2, s2, 2, 1), bksge::out_of_range);
		EXPECT_THROW(s.replace(1, 2, s2, 7), bksge::out_of_range);
		EXPECT_THROW(s.replace(1, 2, s2, 7, 1), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abcd());
	}
	// (4) Throws out_of_range if pos > length()
	{
		string s = Helper::abc();
		auto const p = Helper::abbccc();
		EXPECT_THROW(s.replace(4, 2, p + 2, 4), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abc());
	}
	// (5) Throws out_of_range if pos > length()
	{
		string s = Helper::abcde();
		auto const p = Helper::aaa();
		EXPECT_THROW(s.replace(6, 2, p), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abcde());
	}
	// (6) Throws out_of_range if pos > length()
	{
		string s = Helper::abcd();
		auto const c = Helper::abcde()[0];	// 'a'
		EXPECT_THROW(s.replace(5, 2, 3, c), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abcd());
	}
	// (6) Throws length_error if the resulting string will exceed maximum possible string length (max_size())
	{
		string s = Helper::abcd();
		auto const c = Helper::abcde()[0];	// 'a'
		EXPECT_THROW(s.replace(1, 2, s.max_size(), c), bksge::length_error);
		EXPECT_TRUE(s == Helper::abcd());
	}
	// (8) Throws out_of_range if pos > length()
	{
		string s = Helper::abcde();
		string_view const s2 = Helper::aaa();
		EXPECT_THROW(s.replace(6, 2, s2), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abcde());
	}
	// (9) Throws out_of_range if pos > length() or pos2 > str.length()
	{
		string s = Helper::abcd();
		string_view const s2 = Helper::abbccc();
		EXPECT_THROW(s.replace(5, 2, s2, 2), bksge::out_of_range);
		EXPECT_THROW(s.replace(5, 2, s2, 2, 1), bksge::out_of_range);
		EXPECT_THROW(s.replace(1, 2, s2, 7), bksge::out_of_range);
		EXPECT_THROW(s.replace(1, 2, s2, 7, 1), bksge::out_of_range);
		EXPECT_TRUE(s == Helper::abcd());
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool SubStrTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// basic_string substr()
	{
		string const s = Helper::abcde();
		VERIFY(s.substr() == Helper::abcde());
	}
	// basic_string substr(pos)
	{
		string const s = Helper::abcde();
		VERIFY(s.substr(1) == Helper::bcde());
	}
	// basic_string substr(pos, count)
	{
		string const s = Helper::abcde();
		VERIFY(s.substr(1, 2) == Helper::bc());
	}
	return true;
}
TYPED_TEST(BasicStringTest, SubStrTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubStrTest<CharT>());

	// Exceptions
	// out_of_range if pos > size()
	{
		string const s = Helper::abcde();
		EXPECT_THROW((void)s.substr(6), bksge::out_of_range);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool CopyTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// size_type copy(dest, count)
	{
		CharT dest[32] {};
		string const s = Helper::abcde();
		auto r = s.copy(dest, 3);
		VERIFY(dest == string(Helper::abc()));
		VERIFY(r == 3);
	}
	// size_type copy(dest, count, pos)
	{
		CharT dest[32] {};
		string const s = Helper::abcde();
		auto r = s.copy(dest, 10, 1);
		VERIFY(dest == string(Helper::bcde()));
		VERIFY(r == 4);
	}
	return true;
}
TYPED_TEST(BasicStringTest, CopyTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(CopyTest<CharT>());

	// Exceptions
	// out_of_range if pos > size()
	{
		CharT dest[32] {};
		string const s = Helper::abcde();
		EXPECT_THROW(s.copy(dest, 10, 6), bksge::out_of_range);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool ResizeTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// void resize(count)
	{
		string s = Helper::abcde();
		s.resize(4);
		VERIFY(s == Helper::abcd());
		VERIFY(s.length() == 4);
		s.resize(6);
		//VERIFY(s == Helper::abcd());
		VERIFY(s.length() == 6);
	}
	// void resize(count, ch)
	{
		auto const p = Helper::abcde();
		string s = Helper::abcde();
		s.resize(2, p[0]);
		VERIFY(s == Helper::ab());
		VERIFY(s.length() == 2);
		s.resize(3, p[1]);
		VERIFY(s == Helper::abb());
		VERIFY(s.length() == 3);
	}
	return true;
}
TYPED_TEST(BasicStringTest, ResizeTest)
{
	using CharT = TypeParam;
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ResizeTest<CharT>());

	// Exceptions
	// length_error if count > max_size().
	// If an exception is thrown for any reason, this function has no effect
	{
		auto const p = Helper::abcde();
		string s = p;
		EXPECT_THROW(s.resize(s.max_size() + 1), bksge::length_error);
		EXPECT_THROW(s.resize(s.max_size() + 1, p[0]), bksge::length_error);
	}
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string s1 = Helper::abcde();
		string s2 = Helper::bbcd();

		s1.swap(s2);
		VERIFY(s1 == Helper::bbcd());
		VERIFY(s2 == Helper::abcde());

		bksge::swap(s1, s2);
		VERIFY(s1 == Helper::abcde());
		VERIFY(s2 == Helper::bbcd());

		s1.swap(s1);
		VERIFY(s1 == Helper::abcde());
		VERIFY(s2 == Helper::bbcd());
	}
	{
		string s1;
		string s2 = Helper::abcd();

		s1.swap(s2);
		VERIFY(s1 == Helper::abcd());
		VERIFY(s2.empty());

		bksge::swap(s1, s2);
		VERIFY(s1.empty());
		VERIFY(s2 == Helper::abcd());

		s1.swap(s1);
		VERIFY(s1.empty());
		VERIFY(s2 == Helper::abcd());
	}

	return true;
}
TYPED_TEST(BasicStringTest, SwapTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(SwapTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto const npos = string::npos;

	string const s1 = Helper::aababc();		// "aababc"
	string const s2 = Helper::a();			// "a"
	string const s3 = Helper::ab();			// "ab"
	string const s4 = Helper::abc();		// "abc"
	string const s5 = Helper::abcd();		// "abcd"

	// (1) size_type find(str, pos = 0)
	VERIFY(  0u == s1.find(s1));
	VERIFY(  0u == s1.find(s2));
	VERIFY(  1u == s1.find(s3));
	VERIFY(  3u == s1.find(s4));
	VERIFY(npos == s1.find(s5));
	VERIFY(  1u == s1.find(s2, 1));
	VERIFY(  1u == s1.find(s3, 1));
	VERIFY(  3u == s1.find(s4, 1));
	VERIFY(npos == s1.find(s5, 1));
	VERIFY(  3u == s1.find(s2, 2));
	VERIFY(  3u == s1.find(s3, 2));
	VERIFY(  3u == s1.find(s4, 2));
	VERIFY(npos == s1.find(s5, 2));

	// (2) size_type find(s, pos, count)
	VERIFY(  0u == s1.find(Helper::abcd(), 0, 0));
	VERIFY(  0u == s1.find(Helper::abcd(), 0, 1));
	VERIFY(  1u == s1.find(Helper::abcd(), 0, 2));
	VERIFY(  3u == s1.find(Helper::abcd(), 0, 3));
	VERIFY(npos == s1.find(Helper::abcd(), 0, 4));
	VERIFY(  2u == s1.find(Helper::abcd(), 2, 0));
	VERIFY(  3u == s1.find(Helper::abcd(), 2, 1));
	VERIFY(  3u == s1.find(Helper::abcd(), 2, 2));
	VERIFY(  3u == s1.find(Helper::abcd(), 2, 3));
	VERIFY(npos == s1.find(Helper::abcd(), 2, 4));

	// (3) size_type find(s, pos = 0)
	VERIFY(npos == s1.find(Helper::abcd()));
	VERIFY(  1u == s1.find(Helper::ab()));
	VERIFY(  1u == s1.find(Helper::ab(), 1));
	VERIFY(  3u == s1.find(Helper::ab(), 2));
	VERIFY(  3u == s1.find(Helper::ab(), 3));
	VERIFY(npos == s1.find(Helper::ab(), 4));
	VERIFY(npos == s1.find(Helper::ab(), 5));
	VERIFY(npos == s1.find(Helper::ab(), 6));

	// (4) size_type find(ch, pos)
	VERIFY(  0u == s1.find(Helper::abcd()[0]));
	VERIFY(  2u == s1.find(Helper::abcd()[1]));
	VERIFY(  5u == s1.find(Helper::abcd()[2]));
	VERIFY(npos == s1.find(Helper::abcd()[3]));
	VERIFY(  2u == s1.find(Helper::abcd()[1], 2));
	VERIFY(  4u == s1.find(Helper::abcd()[1], 3));
	VERIFY(  4u == s1.find(Helper::abcd()[1], 4));
	VERIFY(npos == s1.find(Helper::abcd()[1], 5));

	string_view const sv1 = Helper::aababc();
	string_view const sv2 = Helper::a();
	string_view const sv3 = Helper::ab();
	string_view const sv4 = Helper::abc();
	string_view const sv5 = Helper::abcd();

	// (5) size_type find(const T& sv, pos = 0)
	VERIFY(  0u == s1.find(sv1));
	VERIFY(  0u == s1.find(sv2));
	VERIFY(  1u == s1.find(sv3));
	VERIFY(  3u == s1.find(sv4));
	VERIFY(npos == s1.find(sv5));
	VERIFY(  1u == s1.find(sv2, 1));
	VERIFY(  1u == s1.find(sv3, 1));
	VERIFY(  3u == s1.find(sv4, 1));
	VERIFY(npos == s1.find(sv5, 1));
	VERIFY(  3u == s1.find(sv2, 2));
	VERIFY(  3u == s1.find(sv3, 2));
	VERIFY(  3u == s1.find(sv4, 2));
	VERIFY(npos == s1.find(sv5, 2));

	return true;
}
TYPED_TEST(BasicStringTest, FindTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool RFindTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto const npos = string::npos;

	string const s1 = Helper::aababc();		// "aababc"
	string const s2 = Helper::a();			// "a"
	string const s3 = Helper::ab();			// "ab"
	string const s4 = Helper::abc();		// "abc"
	string const s5 = Helper::abcd();		// "abcd"

	// (1) size_type rfind(str, pos = 0)
	VERIFY(  0u == s1.rfind(s1));
	VERIFY(  3u == s1.rfind(s2));
	VERIFY(  3u == s1.rfind(s3));
	VERIFY(  3u == s1.rfind(s4));
	VERIFY(npos == s1.rfind(s5));
	VERIFY(  0u == s1.rfind(s1, 0));
	VERIFY(  0u == s1.rfind(s2, 0));
	VERIFY(npos == s1.rfind(s3, 0));
	VERIFY(npos == s1.rfind(s4, 0));
	VERIFY(npos == s1.rfind(s5, 0));
	VERIFY(  0u == s1.rfind(s1, 1));
	VERIFY(  1u == s1.rfind(s2, 1));
	VERIFY(  1u == s1.rfind(s3, 1));
	VERIFY(npos == s1.rfind(s4, 1));
	VERIFY(npos == s1.rfind(s5, 1));
	VERIFY(  0u == s1.rfind(s1, 3));
	VERIFY(  3u == s1.rfind(s2, 3));
	VERIFY(  3u == s1.rfind(s3, 3));
	VERIFY(  3u == s1.rfind(s4, 3));
	VERIFY(npos == s1.rfind(s5, 3));

	// (2) size_type rfind(s, pos, count)
	VERIFY(  0u == s1.rfind(Helper::abcd(), 0, 0));
	VERIFY(  0u == s1.rfind(Helper::abcd(), 0, 1));
	VERIFY(npos == s1.rfind(Helper::abcd(), 0, 2));
	VERIFY(npos == s1.rfind(Helper::abcd(), 0, 3));
	VERIFY(npos == s1.rfind(Helper::abcd(), 0, 4));
	VERIFY(  1u == s1.rfind(Helper::abcd(), 1, 0));
	VERIFY(  1u == s1.rfind(Helper::abcd(), 1, 1));
	VERIFY(  1u == s1.rfind(Helper::abcd(), 1, 2));
	VERIFY(npos == s1.rfind(Helper::abcd(), 1, 3));
	VERIFY(npos == s1.rfind(Helper::abcd(), 1, 4));
	VERIFY(  5u == s1.rfind(Helper::abcd(), 5, 0));
	VERIFY(  3u == s1.rfind(Helper::abcd(), 5, 1));
	VERIFY(  3u == s1.rfind(Helper::abcd(), 5, 2));
	VERIFY(  3u == s1.rfind(Helper::abcd(), 5, 3));
	VERIFY(npos == s1.rfind(Helper::abcd(), 5, 4));

	// (3) size_type rfind(s, pos = 0)
	VERIFY(npos == s1.rfind(Helper::abcd()));
	VERIFY(  3u == s1.rfind(Helper::ab()));
	VERIFY(npos == s1.rfind(Helper::ab(), 0));
	VERIFY(  1u == s1.rfind(Helper::ab(), 1));
	VERIFY(  1u == s1.rfind(Helper::ab(), 2));
	VERIFY(  3u == s1.rfind(Helper::ab(), 3));
	VERIFY(  3u == s1.rfind(Helper::ab(), 4));
	VERIFY(  3u == s1.rfind(Helper::ab(), 5));
	VERIFY(  3u == s1.rfind(Helper::ab(), 6));

	// (4) size_type rfind(ch, pos)
	VERIFY(  3u == s1.rfind(Helper::abcd()[0]));
	VERIFY(  4u == s1.rfind(Helper::abcd()[1]));
	VERIFY(  5u == s1.rfind(Helper::abcd()[2]));
	VERIFY(npos == s1.rfind(Helper::abcd()[3]));
	VERIFY(  0u == s1.rfind(Helper::abcd()[0], 0));
	VERIFY(npos == s1.rfind(Helper::abcd()[1], 0));
	VERIFY(npos == s1.rfind(Helper::abcd()[2], 0));
	VERIFY(npos == s1.rfind(Helper::abcd()[3], 0));
	VERIFY(  1u == s1.rfind(Helper::abcd()[0], 1));
	VERIFY(npos == s1.rfind(Helper::abcd()[1], 1));
	VERIFY(npos == s1.rfind(Helper::abcd()[2], 1));
	VERIFY(npos == s1.rfind(Helper::abcd()[3], 1));
	VERIFY(  1u == s1.rfind(Helper::abcd()[0], 2));
	VERIFY(  2u == s1.rfind(Helper::abcd()[1], 2));
	VERIFY(npos == s1.rfind(Helper::abcd()[2], 2));
	VERIFY(npos == s1.rfind(Helper::abcd()[3], 2));
	VERIFY(  3u == s1.rfind(Helper::abcd()[0], 4));
	VERIFY(  4u == s1.rfind(Helper::abcd()[1], 4));
	VERIFY(npos == s1.rfind(Helper::abcd()[2], 4));
	VERIFY(npos == s1.rfind(Helper::abcd()[3], 4));
	VERIFY(  3u == s1.rfind(Helper::abcd()[0], 5));
	VERIFY(  4u == s1.rfind(Helper::abcd()[1], 5));
	VERIFY(  5u == s1.rfind(Helper::abcd()[2], 5));
	VERIFY(npos == s1.rfind(Helper::abcd()[3], 5));

	string_view const sv1 = Helper::aababc();
	string_view const sv2 = Helper::a();
	string_view const sv3 = Helper::ab();
	string_view const sv4 = Helper::abc();
	string_view const sv5 = Helper::abcd();

	// (5) size_type rfind(const T& sv, pos = 0)
	VERIFY(  0u == s1.rfind(sv1));
	VERIFY(  3u == s1.rfind(sv2));
	VERIFY(  3u == s1.rfind(sv3));
	VERIFY(  3u == s1.rfind(sv4));
	VERIFY(npos == s1.rfind(sv5));
	VERIFY(  0u == s1.rfind(sv1, 0));
	VERIFY(  0u == s1.rfind(sv2, 0));
	VERIFY(npos == s1.rfind(sv3, 0));
	VERIFY(npos == s1.rfind(sv4, 0));
	VERIFY(npos == s1.rfind(sv5, 0));
	VERIFY(  0u == s1.rfind(sv1, 1));
	VERIFY(  1u == s1.rfind(sv2, 1));
	VERIFY(  1u == s1.rfind(sv3, 1));
	VERIFY(npos == s1.rfind(sv4, 1));
	VERIFY(npos == s1.rfind(sv5, 1));
	VERIFY(  0u == s1.rfind(sv1, 3));
	VERIFY(  3u == s1.rfind(sv2, 3));
	VERIFY(  3u == s1.rfind(sv3, 3));
	VERIFY(  3u == s1.rfind(sv4, 3));
	VERIFY(npos == s1.rfind(sv5, 3));

	return true;
}
TYPED_TEST(BasicStringTest, RFindTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(RFindTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstOfTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto const npos = string::npos;

	string const s1 = Helper::bbcd();
	string const s2 = Helper::a();
	string const s3 = Helper::ab();
	string const s4 = Helper::abc();

	// (1) size_type find_first_of(str, pos = 0)
	VERIFY(npos == s1.find_first_of(s2));
	VERIFY(  0u == s1.find_first_of(s3));
	VERIFY(  0u == s1.find_first_of(s4));
	VERIFY(npos == s1.find_first_of(s2, 1));
	VERIFY(  1u == s1.find_first_of(s3, 1));
	VERIFY(  1u == s1.find_first_of(s4, 1));
	VERIFY(npos == s1.find_first_of(s2, 2));
	VERIFY(npos == s1.find_first_of(s3, 2));
	VERIFY(  2u == s1.find_first_of(s4, 2));

	// (2) size_type find_first_of(s, pos, count)
	VERIFY(npos == s1.find_first_of(Helper::a(),   0, 1));
	VERIFY(  0u == s1.find_first_of(Helper::ab(),  0, 2));
	VERIFY(  0u == s1.find_first_of(Helper::abc(), 0, 3));
	VERIFY(npos == s1.find_first_of(Helper::a(),   1, 1));
	VERIFY(  1u == s1.find_first_of(Helper::ab(),  1, 2));
	VERIFY(npos == s1.find_first_of(Helper::ab(),  1, 1));
	VERIFY(  1u == s1.find_first_of(Helper::abc(), 1, 3));
	VERIFY(npos == s1.find_first_of(Helper::a(),   2, 1));
	VERIFY(npos == s1.find_first_of(Helper::ab(),  2, 2));
	VERIFY(  2u == s1.find_first_of(Helper::abc(), 2, 3));
	VERIFY(npos == s1.find_first_of(Helper::abc(), 2, 2));

	// (3) size_type find_first_of(s, pos = 0)
	VERIFY(npos == s1.find_first_of(Helper::a(),   0));
	VERIFY(  0u == s1.find_first_of(Helper::ab(),  0));
	VERIFY(  0u == s1.find_first_of(Helper::abc(), 0));
	VERIFY(npos == s1.find_first_of(Helper::a(),   1));
	VERIFY(  1u == s1.find_first_of(Helper::ab(),  1));
	VERIFY(  1u == s1.find_first_of(Helper::abc(), 1));
	VERIFY(npos == s1.find_first_of(Helper::a(),   2));
	VERIFY(npos == s1.find_first_of(Helper::ab(),  2));
	VERIFY(  2u == s1.find_first_of(Helper::abc(), 2));

	// (4) size_type find_first_of(ch, pos)
	VERIFY(npos == s1.find_first_of(Helper::abc()[0], 0));
	VERIFY(  0u == s1.find_first_of(Helper::abc()[1], 0));
	VERIFY(  2u == s1.find_first_of(Helper::abc()[2], 0));
	VERIFY(npos == s1.find_first_of(Helper::abc()[0], 1));
	VERIFY(  1u == s1.find_first_of(Helper::abc()[1], 1));
	VERIFY(  2u == s1.find_first_of(Helper::abc()[2], 1));
	VERIFY(npos == s1.find_first_of(Helper::abc()[0], 2));
	VERIFY(npos == s1.find_first_of(Helper::abc()[1], 2));
	VERIFY(  2u == s1.find_first_of(Helper::abc()[2], 2));

	string_view const sv1 = Helper::bbcd();
	string_view const sv2 = Helper::a();
	string_view const sv3 = Helper::ab();
	string_view const sv4 = Helper::abc();

	// (5) size_type find_first_of(const T& t, pos = 0)
	VERIFY(  0u == s1.find_first_of(sv1));
	VERIFY(npos == s1.find_first_of(sv2));
	VERIFY(  0u == s1.find_first_of(sv3));
	VERIFY(  0u == s1.find_first_of(sv4));
	VERIFY(npos == s1.find_first_of(sv2, 1));
	VERIFY(  1u == s1.find_first_of(sv3, 1));
	VERIFY(  1u == s1.find_first_of(sv4, 1));
	VERIFY(npos == s1.find_first_of(sv2, 2));
	VERIFY(npos == s1.find_first_of(sv3, 2));
	VERIFY(  2u == s1.find_first_of(sv4, 2));

	return true;
}
TYPED_TEST(BasicStringTest, FindFirstOfTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindFirstOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindFirstNotOfTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto const npos = string::npos;

	string const s1 = Helper::aababc();
	string const s2 = Helper::a();
	string const s3 = Helper::ab();
	string const s4 = Helper::abc();
	string const s5 = Helper::null_str();

	// (1) size_type find_first_not_of(str, pos = 0)
	VERIFY(  2u == s1.find_first_not_of(s2));
	VERIFY(  5u == s1.find_first_not_of(s3));
	VERIFY(npos == s1.find_first_not_of(s4));
	VERIFY(  0u == s1.find_first_not_of(s5));
	VERIFY(  2u == s1.find_first_not_of(s2, 1));
	VERIFY(  5u == s1.find_first_not_of(s3, 1));
	VERIFY(npos == s1.find_first_not_of(s4, 1));
	VERIFY(  1u == s1.find_first_not_of(s5, 1));
	VERIFY(  2u == s1.find_first_not_of(s2, 2));
	VERIFY(  5u == s1.find_first_not_of(s3, 2));
	VERIFY(npos == s1.find_first_not_of(s4, 2));
	VERIFY(  2u == s1.find_first_not_of(s5, 2));
	VERIFY(  4u == s1.find_first_not_of(s2, 3));
	VERIFY(  5u == s1.find_first_not_of(s3, 3));
	VERIFY(npos == s1.find_first_not_of(s4, 3));
	VERIFY(  3u == s1.find_first_not_of(s5, 3));
	VERIFY(  4u == s1.find_first_not_of(s2, 4));
	VERIFY(  5u == s1.find_first_not_of(s3, 4));
	VERIFY(npos == s1.find_first_not_of(s4, 4));
	VERIFY(  4u == s1.find_first_not_of(s5, 4));
	VERIFY(  5u == s1.find_first_not_of(s2, 5));
	VERIFY(  5u == s1.find_first_not_of(s3, 5));
	VERIFY(npos == s1.find_first_not_of(s4, 5));
	VERIFY(  5u == s1.find_first_not_of(s5, 5));
	VERIFY(npos == s1.find_first_not_of(s2, 6));
	VERIFY(npos == s1.find_first_not_of(s3, 6));
	VERIFY(npos == s1.find_first_not_of(s4, 6));
	VERIFY(npos == s1.find_first_not_of(s5, 6));

	// (2) size_type find_first_not_of(s, pos, count)
	VERIFY(  0u == s1.find_first_not_of(Helper::abcd(), 0, 0));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd(), 0, 1));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 0, 2));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 0, 3));
	VERIFY(  1u == s1.find_first_not_of(Helper::abcd(), 1, 0));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd(), 1, 1));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 1, 2));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 1, 3));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd(), 2, 0));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd(), 2, 1));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 2, 2));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 2, 3));
	VERIFY(  3u == s1.find_first_not_of(Helper::abcd(), 3, 0));
	VERIFY(  4u == s1.find_first_not_of(Helper::abcd(), 3, 1));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 3, 2));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 3, 3));
	VERIFY(  4u == s1.find_first_not_of(Helper::abcd(), 4, 0));
	VERIFY(  4u == s1.find_first_not_of(Helper::abcd(), 4, 1));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 4, 2));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 4, 3));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 5, 0));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 5, 1));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd(), 5, 2));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 5, 3));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 6, 0));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 6, 1));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 6, 2));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd(), 6, 3));

	// (3) size_type find_first_not_of(s, pos = 0)
	VERIFY(npos == s1.find_first_not_of(Helper::abcd()));
	VERIFY(  5u == s1.find_first_not_of(Helper::ab()));
	VERIFY(  5u == s1.find_first_not_of(Helper::ab(), 0));
	VERIFY(npos == s1.find_first_not_of(Helper::ab(), 6));

	// (4) size_type find_first_not_of(ch, pos)
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd()[0]));
	VERIFY(  0u == s1.find_first_not_of(Helper::abcd()[1]));
	VERIFY(  0u == s1.find_first_not_of(Helper::abcd()[2]));
	VERIFY(  0u == s1.find_first_not_of(Helper::abcd()[3]));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd()[0], 1));
	VERIFY(  1u == s1.find_first_not_of(Helper::abcd()[1], 1));
	VERIFY(  1u == s1.find_first_not_of(Helper::abcd()[2], 1));
	VERIFY(  1u == s1.find_first_not_of(Helper::abcd()[3], 1));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd()[0], 2));
	VERIFY(  3u == s1.find_first_not_of(Helper::abcd()[1], 2));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd()[2], 2));
	VERIFY(  2u == s1.find_first_not_of(Helper::abcd()[3], 2));
	VERIFY(  4u == s1.find_first_not_of(Helper::abcd()[0], 3));
	VERIFY(  3u == s1.find_first_not_of(Helper::abcd()[1], 3));
	VERIFY(  3u == s1.find_first_not_of(Helper::abcd()[2], 3));
	VERIFY(  3u == s1.find_first_not_of(Helper::abcd()[3], 3));
	VERIFY(  4u == s1.find_first_not_of(Helper::abcd()[0], 4));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd()[1], 4));
	VERIFY(  4u == s1.find_first_not_of(Helper::abcd()[2], 4));
	VERIFY(  4u == s1.find_first_not_of(Helper::abcd()[3], 4));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd()[0], 5));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd()[1], 5));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd()[2], 5));
	VERIFY(  5u == s1.find_first_not_of(Helper::abcd()[3], 5));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd()[0], 6));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd()[1], 6));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd()[2], 6));
	VERIFY(npos == s1.find_first_not_of(Helper::abcd()[3], 6));

	string_view const sv1 = Helper::aababc();
	string_view const sv2 = Helper::a();
	string_view const sv3 = Helper::ab();
	string_view const sv4 = Helper::abc();
	string_view const sv5 = Helper::null_str();

	// (5) size_type find_first_not_of(const T& t, pos = 0)
	VERIFY(npos == s1.find_first_not_of(sv1));
	VERIFY(  2u == s1.find_first_not_of(sv2));
	VERIFY(  5u == s1.find_first_not_of(sv3));
	VERIFY(npos == s1.find_first_not_of(sv4));
	VERIFY(  0u == s1.find_first_not_of(sv5));
	VERIFY(  2u == s1.find_first_not_of(sv2, 1));
	VERIFY(  5u == s1.find_first_not_of(sv3, 1));
	VERIFY(npos == s1.find_first_not_of(sv4, 1));
	VERIFY(  1u == s1.find_first_not_of(sv5, 1));
	VERIFY(  2u == s1.find_first_not_of(sv2, 2));
	VERIFY(  5u == s1.find_first_not_of(sv3, 2));
	VERIFY(npos == s1.find_first_not_of(sv4, 2));
	VERIFY(  2u == s1.find_first_not_of(sv5, 2));
	VERIFY(  4u == s1.find_first_not_of(sv2, 3));
	VERIFY(  5u == s1.find_first_not_of(sv3, 3));
	VERIFY(npos == s1.find_first_not_of(sv4, 3));
	VERIFY(  3u == s1.find_first_not_of(sv5, 3));
	VERIFY(  4u == s1.find_first_not_of(sv2, 4));
	VERIFY(  5u == s1.find_first_not_of(sv3, 4));
	VERIFY(npos == s1.find_first_not_of(sv4, 4));
	VERIFY(  4u == s1.find_first_not_of(sv5, 4));
	VERIFY(  5u == s1.find_first_not_of(sv2, 5));
	VERIFY(  5u == s1.find_first_not_of(sv3, 5));
	VERIFY(npos == s1.find_first_not_of(sv4, 5));
	VERIFY(  5u == s1.find_first_not_of(sv5, 5));
	VERIFY(npos == s1.find_first_not_of(sv2, 6));
	VERIFY(npos == s1.find_first_not_of(sv3, 6));
	VERIFY(npos == s1.find_first_not_of(sv4, 6));
	VERIFY(npos == s1.find_first_not_of(sv5, 6));

	return true;
}
TYPED_TEST(BasicStringTest, FindFirstNotOfTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindFirstNotOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindLastOfTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto const npos = string::npos;

	string const s1 = Helper::aababc();
	string const s2 = Helper::a();
	string const s3 = Helper::ab();
	string const s4 = Helper::abc();
	string const s5 = Helper::null_str();

	// (1) size_type find_last_of(str, pos = npos)
	VERIFY(3    == s1.find_last_of(s2));
	VERIFY(4    == s1.find_last_of(s3));
	VERIFY(5    == s1.find_last_of(s4));
	VERIFY(npos == s1.find_last_of(s5));
	VERIFY(1    == s1.find_last_of(s2, 1));
	VERIFY(1    == s1.find_last_of(s3, 1));
	VERIFY(1    == s1.find_last_of(s4, 1));
	VERIFY(npos == s1.find_last_of(s5, 1));
	VERIFY(1    == s1.find_last_of(s2, 2));
	VERIFY(2    == s1.find_last_of(s3, 2));
	VERIFY(2    == s1.find_last_of(s4, 2));
	VERIFY(npos == s1.find_last_of(s5, 2));
	VERIFY(3    == s1.find_last_of(s2, 3));
	VERIFY(3    == s1.find_last_of(s3, 3));
	VERIFY(3    == s1.find_last_of(s4, 3));
	VERIFY(npos == s1.find_last_of(s5, 3));
	VERIFY(3    == s1.find_last_of(s2, 4));
	VERIFY(4    == s1.find_last_of(s3, 4));
	VERIFY(4    == s1.find_last_of(s4, 4));
	VERIFY(npos == s1.find_last_of(s5, 4));

	// (2) size_type find_last_of(s, pos, count)
	VERIFY(1    == s1.find_last_of(Helper::a(),   1, 1));
	VERIFY(1    == s1.find_last_of(Helper::ab(),  1, 2));
	VERIFY(1    == s1.find_last_of(Helper::abc(), 1, 3));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  1, 2));
	VERIFY(1    == s1.find_last_of(Helper::a(),   2, 1));
	VERIFY(2    == s1.find_last_of(Helper::ab(),  2, 2));
	VERIFY(1    == s1.find_last_of(Helper::ab(),  2, 1));
	VERIFY(2    == s1.find_last_of(Helper::abc(), 2, 3));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  2, 2));
	VERIFY(3    == s1.find_last_of(Helper::a(),   3, 1));
	VERIFY(3    == s1.find_last_of(Helper::ab(),  3, 2));
	VERIFY(3    == s1.find_last_of(Helper::abc(), 3, 3));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  3, 2));
	VERIFY(3    == s1.find_last_of(Helper::a(),   4, 1));
	VERIFY(4    == s1.find_last_of(Helper::ab(),  4, 2));
	VERIFY(3    == s1.find_last_of(Helper::ab(),  4, 1));
	VERIFY(4    == s1.find_last_of(Helper::abc(), 4, 3));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  4, 2));
	VERIFY(3    == s1.find_last_of(Helper::a(),   5, 1));
	VERIFY(4    == s1.find_last_of(Helper::ab(),  5, 2));
	VERIFY(5    == s1.find_last_of(Helper::abc(), 5, 3));
	VERIFY(4    == s1.find_last_of(Helper::abc(), 5, 2));
	VERIFY(5    == s1.find_last_of(Helper::cd(),  5, 2));

	// (3) size_type find_last_of(s, pos = npos)
	VERIFY(3    == s1.find_last_of(Helper::a()));
	VERIFY(4    == s1.find_last_of(Helper::ab()));
	VERIFY(5    == s1.find_last_of(Helper::abc()));
	VERIFY(5    == s1.find_last_of(Helper::cd()));
	VERIFY(1    == s1.find_last_of(Helper::a(),   1));
	VERIFY(1    == s1.find_last_of(Helper::ab(),  1));
	VERIFY(1    == s1.find_last_of(Helper::abc(), 1));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  1));
	VERIFY(1    == s1.find_last_of(Helper::a(),   2));
	VERIFY(2    == s1.find_last_of(Helper::ab(),  2));
	VERIFY(2    == s1.find_last_of(Helper::abc(), 2));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  2));
	VERIFY(3    == s1.find_last_of(Helper::a(),   3));
	VERIFY(3    == s1.find_last_of(Helper::ab(),  3));
	VERIFY(3    == s1.find_last_of(Helper::abc(), 3));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  3));
	VERIFY(3    == s1.find_last_of(Helper::a(),   4));
	VERIFY(4    == s1.find_last_of(Helper::ab(),  4));
	VERIFY(4    == s1.find_last_of(Helper::abc(), 4));
	VERIFY(npos == s1.find_last_of(Helper::cd(),  4));
	VERIFY(3    == s1.find_last_of(Helper::a(),   5));
	VERIFY(4    == s1.find_last_of(Helper::ab(),  5));
	VERIFY(5    == s1.find_last_of(Helper::abc(), 5));
	VERIFY(5    == s1.find_last_of(Helper::cd(),  5));

	// (4) size_type find_last_of(ch, pos = npos)
	VERIFY(3    == s1.find_last_of(Helper::abcd()[0]));
	VERIFY(4    == s1.find_last_of(Helper::abcd()[1]));
	VERIFY(5    == s1.find_last_of(Helper::abcd()[2]));
	VERIFY(npos == s1.find_last_of(Helper::abcd()[3]));
	VERIFY(1    == s1.find_last_of(Helper::abcd()[0], 2));
	VERIFY(2    == s1.find_last_of(Helper::abcd()[1], 2));
	VERIFY(npos == s1.find_last_of(Helper::abcd()[2], 2));
	VERIFY(npos == s1.find_last_of(Helper::abcd()[3], 2));

	string_view const sv1 = Helper::aababc();
	string_view const sv2 = Helper::a();
	string_view const sv3 = Helper::ab();
	string_view const sv4 = Helper::abc();
	string_view const sv5 = Helper::null_str();

	// (5) size_type find_last_of(const T& t, pos = npos)
	VERIFY(5    == s1.find_last_of(sv1));
	VERIFY(3    == s1.find_last_of(sv2));
	VERIFY(4    == s1.find_last_of(sv3));
	VERIFY(5    == s1.find_last_of(sv4));
	VERIFY(npos == s1.find_last_of(sv5));
	VERIFY(1    == s1.find_last_of(sv2, 1));
	VERIFY(1    == s1.find_last_of(sv3, 1));
	VERIFY(1    == s1.find_last_of(sv4, 1));
	VERIFY(npos == s1.find_last_of(sv5, 1));
	VERIFY(1    == s1.find_last_of(sv2, 2));
	VERIFY(2    == s1.find_last_of(sv3, 2));
	VERIFY(2    == s1.find_last_of(sv4, 2));
	VERIFY(npos == s1.find_last_of(sv5, 2));
	VERIFY(3    == s1.find_last_of(sv2, 3));
	VERIFY(3    == s1.find_last_of(sv3, 3));
	VERIFY(3    == s1.find_last_of(sv4, 3));
	VERIFY(npos == s1.find_last_of(sv5, 3));
	VERIFY(3    == s1.find_last_of(sv2, 4));
	VERIFY(4    == s1.find_last_of(sv3, 4));
	VERIFY(4    == s1.find_last_of(sv4, 4));
	VERIFY(npos == s1.find_last_of(sv5, 4));

	return true;
}
TYPED_TEST(BasicStringTest, FindLastOfTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindLastOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool FindLastNotOfTest()
{
	using string = bksge::basic_string<CharT>;
	using string_view = bksge::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto const npos = string::npos;

	string const s1 = Helper::aababc();
	string const s2 = Helper::a();
	string const s3 = Helper::ab();
	string const s4 = Helper::abc();
	string const s5 = Helper::null_str();

	// (1) size_type find_last_of(str, pos = npos)
	VERIFY(  5u == s1.find_last_not_of(s2));
	VERIFY(  5u == s1.find_last_not_of(s3));
	VERIFY(npos == s1.find_last_not_of(s4));
	VERIFY(  5u == s1.find_last_not_of(s5));
	VERIFY(npos == s1.find_last_not_of(s2, 1));
	VERIFY(npos == s1.find_last_not_of(s3, 1));
	VERIFY(npos == s1.find_last_not_of(s4, 1));
	VERIFY(  1u == s1.find_last_not_of(s5, 1));
	VERIFY(  2u == s1.find_last_not_of(s2, 2));
	VERIFY(npos == s1.find_last_not_of(s3, 2));
	VERIFY(npos == s1.find_last_not_of(s4, 2));
	VERIFY(  2u == s1.find_last_not_of(s5, 2));
	VERIFY(  2u == s1.find_last_not_of(s2, 3));
	VERIFY(npos == s1.find_last_not_of(s3, 3));
	VERIFY(npos == s1.find_last_not_of(s4, 3));
	VERIFY(  3u == s1.find_last_not_of(s5, 3));
	VERIFY(  4u == s1.find_last_not_of(s2, 4));
	VERIFY(npos == s1.find_last_not_of(s3, 4));
	VERIFY(npos == s1.find_last_not_of(s4, 4));
	VERIFY(  4u == s1.find_last_not_of(s5, 4));
	VERIFY(  5u == s1.find_last_not_of(s2, 5));
	VERIFY(  5u == s1.find_last_not_of(s3, 5));
	VERIFY(npos == s1.find_last_not_of(s4, 5));
	VERIFY(  5u == s1.find_last_not_of(s5, 5));
	VERIFY(  5u == s1.find_last_not_of(s2, 6));
	VERIFY(  5u == s1.find_last_not_of(s3, 6));
	VERIFY(npos == s1.find_last_not_of(s4, 6));
	VERIFY(  5u == s1.find_last_not_of(s5, 6));

	// (2) size_type find_last_of(s, pos, count)
	VERIFY(  0u == s1.find_last_not_of(Helper::abcd(), 0, 0));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 0, 1));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 0, 2));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 0, 3));
	VERIFY(  1u == s1.find_last_not_of(Helper::abcd(), 1, 0));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 1, 1));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 1, 2));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 1, 3));
	VERIFY(  2u == s1.find_last_not_of(Helper::abcd(), 2, 0));
	VERIFY(  2u == s1.find_last_not_of(Helper::abcd(), 2, 1));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 2, 2));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 2, 3));
	VERIFY(  3u == s1.find_last_not_of(Helper::abcd(), 3, 0));
	VERIFY(  2u == s1.find_last_not_of(Helper::abcd(), 3, 1));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 3, 2));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 3, 3));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd(), 4, 0));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd(), 4, 1));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 4, 2));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 4, 3));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd(), 5, 0));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd(), 5, 1));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd(), 5, 2));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 5, 3));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd(), 6, 0));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd(), 6, 1));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd(), 6, 2));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd(), 6, 3));

	// (3) size_type find_last_of(s, pos = npos)
	VERIFY(npos == s1.find_last_not_of(Helper::abcd()));
	VERIFY(  5u == s1.find_last_not_of(Helper::ab()));
	VERIFY(npos == s1.find_last_not_of(Helper::ab(), 0));
	VERIFY(npos == s1.find_last_not_of(Helper::ab(), 1));
	VERIFY(npos == s1.find_last_not_of(Helper::ab(), 2));
	VERIFY(npos == s1.find_last_not_of(Helper::ab(), 3));
	VERIFY(npos == s1.find_last_not_of(Helper::ab(), 4));
	VERIFY(  5u == s1.find_last_not_of(Helper::ab(), 5));
	VERIFY(  5u == s1.find_last_not_of(Helper::ab(), 6));

	// (4) size_type find_last_of(ch, pos = npos)
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[0]));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[1]));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd()[2]));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[3]));
	VERIFY(npos == s1.find_last_not_of(Helper::abcd()[0], 1));
	VERIFY(  1u == s1.find_last_not_of(Helper::abcd()[1], 1));
	VERIFY(  1u == s1.find_last_not_of(Helper::abcd()[2], 1));
	VERIFY(  1u == s1.find_last_not_of(Helper::abcd()[3], 1));
	VERIFY(  2u == s1.find_last_not_of(Helper::abcd()[0], 2));
	VERIFY(  1u == s1.find_last_not_of(Helper::abcd()[1], 2));
	VERIFY(  2u == s1.find_last_not_of(Helper::abcd()[2], 2));
	VERIFY(  2u == s1.find_last_not_of(Helper::abcd()[3], 2));
	VERIFY(  2u == s1.find_last_not_of(Helper::abcd()[0], 3));
	VERIFY(  3u == s1.find_last_not_of(Helper::abcd()[1], 3));
	VERIFY(  3u == s1.find_last_not_of(Helper::abcd()[2], 3));
	VERIFY(  3u == s1.find_last_not_of(Helper::abcd()[3], 3));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd()[0], 4));
	VERIFY(  3u == s1.find_last_not_of(Helper::abcd()[1], 4));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd()[2], 4));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd()[3], 4));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[0], 5));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[1], 5));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd()[2], 5));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[3], 5));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[0], 6));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[1], 6));
	VERIFY(  4u == s1.find_last_not_of(Helper::abcd()[2], 6));
	VERIFY(  5u == s1.find_last_not_of(Helper::abcd()[3], 6));

	string_view const sv1 = Helper::aababc();
	string_view const sv2 = Helper::a();
	string_view const sv3 = Helper::ab();
	string_view const sv4 = Helper::abc();
	string_view const sv5 = Helper::null_str();

	// (5) size_type find_last_of(const T& t, pos = npos)
	VERIFY(npos == s1.find_last_not_of(sv1));
	VERIFY(  5u == s1.find_last_not_of(sv2));
	VERIFY(  5u == s1.find_last_not_of(sv3));
	VERIFY(npos == s1.find_last_not_of(sv4));
	VERIFY(  5u == s1.find_last_not_of(sv5));
	VERIFY(npos == s1.find_last_not_of(sv2, 1));
	VERIFY(npos == s1.find_last_not_of(sv3, 1));
	VERIFY(npos == s1.find_last_not_of(sv4, 1));
	VERIFY(  1u == s1.find_last_not_of(sv5, 1));
	VERIFY(  2u == s1.find_last_not_of(sv2, 2));
	VERIFY(npos == s1.find_last_not_of(sv3, 2));
	VERIFY(npos == s1.find_last_not_of(sv4, 2));
	VERIFY(  2u == s1.find_last_not_of(sv5, 2));
	VERIFY(  2u == s1.find_last_not_of(sv2, 3));
	VERIFY(npos == s1.find_last_not_of(sv3, 3));
	VERIFY(npos == s1.find_last_not_of(sv4, 3));
	VERIFY(  3u == s1.find_last_not_of(sv5, 3));
	VERIFY(  4u == s1.find_last_not_of(sv2, 4));
	VERIFY(npos == s1.find_last_not_of(sv3, 4));
	VERIFY(npos == s1.find_last_not_of(sv4, 4));
	VERIFY(  4u == s1.find_last_not_of(sv5, 4));
	VERIFY(  5u == s1.find_last_not_of(sv2, 5));
	VERIFY(  5u == s1.find_last_not_of(sv3, 5));
	VERIFY(npos == s1.find_last_not_of(sv4, 5));
	VERIFY(  5u == s1.find_last_not_of(sv5, 5));
	VERIFY(  5u == s1.find_last_not_of(sv2, 6));
	VERIFY(  5u == s1.find_last_not_of(sv3, 6));
	VERIFY(npos == s1.find_last_not_of(sv4, 6));
	VERIFY(  5u == s1.find_last_not_of(sv5, 6));

	return true;
}
TYPED_TEST(BasicStringTest, FindLastNotOfTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(FindLastNotOfTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorPlusTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	// (1) string operator+(string const& lhs, string const& rhs)
	{
		string const s1 = Helper::ab();
		string const s2 = Helper::cde();
		auto r = s1 + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (2) string operator+(string const& lhs, CharT const* rhs)
	{
		string const s1 = Helper::ab();
		CharT const* s2 = Helper::cde();
		auto r = s1 + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (3) string operator+(string const& lhs, CharT rhs)
	{
		string const s1 = Helper::abcd();
		CharT const  s2 = Helper::cde()[2];
		auto r = s1 + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (4) string operator+(CharT const* lhs, string const& rhs)
	{
		CharT const* s1 = Helper::ab();
		string const s2 = Helper::cde();
		auto r = s1 + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (5) string operator+(CharT lhs, string const& rhs)
	{
		CharT const s1  = Helper::ab()[0];
		string const s2 = Helper::bcde();
		auto r = s1 + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (6) string operator+(string&& lhs, string&& rhs)
	{
		string s1 = Helper::ab();
		string s2 = Helper::cde();
		auto r = std::move(s1) + std::move(s2);
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	{
		string s1 = Helper::abcde();
		string s2;
		auto r = std::move(s1) + std::move(s2);
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	{
		string s1;
		string s2 = Helper::abcde();
		auto r = std::move(s1) + std::move(s2);
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (7) string operator+(string&& lhs, string const& rhs)
	{
		string s1 = Helper::ab();
		string const s2 = Helper::cde();
		auto r = std::move(s1) + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (8) string operator+(string&& lhs, CharT const* rhs)
	{
		string s1 = Helper::ab();
		CharT const* s2 = Helper::cde();
		auto r = std::move(s1) + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (9) string operator+(string&& lhs, CharT rhs)
	{
		string s1 = Helper::abcd();
		CharT const s2 = Helper::cde()[2];
		auto r = std::move(s1) + s2;
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (10) string operator+(string const& lhs, string&& rhs)
	{
		string const s1 = Helper::ab();
		string s2 = Helper::cde();
		auto r = s1 + std::move(s2);
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (11) string operator+(CharT const* lhs, string&& rhs)
	{
		CharT const* s1 = Helper::ab();
		string s2 = Helper::cde();
		auto r = s1 + std::move(s2);
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	// (12) string operator+(CharT lhs, string&& rhs)
	{
		CharT const s1 = Helper::ab()[0];
		string s2 = Helper::bcde();
		auto r = s1 + std::move(s2);
		static_assert(bksge::is_same<decltype(r), string>::value, "");
		VERIFY(r == Helper::abcde());
	}
	return true;
}
TYPED_TEST(BasicStringTest, OperatorPlusTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorPlusTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorCompareTest1()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	string const s1{Helper::aababc(), 6};	// "aababc"
	string const s2 = s1;				// "aababc"
	string const s3 = s1.substr(0, 5);	// "aabab"
	string const s4 = s1.substr(1, 5);	// "ababc"

	VERIFY( (s1 == s1));
	VERIFY( (s1 == s2));
	VERIFY(!(s1 == s3));
	VERIFY(!(s1 == s4));

	VERIFY(!(s1 != s1));
	VERIFY(!(s1 != s2));
	VERIFY( (s1 != s3));
	VERIFY( (s1 != s4));

	VERIFY(!(s1 <  s1));
	VERIFY(!(s1 <  s2));
	VERIFY(!(s1 <  s3));
	VERIFY( (s1 <  s4));

	VERIFY(!(s1 >  s1));
	VERIFY(!(s1 >  s2));
	VERIFY( (s1 >  s3));
	VERIFY(!(s1 >  s4));

	VERIFY( (s1 <= s1));
	VERIFY( (s1 <= s2));
	VERIFY(!(s1 <= s3));
	VERIFY( (s1 <= s4));

	VERIFY( (s1 >= s1));
	VERIFY( (s1 >= s2));
	VERIFY( (s1 >= s3));
	VERIFY(!(s1 >= s4));

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(bksge::is_eq(s1 <=> s1));
	VERIFY(bksge::is_eq(s1 <=> s2));
	VERIFY(bksge::is_gt(s1 <=> s3));
	VERIFY(bksge::is_lt(s1 <=> s4));
#endif

	return true;
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool OperatorCompareTest2()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	string const s1{Helper::abcd()};	// "abcd"
	CharT const* p1 = Helper::abcd();		// "abcd"
	CharT const* p2 = Helper::aababc();		// "aababc"
	CharT const* p3 = Helper::cd();			// "cd"

	VERIFY( (s1 == p1));
	VERIFY(!(s1 == p2));
	VERIFY(!(s1 == p3));

	VERIFY(!(s1 != p1));
	VERIFY( (s1 != p2));
	VERIFY( (s1 != p3));

	VERIFY(!(s1 <  p1));
	VERIFY(!(s1 <  p2));
	VERIFY( (s1 <  p3));

	VERIFY(!(s1 >  p1));
	VERIFY( (s1 >  p2));
	VERIFY(!(s1 >  p3));

	VERIFY( (s1 <= p1));
	VERIFY(!(s1 <= p2));
	VERIFY( (s1 <= p3));

	VERIFY( (s1 >= p1));
	VERIFY( (s1 >= p2));
	VERIFY(!(s1 >= p3));

	VERIFY( (p1 == s1));
	VERIFY(!(p2 == s1));
	VERIFY(!(p3 == s1));

	VERIFY(!(p1 != s1));
	VERIFY( (p2 != s1));
	VERIFY( (p3 != s1));

	VERIFY(!(p1 <  s1));
	VERIFY( (p2 <  s1));
	VERIFY(!(p3 <  s1));

	VERIFY(!(p1 >  s1));
	VERIFY(!(p2 >  s1));
	VERIFY( (p3 >  s1));

	VERIFY( (p1 <= s1));
	VERIFY( (p2 <= s1));
	VERIFY(!(p3 <= s1));

	VERIFY( (p1 >= s1));
	VERIFY(!(p2 >= s1));
	VERIFY( (p3 >= s1));

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(bksge::is_eq(s1 <=> p1));
	VERIFY(bksge::is_gt(s1 <=> p2));
	VERIFY(bksge::is_lt(s1 <=> p3));

	VERIFY(bksge::is_eq(p1 <=> s1));
	VERIFY(bksge::is_lt(p2 <=> s1));
	VERIFY(bksge::is_gt(p3 <=> s1));
#endif

	return true;
}

TYPED_TEST(BasicStringTest, OperatorCompareTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorCompareTest1<CharT>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(OperatorCompareTest2<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool StdEraseTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::abcde();
		CharT const c = Helper::abcd()[0];	// 'a'
		auto r = bksge::erase(s, c);
		VERIFY(s == Helper::bcde());
		VERIFY(r == 1);
	}
	{
		string s = Helper::abbccc();
		CharT const c = Helper::abcd()[2];	// 'c'
		auto r = bksge::erase(s, c);
		VERIFY(s == Helper::abb());
		VERIFY(r == 3);
	}
	{
		string s = Helper::abbccc();
		CharT const c = Helper::abcd()[3];	// 'd'
		auto r = bksge::erase(s, c);
		VERIFY(s == Helper::abbccc());
		VERIFY(r == 0);
	}
	return true;
}

TYPED_TEST(BasicStringTest, StdEraseTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(StdEraseTest<CharT>());
}

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool StdEraseIfTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::abcde();
		auto r = bksge::erase_if(s, [](CharT c) { return c == Helper::abcd()[0]; });	// 'a'
		VERIFY(s == Helper::bcde());
		VERIFY(r == 1);
	}
	{
		string s = Helper::abbccc();
		auto r = bksge::erase_if(s, [](CharT c) { return c == Helper::abcd()[2]; });	// 'c'
		VERIFY(s == Helper::abb());
		VERIFY(r == 3);
	}
	{
		string s = Helper::abbccc();
		auto r = bksge::erase_if(s, [](CharT c) { return c == Helper::abcd()[3]; });	// 'd'
		VERIFY(s == Helper::abbccc());
		VERIFY(r == 0);
	}
	return true;
}

TYPED_TEST(BasicStringTest, StdEraseIfTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(StdEraseIfTest<CharT>());
}

#if (BKSGE_CXX_STANDARD >= 14)
template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool LiteralsTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto s = Helper::abcd_s();
	static_assert(bksge::is_same<decltype(s), string>::value, "");

	VERIFY(s == Helper::abcd());
	VERIFY(s != Helper::ab());
	VERIFY(s != Helper::cd());

	return true;
}
TYPED_TEST(BasicStringTest, LiteralsTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(LiteralsTest<CharT>());
}
#endif

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool HashTest()
{
	using string = bksge::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	using Hash = bksge::hash<string>;

	string const s1{Helper::aababc()};
	string const s2{Helper::aababc(), 5};
	string const s3{Helper::aababc(), 4};
	string const s4{Helper::abcd()};

	Hash h;

	VERIFY(h(s1) == h(s1));
	VERIFY(h(s1) != h(s2));
	VERIFY(h(s1) != h(s3));
	VERIFY(h(s1) != h(s4));

	VERIFY(h(s2) == h(s2));
	VERIFY(h(s2) != h(s3));
	VERIFY(h(s2) != h(s4));

	VERIFY(h(s3) == h(s3));
	VERIFY(h(s3) != h(s4));

	VERIFY(h(s4) == h(s4));

	return true;
}
TYPED_TEST(BasicStringTest, HashTest)
{
	using CharT = TypeParam;
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<CharT>());
}

#undef VERIFY

}	// namespace basic_string_test

}	// namespace bksge_string_test

BKSGE_WARNING_POP();
