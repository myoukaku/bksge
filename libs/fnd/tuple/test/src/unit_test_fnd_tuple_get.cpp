/**
 *	@file	unit_test_fnd_tuple_get.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace get_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	using std::get;
	{
		bksge::tuple<int> t(3);
		int& i = get<0>(t);
		VERIFY(i == 3);
		int&& j = get<0>(std::move(t));
		VERIFY(j == 3);
	}
	{
		bksge::tuple<float, int> const t(1.5f, 2);

		float const& f1 = get<0>(t);
		int   const& i1 = get<1>(t);
		VERIFY(f1 == 1.5f);
		VERIFY(i1 == 2);

		float const&& f2 = get<0>(std::move(t));
		int   const&& i2 = get<1>(std::move(t));
		VERIFY(f2 == 1.5f);
		VERIFY(i2 == 2);
	}
	{
		bksge::tuple<char, float, int> const t('a', 2.5f, 4);

		char  const& c1 = get<0>(t);
		float const& f1 = get<1>(t);
		int   const& i1 = get<2>(t);
		VERIFY(c1 == 'a');
		VERIFY(f1 == 2.5f);
		VERIFY(i1 == 4);

		char  const&& c2 = get<0>(std::move(t));
		float const&& f2 = get<1>(std::move(t));
		int   const&& i2 = get<2>(std::move(t));
		VERIFY(c2 == 'a');
		VERIFY(f2 == 2.5f);
		VERIFY(i2 == 4);
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	using std::get;
	{
		bksge::tuple<int> t(3);
		int& i = get<int>(t);
		VERIFY(i == 3);
		int&& j = get<int>(std::move(t));
		VERIFY(j == 3);
	}
	{
		bksge::tuple<float, int> const t(1.5f, 2);

		float const& f1 = get<float>(t);
		int   const& i1 = get<int>(t);
		VERIFY(f1 == 1.5f);
		VERIFY(i1 == 2);

		float const&& f2 = get<float>(std::move(t));
		int   const&& i2 = get<int>(std::move(t));
		VERIFY(f2 == 1.5f);
		VERIFY(i2 == 2);
	}
	{
		bksge::tuple<char, float, int> const t('a', 3.5f, 4);

		char  const& c1 = get<char>(t);
		float const& f1 = get<float>(t);
		int   const& i1 = get<int>(t);
		VERIFY(c1 == 'a');
		VERIFY(f1 == 3.5f);
		VERIFY(i1 == 4);

		char  const&& c2 = get<char>(std::move(t));
		float const&& f2 = get<float>(std::move(t));
		int   const&& i2 = get<int>(std::move(t));
		VERIFY(c2 == 'a');
		VERIFY(f2 == 3.5f);
		VERIFY(i2 == 4);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, GetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test01()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test02()));
}

}	// namespace get_test

}	// namespace bksge_tuple_test
