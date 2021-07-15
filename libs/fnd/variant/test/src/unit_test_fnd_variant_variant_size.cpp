/**
 *	@file	unit_test_fnd_variant_variant_size.cpp
 *
 *	@brief	variant_size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant_size.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "test_macros.hpp"

namespace bksge_variant_test
{

namespace variant_size_test
{

template <typename V, std::size_t E>
void test()
{
	static_assert(bksge::variant_size<V>::value == E, "");
	static_assert(bksge::variant_size<const V>::value == E, "");
	static_assert(bksge::variant_size<volatile V>::value == E, "");
	static_assert(bksge::variant_size<const volatile V>::value == E, "");
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	static_assert(bksge::variant_size_v<V> == E, "");
	static_assert(bksge::variant_size_v<const V> == E, "");
	static_assert(bksge::variant_size_v<volatile V> == E, "");
	static_assert(bksge::variant_size_v<const volatile V> == E, "");
#endif
	static_assert(bksge::is_base_of<bksge::integral_constant<std::size_t, E>, bksge::variant_size<V>>::value, "");
};

GTEST_TEST(VariantTest, VariantSizeTest)
{
	test<bksge::variant<>, 0>();
	test<bksge::variant<void *>, 1>();
	test<bksge::variant<long, long, void *, double>, 4>();
}

}	// namespace variant_size_test

}	// namespace bksge_variant_test
