/**
 *	@file	unit_test_fnd_optional_hash.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <gtest/gtest.h>
#include <functional>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace hash_test
{

class S {}; // No hash specialization

template<class T>
auto f(int) -> decltype(std::hash<bksge::optional<T>>(), bksge::true_type());

template<class T>
auto f(...) -> decltype(bksge::false_type());

static_assert(!decltype(f<S>(0))::value, "");

template<typename T>
constexpr bool hashable()
{
	return bksge::is_invocable<std::hash<T>&, const T&>::value;
}

static_assert(!hashable<bksge::optional<S>>(), "");
static_assert(!hashable<bksge::optional<const S>>(), "");
static_assert( hashable<bksge::optional<int>>(), "");
static_assert( hashable<bksge::optional<const int>>(), "");

GTEST_TEST(OptionalTest, HashTest)
{
	int x = 42;
	bksge::optional<int> x2 = 42;
	EXPECT_TRUE(std::hash<int>()(x) == std::hash<bksge::optional<int>>()(x2));

	bksge::optional<const int> x3 = x2;
	EXPECT_TRUE(std::hash<int>()(x) == std::hash<bksge::optional<const int>>()(x3));
}

}	// namespace hash_test

}	// namespace bksge_optional_test
