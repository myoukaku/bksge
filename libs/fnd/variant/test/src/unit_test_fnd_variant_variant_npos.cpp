/**
 *	@file	unit_test_fnd_variant_variant_npos.cpp
 *
 *	@brief	variant_npos のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant_npos.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "test_macros.hpp"

GTEST_TEST(VariantTest, VariantNposTest)
{
	static_assert(bksge::variant_npos == static_cast<std::size_t>(-1), "");
}
