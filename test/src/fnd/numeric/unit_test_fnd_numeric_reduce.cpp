/**
 *	@file	unit_test_fnd_numeric_reduce.cpp
 *
 *	@brief	reduce のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/reduce.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace reduce_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[5] = {1, 2, 3, 4, 5};
	test_container<int, input_iterator_wrapper> con(a);
	int res = bksge::reduce(con.begin(), con.end());
	VERIFY(res == 15);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	bool b[] = {true, false, true, true, false, true, false, true, true, false};
	int res = bksge::reduce(bksge::begin(b), bksge::end(b), 100);
	VERIFY(res == 106);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	auto res = bksge::reduce(bksge::begin(a), bksge::end(a), (short)11);
	static_assert(bksge::is_same<decltype(res), short>::value, "");
	VERIFY(res == 66);

	auto res2 = bksge::reduce(bksge::begin(a), bksge::end(a), -1l, bksge::multiplies<>{});
	static_assert(bksge::is_same<decltype(res2), long>::value, "");
	VERIFY(res2 == -3628800);

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, ReduceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace reduce_test

}	// namespace bksge_numeric_test
