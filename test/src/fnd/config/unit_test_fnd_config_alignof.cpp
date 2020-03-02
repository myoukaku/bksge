/**
 *	@file	unit_test_fnd_config_alignof.cpp
 *
 *	@brief	BKSGE_ALIGNOF のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_config_alignof_test
{

struct empty{};

GTEST_TEST(ConfigTest, AlignofTest)
{
	BKSGE_CONSTEXPR_EXPECT_EQ(1u, BKSGE_ALIGNOF(bksge::int8_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, BKSGE_ALIGNOF(bksge::int16_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, BKSGE_ALIGNOF(bksge::int32_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(8u, BKSGE_ALIGNOF(bksge::int64_t));
	BKSGE_CONSTEXPR_EXPECT_EQ(1u, BKSGE_ALIGNOF(empty));
	BKSGE_CONSTEXPR_EXPECT_EQ(BKSGE_ALIGNOF(int*), BKSGE_ALIGNOF(void*));
}

}	// namespace bksge_config_alignof_test
