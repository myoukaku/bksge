/**
 *	@file	unit_test_fnd_cstring.cpp
 *
 *	@brief	cstring のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cstring.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <type_traits>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4996);
BKSGE_WARNING_DISABLE_CLANG("-Wdeprecated-declarations");

GTEST_TEST(CStringTest, CStringTest)
{
	std::size_t s = 0;
	void* vp = 0;
	const void* vpc = 0;
	char* cp = 0;
	const char* cpc = 0;
	char ca[32] = {};
	static_assert((std::is_same<decltype(bksge::strcpy(cp, cpc)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strcpy(ca, cpc)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strncpy(cp, cpc, s)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strcat(cp, cpc)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strcat(ca, cpc)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strncat(cp, cpc, s)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strcmp(cpc, cpc)), int>::value), "");
	static_assert((std::is_same<decltype(bksge::strncmp(cpc, cpc, s)), int>::value), "");
	static_assert((std::is_same<decltype(bksge::strcoll(cpc, cpc)), int>::value), "");
	static_assert((std::is_same<decltype(bksge::strxfrm(cp, cpc, s)), std::size_t>::value), "");
	static_assert((std::is_same<decltype(bksge::strchr(cp, 0)), char*>::value), "");
//	static_assert((std::is_same<decltype(bksge::strchr(cpc, 0)), const char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strcspn(cpc, cpc)), std::size_t>::value), "");
	static_assert((std::is_same<decltype(bksge::strpbrk(cp, cpc)), char*>::value), "");
//	static_assert((std::is_same<decltype(bksge::strpbrk(cpc, cpc)), const char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strrchr(cp, 0)), char*>::value), "");
//	static_assert((std::is_same<decltype(bksge::strrchr(cpc, 0)), const char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strspn(cpc, cpc)), std::size_t>::value), "");
	static_assert((std::is_same<decltype(bksge::strstr(cp, cpc)), char*>::value), "");
//	static_assert((std::is_same<decltype(bksge::strstr(cpc, cpc)), const char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strtok(cp, cpc)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strerror(0)), char*>::value), "");
	static_assert((std::is_same<decltype(bksge::strlen(cpc)), std::size_t>::value), "");
	static_assert((std::is_same<decltype(bksge::memchr(vp, 0, s)), void*>::value), "");
//	static_assert((std::is_same<decltype(bksge::memchr(vpc, 0, s)), const void*>::value), "");
	static_assert((std::is_same<decltype(bksge::memcmp(vpc, vpc, s)), int>::value), "");
	static_assert((std::is_same<decltype(bksge::memcpy(vp, vpc, s)), void*>::value), "");
	static_assert((std::is_same<decltype(bksge::memset(vp, 0, s)), void*>::value), "");
	static_assert((std::is_same<decltype(bksge::memmove(vp, vpc, s)), void*>::value), "");
}

BKSGE_WARNING_POP();
