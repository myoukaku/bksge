/**
 *	@file	unit_test_fnd_type_traits_aligned_union.cpp
 *
 *	@brief	aligned_union のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/aligned_union.hpp>
#include <bksge/fnd/type_traits/alignment_of.hpp>
#include <bksge/fnd/type_traits/is_standard_layout.hpp>
#include <bksge/fnd/type_traits/is_trivial.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <string>
#include <gtest/gtest.h>

GTEST_TEST(TypeTraitsTest, AlignedUnionTest)
{
	using aligned_1 = bksge::aligned_union<128, int>;
	static_assert(aligned_1::alignment_value == bksge::alignment_of<int>::value, "");
	static_assert(bksge::is_standard_layout<aligned_1::type>::value, "");
	static_assert(bksge::is_trivial<aligned_1::type>::value, "");
	static_assert(sizeof(aligned_1::type) >= 128, "");
	static_assert(bksge::is_same<aligned_1::type, bksge::aligned_union_t<128, int>>::value, "");

	using aligned_2 = bksge::aligned_union<64, char, short, std::string>;
	static_assert(aligned_2::alignment_value == bksge::alignment_of<std::string>::value, "");
	static_assert(bksge::is_standard_layout<aligned_2::type>::value, "");
	static_assert(bksge::is_trivial<aligned_2::type>::value, "");
	static_assert(sizeof(aligned_2::type) >= 64, "");
	static_assert(bksge::is_same<aligned_2::type, bksge::aligned_union_t<64, char, short, std::string>>::value, "");
}
