/**
 *	@file	unit_test_fnd_span_assign.cpp
 *
 *	@brief	span& operator=(const span& other) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace assign_test
{

template <typename T>
BKSGE_CXX14_CONSTEXPR bool do_assign(T lhs, T rhs)
{
	BKSGE_ASSERT_NOEXCEPT(bksge::declval<T&>() = rhs);
	lhs = rhs;
	return
		lhs.data() == rhs.data() &&
		lhs.size() == rhs.size();
}

GTEST_TEST(SpanTest, AssignTest)
{
	static constexpr int carr1[] = {1, 2, 3, 4};
	static constexpr int carr2[] = {3, 4, 5};
	static constexpr int carr3[] = {7, 8};
	                 int   arr[] = {5, 6, 7, 9};
	std::string strs[] = {"ABC", "DEF", "GHI"};

	//  constexpr dynamically sized assignment
	{
		//  On systems where 'ptrdiff_t' is a synonym for 'int',
		//  the call span(ptr, 0) selects the (pointer, index_type) constructor.
		//  On systems where 'ptrdiff_t' is NOT a synonym for 'int',
		//  it is ambiguous, because of 0 also being convertible to a null pointer
		//  and so the compiler can't choose between:
		//      span(pointer, index_type)
		//  and span(pointer, pointer)
		//  We cast zero to std::ptrdiff_t to remove that ambiguity.
		//  Example:
		//      On darwin x86_64, ptrdiff_t is the same as long int.
		//      On darwin i386, ptrdiff_t is the same as int.
		constexpr bksge::span<const int> spans[] =
		{
			{},
			{carr1, static_cast<std::size_t>(0)},
			{carr1, 1U},
			{carr1, 2U},
			{carr1, 3U},
			{carr1, 4U},
			{carr2, static_cast<std::size_t>(0)},
			{carr2, 1U},
			{carr2, 2U},
			{carr2, 3U},
			{carr3, static_cast<std::size_t>(0)},
			{carr3, 1U},
			{carr3, 2U},
		};

		static_assert(bksge::size(spans) == 13, "");

		//  No for loops in constexpr land :-(
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[0]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[1]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[2]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[5]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[6]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[7]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[1]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[2]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[5]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[6]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[7]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[2]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[5]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[6]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[7]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[5]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[6]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[7]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[5]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[6]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[7]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[6], spans[6]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[6], spans[7]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[6], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[6], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[6], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[6], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[6], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[7], spans[7]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[7], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[7], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[7], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[7], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[7], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[8], spans[8]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[8], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[8], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[8], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[8], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[9], spans[9]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[9], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[9], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[9], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[10], spans[10]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[10], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[10], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[11], spans[11]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[11], spans[12]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[12], spans[12]));

//      for (std::size_t i = 0; i < bksge::size(spans); ++i)
//          for (std::size_t j = i; j < bksge::size(spans); ++j)
//              static_assert(do_assign(spans[i], spans[j]), "");
	}

	//  constexpr statically sized assignment
	{
		BKSGE_CXX14_CONSTEXPR bksge::span<const int, 2> spans[] =
		{
			{carr1, 2},
			{carr1 + 1, 2},
			{carr1 + 2, 2},
			{carr2, 2},
			{carr2 + 1, 2},
			{carr3, 2},
		};

		static_assert(bksge::size(spans) == 6, "");

		//  No for loops in constexpr land :-(
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[0]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[1]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[2]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[0], spans[5]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[1]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[2]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[1], spans[5]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[2]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[2], spans[5]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[3]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[3], spans[5]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[4]));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[4], spans[5]));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_assign(spans[5], spans[5]));

//      for (std::size_t i = 0; i < bksge::size(spans); ++i)
//          for (std::size_t j = i; j < bksge::size(spans); ++j)
//              static_assert(do_assign(spans[i], spans[j]), "");
	}


	//  dynamically sized assignment
	{
		bksge::span<int> spans[] =
		{
			{},
			{arr, arr + 1},
			{arr, arr + 2},
			{arr, arr + 3},
			{arr + 1, arr + 3}, // same size as s2
		};

		for (std::size_t i = 0; i < bksge::size(spans); ++i)
		{
			for (std::size_t j = i; j < bksge::size(spans); ++j)
			{
				EXPECT_TRUE((do_assign(spans[i], spans[j])));
			}
		}
	}

	//  statically sized assignment
	{
		bksge::span<int, 2> spans[] =
		{
			{arr,     arr + 2},
			{arr + 1, arr + 3},
			{arr + 2, arr + 4},
		};

		for (std::size_t i = 0; i < bksge::size(spans); ++i)
		{
			for (std::size_t j = i; j < bksge::size(spans); ++j)
			{
				EXPECT_TRUE((do_assign(spans[i], spans[j])));
			}
		}
	}

	//  dynamically sized assignment
	{
		bksge::span<std::string> spans[] =
		{
			{strs, strs},
			{strs, strs + 1},
			{strs, strs + 2},
			{strs, strs + 3},
			{strs + 1, strs + 1},
			{strs + 1, strs + 2},
			{strs + 1, strs + 3},
			{strs + 2, strs + 2},
			{strs + 2, strs + 3},
			{strs + 3, strs + 3},
		};

		for (std::size_t i = 0; i < bksge::size(spans); ++i)
		{
			for (std::size_t j = i; j < bksge::size(spans); ++j)
			{
				EXPECT_TRUE((do_assign(spans[i], spans[j])));
			}
		}
	}

	{
		bksge::span<std::string, 1> spans[] =
		{
			{strs,     strs + 1},
			{strs + 1, strs + 2},
			{strs + 2, strs + 3},
		};

		for (std::size_t i = 0; i < bksge::size(spans); ++i)
		{
			for (std::size_t j = i; j < bksge::size(spans); ++j)
			{
				EXPECT_TRUE((do_assign(spans[i], spans[j])));
			}
		}
	}
}

}	// namespace assign_test

}	// namespace bksge_span_test
