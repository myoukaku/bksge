/**
 *	@file	unit_test_fnd_ranges_iota_view.cpp
 *
 *	@brief	ranges::iota_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/iota_view.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace iota_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	auto v = bksge::ranges::iota_view{1, 4};
#else
	auto v = bksge::ranges::iota_view<int, int>{1, 4};
#endif
	VERIFY(v.size() == 3);

	int vals[5] ={};
	int* out = vals;
	for (int i : v)
	{
		*out++ = i;
	}
	VERIFY(out == vals + 3);
	VERIFY(vals[0] == 1);
	VERIFY(vals[1] == 2);
	VERIFY(vals[2] == 3);
	VERIFY(vals[3] == 0);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	auto v = bksge::ranges::views::iota(4);
	auto it = v.begin();
	VERIFY(*it == 4);
	++it;
	VERIFY(*it == 5);
	it++;
	VERIFY(*it == 6);
	--it;
	VERIFY(*it == 5);
	it--;
	VERIFY(*it == 4);

	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	auto v = bksge::ranges::views::iota(10, 15);
	VERIFY(v.size() == 5);

	auto it = v.begin();
	VERIFY(it[0] == 10);
	VERIFY(it[1] == 11);
	VERIFY(*(it + 2) == 12);
	VERIFY(*(3 + it) == 13);

	VERIFY(*it == 10);
	it += 2;
	VERIFY(*it == 12);
	it += 2;
	VERIFY(*it == 14);

	VERIFY(*(it - 1) == 13);

	VERIFY((it - v.begin()) ==  4);
	VERIFY((it - v.end())   == -1);

	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	VERIFY((it <  v.end()) == true);
	VERIFY((it <= v.end()) == true);
	VERIFY((it >  v.end()) == false);
	VERIFY((it >= v.end()) == false);

	++it;

	VERIFY((it == v.end()) == true);
	VERIFY((it != v.end()) == false);
	VERIFY((it <  v.end()) == false);
	VERIFY((it <= v.end()) == true);
	VERIFY((it >  v.end()) == false);
	VERIFY((it >= v.end()) == true);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	int a[2] ={};
	test_random_access_range<int> r(a);
	auto v = bksge::ranges::views::iota(r.begin(), r.end());
	VERIFY(v.size() == 2);

	auto it = v.begin();
	VERIFY((it - v.begin()) ==  0);
	VERIFY((it - v.end())   == -2);
	VERIFY((v.begin() - it) ==  0);
	VERIFY((v.end()   - it) ==  2);

	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	++it;
	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	it++;
	VERIFY((it == v.end()) == true);
	VERIFY((it != v.end()) == false);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test05()
{
	int a[2] ={};
	test_input_range<int> r(a);
	auto v = bksge::ranges::views::iota(r.begin(), r.end());

	auto it = v.begin();
	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	++it;
	VERIFY((it == v.end()) == false);
	VERIFY((it != v.end()) == true);
	it++;
	VERIFY((it == v.end()) == true);
	VERIFY((it != v.end()) == false);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	auto v = bksge::ranges::iota_view<unsigned int, unsigned int>{3u, 5u};
	VERIFY(v.size() == 2);

	auto it = v.begin();
	VERIFY((it - v.begin()) ==  0);

	VERIFY(*it == 3u);
	it += 2;
	VERIFY(*it == 5u);
	it -= 1;
	VERIFY(*it == 4u);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, IotaViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
}

}	// namespace iota_view_test

}	// namespace bksge_ranges_test
