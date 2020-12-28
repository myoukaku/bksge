/**
 *	@file	unit_test_fnd_hash_functions_crc32.cpp
 *
 *	@brief	crc32 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/hash_functions/crc32.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hash_functions_test_helper.hpp"

namespace bksge_hash_functions_test
{

namespace crc32_test
{

GTEST_TEST(HashTest, Crc32Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::crc32, char>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::crc32, wchar_t>()));
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::crc32, char8_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::crc32, char16_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::crc32, char32_t>()));
#endif
}

}	// namespace crc32_test

}	// namespace bksge_hash_functions_test
