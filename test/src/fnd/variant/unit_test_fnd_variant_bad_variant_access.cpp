/**
 *	@file	unit_test_fnd_variant_bad_variant_access.cpp
 *
 *	@brief	bad_variant_access のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/exception/exception.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"

GTEST_TEST(VariantTest, BadVariantAccessTest)
{
	static_assert(bksge::is_base_of<bksge::exception, bksge::bad_variant_access>::value, "");
	static_assert(noexcept(bksge::bad_variant_access{}), "must be noexcept");
	static_assert(noexcept(bksge::bad_variant_access{}.what()), "must be noexcept");
	bksge::bad_variant_access ex;
	EXPECT_TRUE(ex.what() != nullptr);
}
