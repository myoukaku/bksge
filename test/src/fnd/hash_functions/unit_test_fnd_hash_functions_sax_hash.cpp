/**
 *	@file	unit_test_fnd_hash_functions_sax_hash.cpp
 *
 *	@brief	sax_hash のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/hash_functions/sax_hash.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hash_functions_test_helper.hpp"

namespace bksge_hash_functions_test
{

namespace sax_hash_test
{

GTEST_TEST(HashTest, SaxHashTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::sax_hash, char>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::sax_hash, wchar_t>()));
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::sax_hash, char8_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::sax_hash, char16_t>()));
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::sax_hash, char32_t>()));
#endif
}

}	// namespace sax_hash_test

}	// namespace bksge_hash_functions_test
