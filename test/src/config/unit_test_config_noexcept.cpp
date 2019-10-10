/**
 *	@file	unit_test_config_noexcept.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <gtest/gtest.h>

namespace bksge_config_noexcept_test
{

void f1();
void f2() BKSGE_NOEXCEPT;
void f3() BKSGE_NOEXCEPT_OR_NOTHROW;
void f4() BKSGE_NOEXCEPT_IF(true);
void f5() BKSGE_NOEXCEPT_IF(false);
void f6() BKSGE_NOEXCEPT_IF(BKSGE_NOEXCEPT_EXPR(f1()));
void f7() BKSGE_NOEXCEPT_IF(BKSGE_NOEXCEPT_EXPR(f2()));
void f8() BKSGE_NOEXCEPT_IF_EXPR(f1());
void f9() BKSGE_NOEXCEPT_IF_EXPR(f2());

GTEST_TEST(ConfigTest, NoexceptTest)
{
#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
	static_assert(!BKSGE_NOEXCEPT_EXPR(f1()), "");
	static_assert( BKSGE_NOEXCEPT_EXPR(f2()), "");
	static_assert( BKSGE_NOEXCEPT_EXPR(f3()), "");
	static_assert( BKSGE_NOEXCEPT_EXPR(f4()), "");
	static_assert(!BKSGE_NOEXCEPT_EXPR(f5()), "");
	static_assert(!BKSGE_NOEXCEPT_EXPR(f6()), "");
	static_assert( BKSGE_NOEXCEPT_EXPR(f7()), "");
	static_assert(!BKSGE_NOEXCEPT_EXPR(f8()), "");
	static_assert( BKSGE_NOEXCEPT_EXPR(f9()), "");
#endif
}

}	// namespace bksge_config_noexcept_test
