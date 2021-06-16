/**
 *	@file	unit_test_fnd_hash_functions_fnv_hash.cpp
 *
 *	@brief	fnv_hash のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/hash_functions/fnv_hash.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hash_functions_test_helper.hpp"

namespace bksge_hash_functions_test
{

namespace fnv_hash_test
{

GTEST_TEST(HashTest, FnvHashTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::fnv_hash, char>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::fnv_hash, wchar_t>()));
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::fnv_hash, char8_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::fnv_hash, char16_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::fnv_hash, char32_t>()));
#endif
}

}	// namespace fnv_hash_test

}	// namespace bksge_hash_functions_test
