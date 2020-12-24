/**
 *	@file	unit_test_fnd_variant_assign_conv.cpp
 *
 *	@brief	variant& operator=(T&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>
#include <string>
#include <gtest/gtest.h>
#include "fnd/variant/variant_test_helpers.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_variant_test
{

namespace assign_conv_test
{

GTEST_TEST(VariantTest, AssignConvTest)
{
	static_assert(!bksge::is_assignable<bksge::variant<int, int>, int>::value, "");
	static_assert(!bksge::is_assignable<bksge::variant<long, long long>, int>::value, "");
	//static_assert( bksge::is_assignable<bksge::variant<char>, int>::value == VariantAllowsNarrowingConversions, "");

	//static_assert( bksge::is_assignable<bksge::variant<std::string, float>, int>::value == VariantAllowsNarrowingConversions, "");
	//static_assert( bksge::is_assignable<bksge::variant<std::string, double>, int>::value == VariantAllowsNarrowingConversions, "");
// TODO
//	static_assert(!bksge::is_assignable<bksge::variant<std::string, bool>, int>::value, "");

// TODO
//	static_assert(!bksge::is_assignable<bksge::variant<int, bool>, decltype("meow")>::value, "");
	static_assert(!bksge::is_assignable<bksge::variant<int, const bool>, decltype("meow")>::value, "");
	static_assert(!bksge::is_assignable<bksge::variant<int, const volatile bool>, decltype("meow")>::value, "");

// TODO
//	static_assert(!bksge::is_assignable<bksge::variant<bool>, bksge::true_type>::value, "");
	static_assert(!bksge::is_assignable<bksge::variant<bool>, bksge::unique_ptr<char> >::value, "");
// TODO
//	static_assert(!bksge::is_assignable<bksge::variant<bool>, decltype(nullptr)>::value, "");
}

}	// namespace assign_conv_test

}	// namespace bksge_variant_test

BKSGE_WARNING_POP();
