/**
 *	@file	unit_test_fnd_config_alignof.cpp
 *
 *	@brief	BKSGE_ALIGNOF のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>

namespace bksge_config_alignof_test
{

struct empty{};

static_assert(1u == BKSGE_ALIGNOF(std::int8_t), "");
static_assert(2u == BKSGE_ALIGNOF(std::int16_t), "");
static_assert(4u == BKSGE_ALIGNOF(std::int32_t), "");
static_assert(8u == BKSGE_ALIGNOF(std::int64_t), "");
static_assert(1u == BKSGE_ALIGNOF(empty), "");
static_assert(BKSGE_ALIGNOF(int*) == BKSGE_ALIGNOF(void*), "");

}	// namespace bksge_config_alignof_test
