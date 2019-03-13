/**
 *	@file	unit_test_config_alignof.cpp
 *
 *	@brief	BKSGE_ALIGNOF のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

namespace bksge_config_alignof_test
{

struct empty{};

GTEST_TEST(ConfigTest, AlignofTest)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(1u, BKSGE_ALIGNOF(std::int8_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, BKSGE_ALIGNOF(std::int16_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, BKSGE_ALIGNOF(std::int32_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(8u, BKSGE_ALIGNOF(std::int64_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(1u, BKSGE_ALIGNOF(empty));
	BKSGE_CONSTEXPR_EXPECT_EQ(BKSGE_ALIGNOF(int*), BKSGE_ALIGNOF(void*));
}

}	// namespace bksge_config_alignof_test
