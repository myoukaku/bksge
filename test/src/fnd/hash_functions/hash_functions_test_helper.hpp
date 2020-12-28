﻿/**
 *	@file	hash_functions_test_helper.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_HASH_FUNCTIONS_HASH_FUNCTIONS_TEST_HELPER_HPP
#define UNIT_TEST_FND_HASH_FUNCTIONS_HASH_FUNCTIONS_TEST_HELPER_HPP

#include <bksge/fnd/config.hpp>

namespace
{

template <typename CharT>
struct HashFuncTestHelper;

template <>
struct HashFuncTestHelper<char>
{
	BKSGE_CONSTEXPR static const char* a()     { return "a"; }
	BKSGE_CONSTEXPR static const char* aa()    { return "aa"; }
	BKSGE_CONSTEXPR static const char* aaa()   { return "aaa"; }
	BKSGE_CONSTEXPR static const char* abc()   { return "abc"; }
	BKSGE_CONSTEXPR static const char* acb()   { return "acb"; }
	BKSGE_CONSTEXPR static const char* bac()   { return "bac"; }
	BKSGE_CONSTEXPR static const char* bca()   { return "bca"; }
	BKSGE_CONSTEXPR static const char* cab()   { return "cab"; }
	BKSGE_CONSTEXPR static const char* cba()   { return "cba"; }
	BKSGE_CONSTEXPR static const char* abcde() { return "abcde"; }
};

template <>
struct HashFuncTestHelper<wchar_t>
{
	BKSGE_CONSTEXPR static const wchar_t* a()     { return L"a"; }
	BKSGE_CONSTEXPR static const wchar_t* aa()    { return L"aa"; }
	BKSGE_CONSTEXPR static const wchar_t* aaa()   { return L"aaa"; }
	BKSGE_CONSTEXPR static const wchar_t* abc()   { return L"abc"; }
	BKSGE_CONSTEXPR static const wchar_t* acb()   { return L"acb"; }
	BKSGE_CONSTEXPR static const wchar_t* bac()   { return L"bac"; }
	BKSGE_CONSTEXPR static const wchar_t* bca()   { return L"bca"; }
	BKSGE_CONSTEXPR static const wchar_t* cab()   { return L"cab"; }
	BKSGE_CONSTEXPR static const wchar_t* cba()   { return L"cba"; }
	BKSGE_CONSTEXPR static const wchar_t* abcde() { return L"abcde"; }
};

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
template <>
struct HashFuncTestHelper<char8_t>
{
	BKSGE_CONSTEXPR static const char8_t* a()     { return u8"a"; }
	BKSGE_CONSTEXPR static const char8_t* aa()    { return u8"aa"; }
	BKSGE_CONSTEXPR static const char8_t* aaa()   { return u8"aaa"; }
	BKSGE_CONSTEXPR static const char8_t* abc()   { return u8"abc"; }
	BKSGE_CONSTEXPR static const char8_t* acb()   { return u8"acb"; }
	BKSGE_CONSTEXPR static const char8_t* bac()   { return u8"bac"; }
	BKSGE_CONSTEXPR static const char8_t* bca()   { return u8"bca"; }
	BKSGE_CONSTEXPR static const char8_t* cab()   { return u8"cab"; }
	BKSGE_CONSTEXPR static const char8_t* cba()   { return u8"cba"; }
	BKSGE_CONSTEXPR static const char8_t* abcde() { return u8"abcde"; }
};
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
template <>
struct HashFuncTestHelper<char16_t>
{
	BKSGE_CONSTEXPR static const char16_t* a()     { return u"a"; }
	BKSGE_CONSTEXPR static const char16_t* aa()    { return u"aa"; }
	BKSGE_CONSTEXPR static const char16_t* aaa()   { return u"aaa"; }
	BKSGE_CONSTEXPR static const char16_t* abc()   { return u"abc"; }
	BKSGE_CONSTEXPR static const char16_t* acb()   { return u"acb"; }
	BKSGE_CONSTEXPR static const char16_t* bac()   { return u"bac"; }
	BKSGE_CONSTEXPR static const char16_t* bca()   { return u"bca"; }
	BKSGE_CONSTEXPR static const char16_t* cab()   { return u"cab"; }
	BKSGE_CONSTEXPR static const char16_t* cba()   { return u"cba"; }
	BKSGE_CONSTEXPR static const char16_t* abcde() { return u"abcde"; }
};
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
template <>
struct HashFuncTestHelper<char32_t>
{
	BKSGE_CONSTEXPR static const char32_t* a()     { return U"a"; }
	BKSGE_CONSTEXPR static const char32_t* aa()    { return U"aa"; }
	BKSGE_CONSTEXPR static const char32_t* aaa()   { return U"aaa"; }
	BKSGE_CONSTEXPR static const char32_t* abc()   { return U"abc"; }
	BKSGE_CONSTEXPR static const char32_t* acb()   { return U"acb"; }
	BKSGE_CONSTEXPR static const char32_t* bac()   { return U"bac"; }
	BKSGE_CONSTEXPR static const char32_t* bca()   { return U"bca"; }
	BKSGE_CONSTEXPR static const char32_t* cab()   { return U"cab"; }
	BKSGE_CONSTEXPR static const char32_t* cba()   { return U"cba"; }
	BKSGE_CONSTEXPR static const char32_t* abcde() { return U"abcde"; }
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Hash, typename CharT>
inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using Helper = HashFuncTestHelper<CharT>;
	{
		Hash f;

		auto h1 = f(Helper::a(), 1);
		auto h2 = f(Helper::a());
		auto h3 = f(Helper::aa(), 2);
		auto h4 = f(Helper::aa());
		auto h5 = f(Helper::aaa(), 3);
		auto h6 = f(Helper::aaa());

		VERIFY(h1 == h2);
		VERIFY(h3 == h4);
		VERIFY(h5 == h6);

		VERIFY(h1 != h3);
		VERIFY(h1 != h5);
		VERIFY(h3 != h5);
	}
	{
		Hash f;

		auto h1 = f(Helper::abc());
		auto h2 = f(Helper::acb());
		auto h3 = f(Helper::bac());
		auto h4 = f(Helper::bca());
		auto h5 = f(Helper::cab());
		auto h6 = f(Helper::cba());

		VERIFY(h1 != h2);
		VERIFY(h1 != h3);
		VERIFY(h1 != h4);
		VERIFY(h1 != h5);
		VERIFY(h1 != h6);
		VERIFY(h2 != h3);
		VERIFY(h2 != h4);
		VERIFY(h2 != h5);
		VERIFY(h2 != h6);
		VERIFY(h3 != h4);
		VERIFY(h3 != h5);
		VERIFY(h3 != h6);
		VERIFY(h4 != h5);
		VERIFY(h4 != h6);
		VERIFY(h5 != h6);

		auto h1_2 = f(Helper::abc());
		auto h2_2 = f(Helper::acb());
		auto h3_2 = f(Helper::bac());
		auto h4_2 = f(Helper::bca());
		auto h5_2 = f(Helper::cab());
		auto h6_2 = f(Helper::cba());

		VERIFY(h1 == h1_2);
		VERIFY(h2 == h2_2);
		VERIFY(h3 == h3_2);
		VERIFY(h4 == h4_2);
		VERIFY(h5 == h5_2);
		VERIFY(h6 == h6_2);
	}
	{
		Hash f1(0x01234567);
		Hash f2;
		VERIFY(f1(Helper::abcde()) != f2(Helper::abcde()));
		f2.set_seed(0x01234567);
		VERIFY(f1(Helper::abcde()) == f2(Helper::abcde()));
	}
	return true;
}

#undef VERIFY

}	// namespace

#endif // UNIT_TEST_FND_HASH_FUNCTIONS_HASH_FUNCTIONS_TEST_HELPER_HPP
