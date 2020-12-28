/**
 *	@file	unit_test_fnd_hash_functions_murmur_hash_3.cpp
 *
 *	@brief	murmur_hash_3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/hash_functions/murmur_hash_3.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hash_functions_test_helper.hpp"

namespace bksge_hash_functions_test
{

namespace murmur_hash_3_test
{

GTEST_TEST(HashTest, MurmurHash3Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::murmur_hash_3, char>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::murmur_hash_3, wchar_t>()));
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::murmur_hash_3, char8_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::murmur_hash_3, char16_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::murmur_hash_3, char32_t>()));
#endif
}

}	// namespace murmur_hash_3_test

}	// namespace bksge_hash_functions_test
