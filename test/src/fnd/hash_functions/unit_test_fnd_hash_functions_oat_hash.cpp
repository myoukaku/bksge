/**
 *	@file	unit_test_fnd_hash_functions_oat_hash.cpp
 *
 *	@brief	oat_hash のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/hash_functions/oat_hash.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hash_functions_test_helper.hpp"

namespace bksge_hash_functions_test
{

namespace oat_hash_test
{

GTEST_TEST(HashTest, OatHashTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::oat_hash, char>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::oat_hash, wchar_t>()));
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::oat_hash, char8_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::oat_hash, char16_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::oat_hash, char32_t>()));
#endif
}

}	// namespace oat_hash_test

}	// namespace bksge_hash_functions_test
