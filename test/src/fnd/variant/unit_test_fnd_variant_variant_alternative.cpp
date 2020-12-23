/**
 *	@file	unit_test_fnd_variant_variant_alternative.cpp
 *
 *	@brief	variant_alternative のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace variant_alternative_test
{

template <typename V, bksge::size_t I, typename E>
void test()
{
	static_assert(bksge::is_same<typename bksge::variant_alternative<I, V>::type, E>::value, "");
	static_assert(bksge::is_same<typename bksge::variant_alternative<I, const V>::type, const E>::value, "");
	static_assert(bksge::is_same<typename bksge::variant_alternative<I, volatile V>::type, volatile E>::value, "");
	static_assert(bksge::is_same<typename bksge::variant_alternative<I, const volatile V>::type, const volatile E>::value, "");
	static_assert(bksge::is_same<bksge::variant_alternative_t<I, V>, E>::value, "");
	static_assert(bksge::is_same<bksge::variant_alternative_t<I, const V>, const E>::value, "");
	static_assert(bksge::is_same<bksge::variant_alternative_t<I, volatile V>, volatile E>::value, "");
	static_assert(bksge::is_same<bksge::variant_alternative_t<I, const volatile V>, const volatile E>::value, "");
}

GTEST_TEST(VariantTest, VariantAlternativeTest)
{
	{
		using V = bksge::variant<int, void *, const void *, long double>;
		test<V, 0, int>();
		test<V, 1, void *>();
		test<V, 2, const void *>();
		test<V, 3, long double>();
	}
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int, int &, const int &, int &&, long double>;
		test<V, 0, int>();
		test<V, 1, int &>();
		test<V, 2, const int &>();
		test<V, 3, int &&>();
		test<V, 4, long double>();
	}
#endif
}

}	// namespace variant_alternative_test

}	// namespace bksge_variant_test
