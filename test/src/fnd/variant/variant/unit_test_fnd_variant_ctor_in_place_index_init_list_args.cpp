/**
 *	@file	unit_test_fnd_variant_ctor_in_place_index_init_list_args.cpp
 *
 *	@brief	variant::variant(in_place_index_t<I>, initializer_list<Up>, Args&&...) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <initializer_list>
#include <gtest/gtest.h>
#include "fnd/variant/test_convertible.hpp"
#include "fnd/variant/test_macros.hpp"
#include "constexpr_test.hpp"

namespace bksge_variant_test
{

namespace ctor_in_place_index_init_list_args_test
{

struct InitList
{
	std::size_t size;

	BKSGE_CXX14_CONSTEXPR
	InitList(std::initializer_list<int> il)
		: size(il.size()) {}
};

struct InitListArg
{
	std::size_t size;
	int value;

	BKSGE_CXX14_CONSTEXPR
	InitListArg(std::initializer_list<int> il, int v)
		: size(il.size()), value(v) {}
};

void test_ctor_sfinae()
{
	using IL = std::initializer_list<int>;
	{
		// just init list
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(bksge::is_constructible<V, bksge::in_place_index_t<0>, IL>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<0>, IL>(), "");
	}
	{
		// too many arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_index_t<0>, IL, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<0>, IL, int>(), "");
	}
	{
		// too few arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_index_t<1>, IL>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<1>, IL>(), "");
	}
	{
		// init list and arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(bksge::is_constructible<V, bksge::in_place_index_t<1>, IL, int>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<1>, IL, int>(), "");
	}
	{
		// not constructible from arguments
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_index_t<2>, IL>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<2>, IL>(), "");
	}
#if !(defined(BKSGE_GCC) && (BKSGE_GCC < 80000))
	{
		// index not in variant
		using V = bksge::variant<InitList, InitListArg, int>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_index_t<3>, IL>::value, "");
		static_assert(!test_convertible<V, bksge::in_place_index_t<3>, IL>(), "");
	}
#endif
}

void test_ctor_basic()
{
	using std::get;
	{
		BKSGE_CXX14_CONSTEXPR bksge::variant<InitList, InitListArg, InitList> v(
			bksge::in_place_index_t<0>{}, {1, 2, 3});
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(v.index() == 0);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(get<0>(v).size == 3);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::variant<InitList, InitListArg, InitList> v(
			bksge::in_place_index_t<2>{}, {1, 2, 3});
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(v.index() == 2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(get<2>(v).size == 3);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::variant<InitList, InitListArg, InitListArg> v(
			bksge::in_place_index_t<1>{}, {1, 2, 3, 4}, 42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(v.index() == 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(get<1>(v).size == 4);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(get<1>(v).value == 42);
	}
}

GTEST_TEST(VariantTest, CtorInPlaceIndexInitListArgsTest)
{
	test_ctor_basic();
	test_ctor_sfinae();
}

}	// namespace ctor_in_place_index_init_list_args_test

}	// namespace bksge_variant_test
