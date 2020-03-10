/**
 *	@file	unit_test_fnd_vector_vector.cpp
 *
 *	@brief	vectorのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/pair.hpp>
//#include <bksge/fnd/string.hpp>
#include <string>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
//#include <bksge/fnd/iterator/istream_iterator.hpp>
#include <iterator>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/memory/allocator.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
//#include <bksge/fnd/sstream/stringstream.hpp>
#include <sstream>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <gtest/gtest.h>

namespace bksge_vector_test
{

#if 0
template <typename T>
struct NonPropagateAllocator
	: public bksge::allocator<T>
{
	using propagate_on_container_move_assignment = bksge::false_type;
};
#endif

GTEST_TEST(VectorTest, ConstructTest)
{
	// (1)
	{
		bksge::vector<int> v;
		EXPECT_EQ(0u, v.size());
	}
	{
		bksge::vector<int> v {};
		EXPECT_EQ(0u, v.size());
	}
	{
		bksge::vector<int> v{ bksge::allocator<int>() };
		EXPECT_EQ(0u, v.size());
	}
	// (2)
	{
		bksge::vector<int> v(5, 42);
		EXPECT_EQ(5u, v.size());
		EXPECT_EQ(42, v[0]);
		EXPECT_EQ(42, v[4]);
	}
	{
		bksge::vector<int> v(5, 42, bksge::allocator<int>());
		EXPECT_EQ(5u, v.size());
		EXPECT_EQ(42, v[0]);
		EXPECT_EQ(42, v[4]);
	}
	// (3)
	{
		bksge::vector<int> v(10);
		EXPECT_EQ(10u, v.size());
		EXPECT_EQ(0, v[0]);
		EXPECT_EQ(0, v[9]);
	}
	{
		bksge::allocator<int> a;
		bksge::vector<int> v(10, a);
		EXPECT_EQ(10u, v.size());
		EXPECT_EQ(0, v[0]);
		EXPECT_EQ(0, v[9]);
	}
	// (4)
	{
		int a[] { 1, 2, 3 };
		bksge::vector<int> v(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
	}
	{
		int a[] { 1, 2, 3, 4 };
		bksge::vector<int> v(bksge::begin(a), bksge::end(a), bksge::allocator<int>());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(4, v[3]);
	}
	{
		std::stringstream ss("1 2 3");
		std::istream_iterator<int> ii_first(ss);
		std::istream_iterator<int> ii_last;
		bksge::vector<int> v(ii_first, ii_last);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
	}
	{
		std::stringstream ss("1 2 3");
		std::istream_iterator<int> ii_first(ss);
		std::istream_iterator<int> ii_last;
		bksge::vector<int> v(ii_first, ii_last, bksge::allocator<int>());
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
	}
	// (5)
	{
		const bksge::vector<int> v1(3, 10);
		const bksge::vector<int> v2(v1);
		EXPECT_EQ(3u, v2.size());
		EXPECT_EQ(10, v2[0]);
		EXPECT_EQ(10, v2[2]);
	}
	{
		const bksge::vector<int> v1(3, 10);
		const bksge::vector<int> v2(v1, bksge::allocator<int>());
		EXPECT_EQ(3u, v2.size());
		EXPECT_EQ(10, v2[0]);
		EXPECT_EQ(10, v2[2]);
	}
	// (6)
	{
		const bksge::vector<int> v1(3, 10);
		const bksge::vector<int> v2(bksge::move(v1));
		EXPECT_EQ(3u, v2.size());
		EXPECT_EQ(10, v2[0]);
		EXPECT_EQ(10, v2[2]);
	}
	// (7)
	{
		bksge::vector<int> v1(3, 10);
		const bksge::vector<int> v2(bksge::move(v1), bksge::allocator<int>());
		EXPECT_EQ(3u, v2.size());
		EXPECT_EQ(10, v2[0]);
		EXPECT_EQ(10, v2[2]);
	}
	// (8)
	{
		const bksge::vector<int> v { 3, 4, 5, 6, 7 };
		EXPECT_EQ(5u, v.size());
		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(5, v[2]);
		EXPECT_EQ(6, v[3]);
		EXPECT_EQ(7, v[4]);
	}
	{
		const bksge::vector<int> v({ 3, 4, 5, 6, 7 }, bksge::allocator<int>());
		EXPECT_EQ(5u, v.size());
		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(5, v[2]);
		EXPECT_EQ(6, v[3]);
		EXPECT_EQ(7, v[4]);
	}
}

GTEST_TEST(VectorTest, OperatorAssignTest)
{
	// (1)
	{
		const bksge::vector<int> v1 { 1, 2, 3 };
		bksge::vector<int> v2;
		EXPECT_EQ(0u, v2.size());

		v2 = v1;

		EXPECT_EQ(3u, v2.size());
		EXPECT_EQ(1, v2[0]);
		EXPECT_EQ(2, v2[1]);
		EXPECT_EQ(3, v2[2]);
	}
	// (2)
	{
		bksge::vector<int> v1 { 1, 2, 3 };
		bksge::vector<int> v2;
		EXPECT_EQ(0u, v2.size());

		v2 = bksge::move(v1);

		EXPECT_EQ(3u, v2.size());
		EXPECT_EQ(1, v2[0]);
		EXPECT_EQ(2, v2[1]);
		EXPECT_EQ(3, v2[2]);
	}
#if 0
	{
		bksge::vector<int, NonPropagateAllocator<int>> v1 { 1, 2, 3 };
		bksge::vector<int, NonPropagateAllocator<int>> v2;
		EXPECT_EQ(0u, v2.size());

		v2 = bksge::move(v1);

		EXPECT_EQ(3u, v2.size());
		EXPECT_EQ(1, v2[0]);
		EXPECT_EQ(2, v2[1]);
		EXPECT_EQ(3, v2[2]);
	}
#endif
	// (3)
	{
		bksge::vector<int> v;
		EXPECT_EQ(0u, v.size());

		v = { 3, 4, 5, 6 };

		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(5, v[2]);
		EXPECT_EQ(6, v[3]);
	}
}

GTEST_TEST(VectorTest, BeginEndTest)
{
	{
		bksge::vector<int> v { 1, 2, 3 };
		auto it = v.begin();
		EXPECT_FALSE(it == v.end());
		EXPECT_TRUE (it != v.end());
		EXPECT_EQ(1, *it);
		*it = 4;
		++it;
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_TRUE (it == v.end());
		EXPECT_FALSE(it != v.end());
		EXPECT_EQ(4, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
	}
	{
		const bksge::vector<int> v { 1, 2, 3 };
		auto it = v.begin();
		EXPECT_FALSE(it == v.end());
		EXPECT_TRUE (it != v.end());
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_TRUE (it == v.end());
		EXPECT_FALSE(it != v.end());
	}
}

GTEST_TEST(VectorTest, CBeginCEndTest)
{
	{
		bksge::vector<int> v { 1, 2, 3 };
		auto it = v.cbegin();
		EXPECT_FALSE(it == v.cend());
		EXPECT_TRUE (it != v.cend());
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_TRUE (it == v.cend());
		EXPECT_FALSE(it != v.cend());
	}
}

GTEST_TEST(VectorTest, RBeginREndTest)
{
	{
		bksge::vector<int> v { 1, 2, 3 };
		auto it = v.rbegin();
		EXPECT_FALSE(it == v.rend());
		EXPECT_TRUE (it != v.rend());
		EXPECT_EQ(3, *it);
		*it = 4;
		++it;
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_TRUE (it == v.rend());
		EXPECT_FALSE(it != v.rend());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(4, v[2]);
	}
	{
		const bksge::vector<int> v { 1, 2, 3 };
		auto it = v.rbegin();
		EXPECT_FALSE(it == v.rend());
		EXPECT_TRUE (it != v.rend());
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_TRUE (it == v.rend());
		EXPECT_FALSE(it != v.rend());
	}
}

GTEST_TEST(VectorTest, CRBeginCREndTest)
{
	{
		bksge::vector<int> v { 1, 2, 3 };
		auto it = v.crbegin();
		EXPECT_FALSE(it == v.crend());
		EXPECT_TRUE (it != v.crend());
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_TRUE (it == v.crend());
		EXPECT_FALSE(it != v.crend());
	}
}

GTEST_TEST(VectorTest, SizeTest)
{
	{
		const bksge::vector<int> v;
		EXPECT_EQ(0u, v.size());
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(3u, v.size());
	}
	{
		const bksge::vector<int> v { 3, 1, 4, 1, 5 };
		EXPECT_EQ(5u, v.size());
	}
}

GTEST_TEST(VectorTest, MaxSizeTest)
{
	{
		const bksge::vector<int> v;
		EXPECT_LE(1u, v.max_size());
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_LE(1u, v.max_size());
	}
	{
		const bksge::vector<int> v { 3, 1, 4, 1, 5 };
		EXPECT_LE(1u, v.max_size());
	}
}

GTEST_TEST(VectorTest, ResizeTest)
{
	bksge::vector<int> v;
	EXPECT_EQ(0u, v.size());

	v.resize(3);
	EXPECT_EQ(3u, v.size());
	EXPECT_EQ(0, v[0]);
	EXPECT_EQ(0, v[1]);
	EXPECT_EQ(0, v[2]);

	v.resize(5, 42);
	EXPECT_EQ(5u, v.size());
	EXPECT_EQ(0, v[0]);
	EXPECT_EQ(0, v[1]);
	EXPECT_EQ(0, v[2]);
	EXPECT_EQ(42, v[3]);
	EXPECT_EQ(42, v[4]);

	v.resize(2);
	EXPECT_EQ(2u, v.size());
	EXPECT_EQ(0, v[0]);
	EXPECT_EQ(0, v[1]);
}

GTEST_TEST(VectorTest, CapacityTest)
{
	{
		const bksge::vector<int> v;
		EXPECT_LE(0u, v.capacity());
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_LE(0u, v.capacity());
	}
	{
		const bksge::vector<int> v { 3, 1, 4, 1, 5 };
		EXPECT_LE(0u, v.capacity());
	}
}

GTEST_TEST(VectorTest, EmptyTest)
{
	{
		const bksge::vector<int> v;
		EXPECT_TRUE(v.empty());
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_FALSE(v.empty());
	}
}

GTEST_TEST(VectorTest, ReserveTest)
{
	{
		bksge::vector<int> v;
		v.reserve(5);
		EXPECT_LE(5u, v.capacity());
	}
}

GTEST_TEST(VectorTest, ShrinkToFitTest)
{
	{
		bksge::vector<int> v;
		v.reserve(5);
		EXPECT_LE(5u, v.capacity());

		v = { 1, 2, 3 };
		v.shrink_to_fit();
		EXPECT_LE(3u, v.capacity());
	}
}

GTEST_TEST(VectorTest, OperatorBracketTest)
{
	{
		bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(1, v[1]);
		EXPECT_EQ(4, v[2]);

		v[1] = 6;

		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(6, v[1]);
		EXPECT_EQ(4, v[2]);
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(1, v[1]);
		EXPECT_EQ(4, v[2]);
	}
}

GTEST_TEST(VectorTest, AtTest)
{
	{
		bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(3, v.at(0));
		EXPECT_EQ(1, v.at(1));
		EXPECT_EQ(4, v.at(2));
		EXPECT_THROW(v.at(3) = 0, bksge::out_of_range);

		v.at(1) = 6;

		EXPECT_EQ(3, v.at(0));
		EXPECT_EQ(6, v.at(1));
		EXPECT_EQ(4, v.at(2));
		int t = 0;
		EXPECT_THROW(t = v.at(3), bksge::out_of_range);
		(void)t;
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(3, v.at(0));
		EXPECT_EQ(1, v.at(1));
		EXPECT_EQ(4, v.at(2));
		int t = 0;
		EXPECT_THROW(t = v.at(3), bksge::out_of_range);
		(void)t;
	}
}

GTEST_TEST(VectorTest, DataTest)
{
	{
		bksge::vector<int> v { 3, 1, 4 };
		int* p = v.data();
		EXPECT_EQ(3, p[0]);
		EXPECT_EQ(1, p[1]);
		EXPECT_EQ(4, p[2]);

		p[1] = 6;

		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(6, v[1]);
		EXPECT_EQ(4, v[2]);
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		const int* p = v.data();
		EXPECT_EQ(3, p[0]);
		EXPECT_EQ(1, p[1]);
		EXPECT_EQ(4, p[2]);
	}
}

GTEST_TEST(VectorTest, FrontTest)
{
	{
		bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(3, v.front());

		v.front() = 6;

		EXPECT_EQ(6, v[0]);
		EXPECT_EQ(1, v[1]);
		EXPECT_EQ(4, v[2]);
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(3, v.front());
	}
}

GTEST_TEST(VectorTest, BackTest)
{
	{
		bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(4, v.back());

		v.back() = 6;

		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(1, v[1]);
		EXPECT_EQ(6, v[2]);
	}
	{
		const bksge::vector<int> v { 3, 1, 4 };
		EXPECT_EQ(4, v.back());
	}
}

GTEST_TEST(VectorTest, AssignTest)
{
	bksge::vector<int> v;

	{
		const int a[] { 1, 2, 3 };
		v.assign(bksge::begin(a), bksge::end(a));
	}
	EXPECT_EQ(3u, v.size());
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(2, v[1]);
	EXPECT_EQ(3, v[2]);

	{
		std::stringstream ss("4 5 6 7");
		std::istream_iterator<int> ii_first(ss);
		std::istream_iterator<int> ii_last;
		v.assign(ii_first, ii_last);
	}
	EXPECT_EQ(4u, v.size());
	EXPECT_EQ(4, v[0]);
	EXPECT_EQ(5, v[1]);
	EXPECT_EQ(6, v[2]);
	EXPECT_EQ(7, v[3]);

	v.assign(4, 10);
	EXPECT_EQ(4u, v.size());
	EXPECT_EQ(10, v[0]);
	EXPECT_EQ(10, v[1]);
	EXPECT_EQ(10, v[2]);
	EXPECT_EQ(10, v[3]);

	v.assign({3, 1, 4, 1, 5, 9});
	EXPECT_EQ(6u, v.size());
	EXPECT_EQ(3, v[0]);
	EXPECT_EQ(1, v[1]);
	EXPECT_EQ(4, v[2]);
	EXPECT_EQ(1, v[3]);
	EXPECT_EQ(5, v[4]);
	EXPECT_EQ(9, v[5]);

	v.assign({});
	EXPECT_EQ(0u, v.size());
}

GTEST_TEST(VectorTest, PushBackTest)
{
	bksge::vector<int> v;

	v.push_back(1);

	EXPECT_EQ(1u, v.size());
	EXPECT_EQ(1, v[0]);

	const int i1 = 3;
	v.push_back(i1);

	EXPECT_EQ(2u, v.size());
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(3, v[1]);

	int i2 = 5;
	v.push_back(bksge::move(i2));

	EXPECT_EQ(3u, v.size());
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(3, v[1]);
	EXPECT_EQ(5, v[2]);
}

GTEST_TEST(VectorTest, EmplaceBackTest)
{
	bksge::vector<bksge::pair<int, std::string>> v;

	v.emplace_back(3, "hoge");

	EXPECT_EQ(3,      v[0].first);
	EXPECT_EQ("hoge", v[0].second);
}

GTEST_TEST(VectorTest, PopBackTest)
{
	bksge::vector<int> v { 1, 2, 3 };

	EXPECT_EQ(3u, v.size());
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(2, v[1]);
	EXPECT_EQ(3, v[2]);

	v.pop_back();

	EXPECT_EQ(2u, v.size());
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(2, v[1]);

	v.pop_back();

	EXPECT_EQ(1u, v.size());
	EXPECT_EQ(1, v[0]);
}

GTEST_TEST(VectorTest, InsertTest)
{
	// (1)
	{
		bksge::vector<int> v { 1, 2, 3 };

		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);

		const int i = 5;
		auto it = v.insert(v.begin() + 1, i);

		EXPECT_EQ(5, *it);

		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(5, v[1]);
		EXPECT_EQ(2, v[2]);
		EXPECT_EQ(3, v[3]);
	}
	{
		bksge::vector<bksge::vector<int>> v;

		{
			bksge::vector<int> v1 { 11, 12, 13 };
			auto it = v.insert(v.begin(), v1);
			EXPECT_EQ(11, (*it)[0]);
			EXPECT_EQ(12, (*it)[1]);
			EXPECT_EQ(13, (*it)[2]);
		}
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(11, v[0][0]);
		EXPECT_EQ(12, v[0][1]);
		EXPECT_EQ(13, v[0][2]);

		{
			bksge::vector<int> v1 { 21, 22 };
			auto it = v.insert(v.begin(), v1);
			EXPECT_EQ(21, (*it)[0]);
			EXPECT_EQ(22, (*it)[1]);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(21, v[0][0]);
		EXPECT_EQ(22, v[0][1]);
		EXPECT_EQ(11, v[1][0]);
		EXPECT_EQ(12, v[1][1]);
		EXPECT_EQ(13, v[1][2]);

		{
			bksge::vector<int> v1 { 31, 32, 33, 34 };
			auto it = v.insert(v.begin() + 1, v1);
			EXPECT_EQ(31, (*it)[0]);
			EXPECT_EQ(32, (*it)[1]);
			EXPECT_EQ(33, (*it)[2]);
			EXPECT_EQ(34, (*it)[3]);
		}
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(21, v[0][0]);
		EXPECT_EQ(22, v[0][1]);
		EXPECT_EQ(31, v[1][0]);
		EXPECT_EQ(32, v[1][1]);
		EXPECT_EQ(33, v[1][2]);
		EXPECT_EQ(34, v[1][3]);
		EXPECT_EQ(11, v[2][0]);
		EXPECT_EQ(12, v[2][1]);
		EXPECT_EQ(13, v[2][2]);
	}
	// (2)
	{
		bksge::vector<int> v { 1, 2, 3 };

		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);

		int i = 5;
		auto it = v.insert(v.begin() + 1, bksge::move(i));

		EXPECT_EQ(5, *it);

		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(5, v[1]);
		EXPECT_EQ(2, v[2]);
		EXPECT_EQ(3, v[3]);
	}
	// (3)
	{
		bksge::vector<int> v { 1, 2, 3 };

		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);

		auto it = v.insert(v.begin() + 2, 3, 42);

		EXPECT_EQ(42, *it);

		EXPECT_EQ(6u, v.size());
		EXPECT_EQ( 1, v[0]);
		EXPECT_EQ( 2, v[1]);
		EXPECT_EQ(42, v[2]);
		EXPECT_EQ(42, v[3]);
		EXPECT_EQ(42, v[4]);
		EXPECT_EQ( 3, v[5]);
	}
	// (4)
	{
		bksge::vector<int> v { 1, 2, 3 };

		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);

		{
			const int a[] { 4, 5, 6 };
			auto it = v.insert(v.end(), bksge::begin(a), bksge::end(a));
			EXPECT_EQ(4, *it);
		}

		EXPECT_EQ(6u, v.size());
		EXPECT_EQ( 1, v[0]);
		EXPECT_EQ( 2, v[1]);
		EXPECT_EQ( 3, v[2]);
		EXPECT_EQ( 4, v[3]);
		EXPECT_EQ( 5, v[4]);
		EXPECT_EQ( 6, v[5]);

		{
			std::stringstream ss("7 8");
			std::istream_iterator<int> ii_first(ss);
			std::istream_iterator<int> ii_last;
			auto it = v.insert(v.begin() + 1, ii_first, ii_last);
			EXPECT_EQ(7, *it);
		}

		EXPECT_EQ(8u, v.size());
		EXPECT_EQ( 1, v[0]);
		EXPECT_EQ( 7, v[1]);
		EXPECT_EQ( 8, v[2]);
		EXPECT_EQ( 2, v[3]);
		EXPECT_EQ( 3, v[4]);
		EXPECT_EQ( 4, v[5]);
		EXPECT_EQ( 5, v[6]);
		EXPECT_EQ( 6, v[7]);
	}
	// (5)
	{
		bksge::vector<int> v { 1, 2, 3 };

		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);

		auto it = v.insert(v.begin(), {4, 5, 6, 7});

		EXPECT_EQ(4, *it);

		EXPECT_EQ(7u, v.size());
		EXPECT_EQ( 4, v[0]);
		EXPECT_EQ( 5, v[1]);
		EXPECT_EQ( 6, v[2]);
		EXPECT_EQ( 7, v[3]);
		EXPECT_EQ( 1, v[4]);
		EXPECT_EQ( 2, v[5]);
		EXPECT_EQ( 3, v[6]);
	}
}

GTEST_TEST(VectorTest, EmplaceTest)
{
	bksge::vector<bksge::pair<int, std::string>> v;

	v.emplace(v.begin(), 3, "hoge");

	EXPECT_EQ(3,      v[0].first);
	EXPECT_EQ("hoge", v[0].second);
}

GTEST_TEST(VectorTest, EraseTest)
{
	// (1)
	{
		bksge::vector<int> v { 1, 2, 3, 4, 5 };

		EXPECT_EQ(5u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(4, v[3]);
		EXPECT_EQ(5, v[4]);

		{
			auto it = v.erase(v.begin());
			EXPECT_EQ(2, *it);
		}

		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(3, v[1]);
		EXPECT_EQ(4, v[2]);
		EXPECT_EQ(5, v[3]);

		{
			auto it = v.erase(v.begin() + 1);
			EXPECT_EQ(4, *it);
		}

		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(5, v[2]);

		{
			auto it = v.erase(v.begin() + 2);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(4, v[1]);
	}
	// (2)
	{
		bksge::vector<int> v { 1, 2, 3, 4, 5 };

		EXPECT_EQ(5u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(4, v[3]);
		EXPECT_EQ(5, v[4]);

		{
			auto it = v.erase(v.begin(), v.begin() + 2);
			EXPECT_EQ(3, *it);
		}

		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(3, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(5, v[2]);

		{
			auto it = v.erase(v.begin(), v.end());
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_EQ(0u, v.size());
	}
}

GTEST_TEST(VectorTest, SwapTest)
{
	bksge::vector<int> v1 { 1, 2, 3 };
	bksge::vector<int> v2 { 4, 5, 6, 7 };

	v1.swap(v2);

	EXPECT_EQ(4u, v1.size());
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(6, v1[2]);
	EXPECT_EQ(7, v1[3]);
	EXPECT_EQ(3u, v2.size());
	EXPECT_EQ(1, v2[0]);
	EXPECT_EQ(2, v2[1]);
	EXPECT_EQ(3, v2[2]);

	swap(v1, v2);

	EXPECT_EQ(3u, v1.size());
	EXPECT_EQ(1, v1[0]);
	EXPECT_EQ(2, v1[1]);
	EXPECT_EQ(3, v1[2]);
	EXPECT_EQ(4u, v2.size());
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
	EXPECT_EQ(6, v2[2]);
	EXPECT_EQ(7, v2[3]);
}

GTEST_TEST(VectorTest, ClearTest)
{
	bksge::vector<int> v { 1, 2, 3 };

	EXPECT_FALSE(v.empty());

	v.clear();

	EXPECT_TRUE(v.empty());
}

GTEST_TEST(VectorTest, GetAllocatorTest)
{
	bksge::allocator<int> a;
	bksge::vector<int> v(a);

	auto r = v.get_allocator();

	EXPECT_TRUE(r == a);
}

GTEST_TEST(VectorTest, CompareTest)
{
	bksge::vector<int> v1 { 1, 2, 3 };
	bksge::vector<int> v2 { 1, 2, 3 };
	bksge::vector<int> v3 { 0, 2, 3 };
	bksge::vector<int> v4 { 2, 2, 3 };
	bksge::vector<int> v5 { 1, 2, 1 };
	bksge::vector<int> v6 { 1, 2, 4 };
	bksge::vector<int> v7 { 1, 2 };
	bksge::vector<int> v8 { 1, 2, 3, 4 };

	EXPECT_TRUE (v1 == v1);
	EXPECT_TRUE (v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);
	EXPECT_FALSE(v1 == v5);
	EXPECT_FALSE(v1 == v6);
	EXPECT_FALSE(v1 == v7);
	EXPECT_FALSE(v1 == v8);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE (v1 != v3);
	EXPECT_TRUE (v1 != v4);
	EXPECT_TRUE (v1 != v5);
	EXPECT_TRUE (v1 != v6);
	EXPECT_TRUE (v1 != v7);
	EXPECT_TRUE (v1 != v8);

	EXPECT_FALSE(v1 <  v1);
	EXPECT_FALSE(v1 <  v2);
	EXPECT_FALSE(v1 <  v3);
	EXPECT_TRUE (v1 <  v4);
	EXPECT_FALSE(v1 <  v5);
	EXPECT_TRUE (v1 <  v6);
	EXPECT_FALSE(v1 <  v7);
	EXPECT_TRUE (v1 <  v8);

	EXPECT_FALSE(v1 >  v1);
	EXPECT_FALSE(v1 >  v2);
	EXPECT_TRUE (v1 >  v3);
	EXPECT_FALSE(v1 >  v4);
	EXPECT_TRUE (v1 >  v5);
	EXPECT_FALSE(v1 >  v6);
	EXPECT_TRUE (v1 >  v7);
	EXPECT_FALSE(v1 >  v8);

	EXPECT_TRUE (v1 <= v1);
	EXPECT_TRUE (v1 <= v2);
	EXPECT_FALSE(v1 <= v3);
	EXPECT_TRUE (v1 <= v4);
	EXPECT_FALSE(v1 <= v5);
	EXPECT_TRUE (v1 <= v6);
	EXPECT_FALSE(v1 <= v7);
	EXPECT_TRUE (v1 <= v8);

	EXPECT_TRUE (v1 >= v1);
	EXPECT_TRUE (v1 >= v2);
	EXPECT_TRUE (v1 >= v3);
	EXPECT_FALSE(v1 >= v4);
	EXPECT_TRUE (v1 >= v5);
	EXPECT_FALSE(v1 >= v6);
	EXPECT_TRUE (v1 >= v7);
	EXPECT_FALSE(v1 >= v8);
}

}	// namespace bksge_vector_test
