/**
 *	@file	unit_test_fnd_algorithm_ranges_radix_sort.cpp
 *
 *	@brief	ranges::radix_sort のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/radix_sort.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/algorithm/ranges/is_sorted.hpp>
//#include <bksge/fnd/algorithm/ranges/sort.hpp>
#include <bksge/fnd/random.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
//#include <chrono>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_radix_sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		unsigned char x[] = { 3,1,4,1,5,9,2,6 };
		auto res = ranges::radix_sort(x, x + 8);
		VERIFY(res == x + 8);
		unsigned char const y[] = { 1,1,2,3,4,5,6,9 };
		VERIFY(ranges::equal(x, y));
	}
	{
		unsigned short x[] = { 5,1,3,5,5,2,5,1,5,1, };
		auto res = ranges::radix_sort(x);
		VERIFY(res == x + 10);
		unsigned short const y[] = { 1,1,1,2,3,5,5,5,5,5, };
		VERIFY(ranges::equal(x, y));
	}
	{
		unsigned int x[] =
		{
			96580, 71212, 93844,  8683, 51070, 63008, 30816, 56650,
			 2872,  1799, 48614, 74299, 94453, 65547, 17404, 91217,
		};
		test_range<unsigned int, random_access_iterator_wrapper> r(x);
		auto res = ranges::radix_sort(r);
		VERIFY(res == r.end());
		unsigned int const y[] =
		{
			 1799,  2872,  8683, 17404, 30816, 48614, 51070, 56650,
			63008, 65547, 71212, 74299, 91217, 93844, 94453, 96580,
		};
		VERIFY(ranges::equal(x, y));
	}
	{
		unsigned long long x[] =
		{
			76813, 2398,37548,37796,17013,70225,67808, 6876, 1838,62903,
			91810,95592,64844,67240,42143,95681,69405,39267,80218,10788,
		};
		auto res = ranges::radix_sort(x);
		VERIFY(res == x + 20);
		unsigned long long const y[] =
		{
			 1838, 2398, 6876,10788,17013,37548,37796,39267,42143,62903,
			64844,67240,67808,69405,70225,76813,80218,91810,95592,95681,
		};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	unsigned int	index;
	bksge::string	name;

	bool operator==(X const& rhs) const
	{
		return index == rhs.index &&
			name == rhs.name;
	}
	bool operator!=(X const& rhs) const
	{
		return !(*this == rhs);
	}
};

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		X x[] =
		{
			{3, "Alice"},
			{4, "Bob"},
			{2, "Carol"},
			{1, "Dave"},
			{5, "Eve"},
		};
		auto res = ranges::radix_sort(x, &X::index);
		VERIFY(res == x + 5);
		X const y[] =
		{
			{1, "Dave"},
			{2, "Carol"},
			{3, "Alice"},
			{4, "Bob"},
			{5, "Eve"},
		};
		VERIFY(ranges::equal(x, y));
	}
	{
		X x[] =
		{
			{200, "Alice"},
			{100, "Bob"},
			{200, "Carol"},
			{100, "Dave"},
			{100, "Eve"},
		};
		test_range<X, random_access_iterator_wrapper> r(x);
		auto res = ranges::radix_sort(r, &X::index);
		VERIFY(res == r.end());
		X const y[] =
		{
			{100, "Bob"},
			{100, "Dave"},
			{100, "Eve"},
			{200, "Alice"},
			{200, "Carol"},
		};
		VERIFY(ranges::equal(x, y));
	}
	{
		bksge::mt19937 rng;
		unsigned int const min = 0;
		unsigned int const max = 0xFFFFFFFF;
		bksge::uniform_int_distribution<unsigned int> dist(min, max);
		bksge::size_t const n = 100;
		bksge::vector<unsigned int> v(n);
		for (auto& x : v)
		{
			x = dist(rng);
		}

		ranges::radix_sort(v);
		VERIFY(ranges::is_sorted(v));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RangesRadixSortTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());

#if 0
	namespace ranges = bksge::ranges;
	{
		bksge::size_t const n_tbl[] =
		{
			10,
			100,
			1000,
			10000,
			100000,
			1000000,
			10000000,
			100000000,
			//1000000000,
		};

		unsigned int const max_tbl[] =
		{
			10,
			100,
			10000,
			1000000,
			//100000000,
		};

		enum SortAlgo
		{
			StdSort,
			RadixSort,
		};

		SortAlgo const algo_tbl[] = {StdSort, RadixSort};

		bksge::mt19937 rng;

		for (auto algo : algo_tbl)
		{
			std::cout << ((algo == StdSort) ? "sort" : "radix_sort") << ":" << std::endl;
			for (auto max : max_tbl)
			{
				unsigned int const min = 0;
				std::cout << "distribution(" << min << ", " << max << "):" << std::endl;
				for (auto n : n_tbl)
				{
					bksge::uniform_int_distribution<unsigned int> dist(min, max);
					bksge::vector<unsigned int> v(n);
					for (auto& x : v)
					{
						x = dist(rng);
					}

					{
						auto t1 = std::chrono::high_resolution_clock::now();

						if (algo == StdSort)
						{
							std::ranges::sort(v);
						}
						else
						{
							ranges::radix_sort(v);
						}

						auto t2 = std::chrono::high_resolution_clock::now();
						auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
						std::cout << std::right << std::setw(10);
						std::cout << n << ": " << elapsed_time.count() << " us"<< std::endl;
					}

					EXPECT_TRUE(ranges::is_sorted(v));
				}
			}

			std::cout << std::endl;
		}
	}
#endif
}

}	// namespace ranges_radix_sort_test

}	// namespace bksge_algorithm_test
