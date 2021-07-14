/**
 *	@file	unit_test_fnd_array_to_array.cpp
 *
 *	@brief	to_array のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/array/to_array.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct CopyOnly
{
	BKSGE_CONSTEXPR CopyOnly(int i = 0) : m_value(i) {}
	BKSGE_CONSTEXPR CopyOnly(CopyOnly const& rhs) : m_value(rhs.m_value) {}

	CopyOnly(CopyOnly&& rhs) = delete;
	CopyOnly& operator=(CopyOnly&& rhs) = delete;

	int m_value;
};

struct MoveOnly
{
	BKSGE_CONSTEXPR MoveOnly(int i = 0) : m_value(i) {}
	BKSGE_CONSTEXPR MoveOnly(MoveOnly&& rhs) : m_value(rhs.m_value) {}

	MoveOnly(MoveOnly const& rhs) = delete;
	MoveOnly& operator=(MoveOnly const& rhs) = delete;

	int m_value;
};

inline BKSGE_CXX14_CONSTEXPR bool test_to_array()
{
	{
		int const x[] = {1,2,3};
		auto y = bksge::to_array(x);
		static_assert(bksge::is_same<decltype(y), bksge::array<int, 3>>::value, "");
		VERIFY(y[0] == 1);
		VERIFY(y[1] == 2);
		VERIFY(y[2] == 3);
	}
	{
		int x[] = {1,2,3,4};
		auto y = bksge::to_array(bksge::move(x));
		static_assert(bksge::is_same<decltype(y), bksge::array<int, 4>>::value, "");
		VERIFY(y[0] == 1);
		VERIFY(y[1] == 2);
		VERIFY(y[2] == 3);
		VERIFY(y[3] == 4);
	}
	{
		auto a = bksge::to_array("abcde");
		static_assert(bksge::is_same<decltype(a), bksge::array<char, 6>>::value, "");
		VERIFY(a[0] == 'a');
		VERIFY(a[1] == 'b');
		VERIFY(a[2] == 'c');
		VERIFY(a[3] == 'd');
		VERIFY(a[4] == 'e');
		VERIFY(a[5] == '\0');
	}
	{
		CopyOnly const x[] = {{1},{2},{3}};
		auto y = bksge::to_array(x);
		static_assert(bksge::is_same<decltype(y), bksge::array<CopyOnly, 3>>::value, "");
		VERIFY(y[0].m_value == 1);
		VERIFY(y[1].m_value == 2);
		VERIFY(y[2].m_value == 3);
	}
#if !(defined(BKSGE_MSVC) && (BKSGE_MSVC < 1920))
	{
		MoveOnly x[] = {{1},{2},{3}};
		auto y = bksge::to_array(bksge::move(x));
		static_assert(bksge::is_same<decltype(y), bksge::array<MoveOnly, 3>>::value, "");
		VERIFY(y[0].m_value == 1);
		VERIFY(y[1].m_value == 2);
		VERIFY(y[2].m_value == 3);
	}
#endif
	return true;
}

GTEST_TEST(ArrayTest, ToArrayTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_to_array()));
}

#undef VERIFY

}	// namespace bksge_array_test
