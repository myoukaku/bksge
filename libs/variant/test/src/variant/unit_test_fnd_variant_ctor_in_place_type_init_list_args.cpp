/**
 *	@file	unit_test_fnd_variant_ctor_in_place_type_init_list_args.cpp
 *
 *	@brief	variant::variant(in_place_type_t<Tp>, initializer_list<Up>, Args&&...) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/initializer_list.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "test_convertible.hpp"
#include "test_macros.hpp"
#include "constexpr_test.hpp"

namespace bksge_variant_test
{

namespace ctor_in_place_type_init_list_args_test
{

struct InitList
{
	bksge::size_t size;

	BKSGE_CXX14_CONSTEXPR
	InitList(bksge::initializer_list<int> il)
		: size(il.size()) {}
};

struct InitListArg
{
	bksge::size_t size;
	int value;

	BKSGE_CXX14_CONSTEXPR
	InitListArg(bksge::initializer_list<int> il, int v)
		: size(il.size()), value(v) {}
};

void test_ctor_sfinae()
{
	using IL = bksge::initializer_list<int>;
	{
		// just init list
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(bksge::is_constructible<V, bksge::in_place_type_t<InitList>, IL>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<InitList>, IL>(), "");
	}
	{
		// too many arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<InitList>, IL, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<InitList>, IL, int>(), "");
	}
	{
		// too few arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<InitListArg>, IL>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<InitListArg>, IL>(), "");
	}
	{
		// init list and arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(bksge::is_constructible<V, bksge::in_place_type_t<InitListArg>, IL, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<InitListArg>, IL, int>(), "");
	}
	{
		// not constructible from arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<int>, IL>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<int>, IL>(), "");
	}
	{
		// duplicate types in variant
		using V = bksge::variant<InitListArg, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<InitListArg>, IL, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_type_t<InitListArg>, IL, int>(), "");
	}
}

void test_ctor_basic()
{
	using std::get;
	{
		BKSGE_CXX14_CONSTEXPR bksge::variant<InitList, InitListArg> v(
			bksge::in_place_type_t<InitList>{}, {1, 2, 3});
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(v.index() == 0);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(get<0>(v).size == 3);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::variant<InitList, InitListArg> v(
			bksge::in_place_type_t<InitListArg>{}, {1, 2, 3, 4}, 42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(v.index() == 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(get<1>(v).size == 4);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(get<1>(v).value == 42);
	}
}

GTEST_TEST(VariantTest, CtorInPlaceTypeInitListArgsTest)
{
	test_ctor_basic();
	test_ctor_sfinae();
}

}	// namespace ctor_in_place_type_init_list_args_test

}	// namespace bksge_variant_test
