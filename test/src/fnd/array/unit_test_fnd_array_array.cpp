/**
 *	@file	unit_test_fnd_array_array.cpp
 *
 *	@brief	array のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/array/array.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test_ctor_default()
{
	{
		bksge::array<int, 0> a{};
		VERIFY(a.size()     == 0);
		VERIFY(a.max_size() == 0);
		VERIFY(a.empty()    == true);
	}
	{
		bksge::array<int, 2> a{};
		VERIFY(a.size()     == 2);
		VERIFY(a.max_size() == 2);
		VERIFY(a.empty()    == false);
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test_ctor_aggregate()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		VERIFY(a.size()     == 5);
		VERIFY(a.max_size() == 5);
		VERIFY(a.empty()    == false);
	}
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3 } };
		VERIFY(a.size()     == 5);
		VERIFY(a.max_size() == 5);
		VERIFY(a.empty()    == false);
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test_ctor_deduction()
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		bksge::array a = {1,2,3};
		static_assert(bksge::is_same<decltype(a), bksge::array<int, 3>>::value, "");
		VERIFY(a.size()     == 3);
		VERIFY(a.max_size() == 3);
		VERIFY(a.empty()    == false);
	}
	{
		int x = 2;
		int const y = 3;
		bksge::array a = {1,x,y};
		static_assert(bksge::is_same<decltype(a), bksge::array<int, 3>>::value, "");
		VERIFY(a.size()     == 3);
		VERIFY(a.max_size() == 3);
		VERIFY(a.empty()    == false);
	}
	{
		bksge::array a = {'a', 'b', 'c', 'd', 'e'};
		static_assert(bksge::is_same<decltype(a), bksge::array<char, 5>>::value, "");
		VERIFY(a.size()     == 5);
		VERIFY(a.max_size() == 5);
		VERIFY(a.empty()    == false);
	}
	{
		bksge::array a = {1,2,3,4};
		bksge::array b = a;
		static_assert(bksge::is_same<decltype(b), bksge::array<int, 4>>::value, "");
		VERIFY(b.size()     == 4);
		VERIFY(b.max_size() == 4);
		VERIFY(b.empty()    == false);

		bksge::array c = bksge::move(a);
		static_assert(bksge::is_same<decltype(c), bksge::array<int, 4>>::value, "");
		VERIFY(c.size()     == 4);
		VERIFY(c.max_size() == 4);
		VERIFY(c.empty()    == false);
	}
#endif
	return true;
}

GTEST_TEST(ArrayTest, CtorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_default()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_aggregate()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_deduction()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_size()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		auto s = a.size();
		VERIFY(s == 5);
	}
	{
		bksge::array<int, 0> a{};
		auto s = a.size();
		VERIFY(s == 0);
	}
	return true;
}

GTEST_TEST(ArrayTest, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_size()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_max_size()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		auto s = a.max_size();
		VERIFY(s == 5);
	}
	{
		bksge::array<int, 0> a{};
		auto s = a.max_size();
		VERIFY(s == 0);
	}
	return true;
}

GTEST_TEST(ArrayTest, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_max_size()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_empty()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		auto b = a.empty();
		VERIFY(b == false);
	}
	{
		bksge::array<int, 0> a{};
		auto b = a.empty();
		VERIFY(b == true);
	}
	return true;
}

GTEST_TEST(ArrayTest, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_empty()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_front()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		int& r = a.front();
		VERIFY(r == 0);
	}
	{
		bksge::array<int, 5> const a = { { 0, 1, 2, 3, 4 } };
		int const& r = a.front();
		VERIFY(r == 0);
	}
	return true;
}

GTEST_TEST(ArrayTest, FrontTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_front()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_back()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		int& r = a.back();
		VERIFY(r == 4);
	}
	{
		bksge::array<int, 5> const a = { { 0, 1, 2, 3, 4 } };
		int const& r = a.back();
		VERIFY(r == 4);
	}
	return true;
}

GTEST_TEST(ArrayTest, BackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_back()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_at()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		int& r = a.at(1);
		VERIFY(r == 1);
	}
	{
		bksge::array<int, 5> const a = { { 0, 1, 2, 3, 4 } };
		int const& r = a.at(2);
		VERIFY(r == 2);
	}
	return true;
}

GTEST_TEST(ArrayTest, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_at()));

	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		EXPECT_THROW((void)a.at(5), bksge::out_of_range);
	}
	{
		bksge::array<int, 5> const a = { { 0, 1, 2, 3, 4 } };
		EXPECT_THROW((void)a.at(5), bksge::out_of_range);
	}
}

inline BKSGE_CXX14_CONSTEXPR bool test_brackets()
{
	{
		bksge::array<int, 5> a = { { 0, 1, 2, 3, 4 } };
		int& r = a[2];
		VERIFY(r == 2);
	}
	{
		bksge::array<int, 5> const a = { { 0, 1, 2, 3, 4 } };
		int const& r = a[3];
		VERIFY(r == 3);
	}
	return true;
}

GTEST_TEST(ArrayTest, BracketsTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_brackets()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_begin_end()
{
	{
		bksge::array<int, 3> a = { { 1, 2, 3 } };
		auto it = a.begin();
		VERIFY(*it == 1);
		VERIFY(it != a.end());
		VERIFY(*++it == 2);
		VERIFY(it != a.end());
		VERIFY(*it++ == 2);
		VERIFY(it != a.end());
		VERIFY(*it++ == 3);
		VERIFY(it == a.end());
	}
	{
		bksge::array<int, 3> const a = { { 1, 2, 3 } };
		auto it = a.begin();
		VERIFY(*it == 1);
		VERIFY(it != a.end());
		VERIFY(*++it == 2);
		VERIFY(it != a.end());
		VERIFY(*it++ == 2);
		VERIFY(it != a.end());
		VERIFY(*it++ == 3);
		VERIFY(it == a.end());
	}
	{
		bksge::array<int, 3> a = { { 1, 2, 3 } };
		auto it = a.cbegin();
		VERIFY(*it == 1);
		VERIFY(it != a.cend());
		VERIFY(*++it == 2);
		VERIFY(it != a.cend());
		VERIFY(*it++ == 2);
		VERIFY(it != a.cend());
		VERIFY(*it++ == 3);
		VERIFY(it == a.cend());
	}
	return true;
}

GTEST_TEST(ArrayTest, BeginEndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_begin_end()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_rbegin_rend()
{
	{
		bksge::array<int, 3> a = { { 1, 2, 3 } };
		auto it = a.rbegin();
		VERIFY(*it == 3);
		VERIFY(it != a.rend());
		VERIFY(*++it == 2);
		VERIFY(it != a.rend());
		VERIFY(*it++ == 2);
		VERIFY(it != a.rend());
		VERIFY(*it++ == 1);
		VERIFY(it == a.rend());
	}
	{
		bksge::array<int, 3> const a = { { 1, 2, 3 } };
		auto it = a.rbegin();
		VERIFY(*it == 3);
		VERIFY(it != a.rend());
		VERIFY(*++it == 2);
		VERIFY(it != a.rend());
		VERIFY(*it++ == 2);
		VERIFY(it != a.rend());
		VERIFY(*it++ == 1);
		VERIFY(it == a.rend());
	}
	{
		bksge::array<int, 3> a = { { 1, 2, 3 } };
		auto it = a.crbegin();
		VERIFY(*it == 3);
		VERIFY(it != a.crend());
		VERIFY(*++it == 2);
		VERIFY(it != a.crend());
		VERIFY(*it++ == 2);
		VERIFY(it != a.crend());
		VERIFY(*it++ == 1);
		VERIFY(it == a.crend());
	}
	return true;
}

GTEST_TEST(ArrayTest, RBeginREndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_rbegin_rend()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_fill()
{
	{
		bksge::array<int, 3> a = { { 1, 2, 3 } };
		a.fill(42);
		VERIFY(a[0] == 42);
		VERIFY(a[1] == 42);
		VERIFY(a[2] == 42);
	}
	return true;
}

GTEST_TEST(ArrayTest, FillTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_fill()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_swap()
{
	{
		bksge::array<int, 3> a1 = { { 1, 2, 3 } };
		bksge::array<int, 3> a2 = { { 4, 5, 6 } };

		a1.swap(a2);

		VERIFY(a1[0] == 4);
		VERIFY(a1[1] == 5);
		VERIFY(a1[2] == 6);
		VERIFY(a2[0] == 1);
		VERIFY(a2[1] == 2);
		VERIFY(a2[2] == 3);

		bksge::swap(a1, a2);

		VERIFY(a1[0] == 1);
		VERIFY(a1[1] == 2);
		VERIFY(a1[2] == 3);
		VERIFY(a2[0] == 4);
		VERIFY(a2[1] == 5);
		VERIFY(a2[2] == 6);
	}
	return true;
}

GTEST_TEST(ArrayTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_swap()));
}

inline BKSGE_CXX14_CONSTEXPR bool test_compare()
{
	{
		bksge::array<int, 3> a1 = { { 1, 2, 3 } };
		bksge::array<int, 3> a2 = { { 1, 2, 3 } };
		bksge::array<int, 3> a3 = { { 1, 2, 4 } };
		bksge::array<int, 3> a4 = { { 1, 2, 0 } };
		bksge::array<int, 3> a5 = { { 2, 2, 3 } };
		bksge::array<int, 3> a6 = { { 0, 2, 3 } };

		VERIFY((a1 == a1) == true);
		VERIFY((a1 == a2) == true);
		VERIFY((a1 == a3) == false);
		VERIFY((a1 == a4) == false);
		VERIFY((a1 == a5) == false);
		VERIFY((a1 == a6) == false);

		VERIFY((a1 != a1) == false);
		VERIFY((a1 != a2) == false);
		VERIFY((a1 != a3) == true);
		VERIFY((a1 != a4) == true);
		VERIFY((a1 != a5) == true);
		VERIFY((a1 != a6) == true);

		VERIFY((a1 <  a1) == false);
		VERIFY((a1 <  a2) == false);
		VERIFY((a1 <  a3) == true);
		VERIFY((a1 <  a4) == false);
		VERIFY((a1 <  a5) == true);
		VERIFY((a1 <  a6) == false);

		VERIFY((a1 >  a1) == false);
		VERIFY((a1 >  a2) == false);
		VERIFY((a1 >  a3) == false);
		VERIFY((a1 >  a4) == true);
		VERIFY((a1 >  a5) == false);
		VERIFY((a1 >  a6) == true);

		VERIFY((a1 <= a1) == true);
		VERIFY((a1 <= a2) == true);
		VERIFY((a1 <= a3) == true);
		VERIFY((a1 <= a4) == false);
		VERIFY((a1 <= a5) == true);
		VERIFY((a1 <= a6) == false);

		VERIFY((a1 >= a1) == true);
		VERIFY((a1 >= a2) == true);
		VERIFY((a1 >= a3) == false);
		VERIFY((a1 >= a4) == true);
		VERIFY((a1 >= a5) == false);
		VERIFY((a1 >= a6) == true);
	}
	return true;
}

GTEST_TEST(ArrayTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_compare()));
}

#undef VERIFY

}	// namespace bksge_array_test
