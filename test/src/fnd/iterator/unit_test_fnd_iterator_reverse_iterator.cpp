/**
 *	@file	unit_test_fnd_iterator_reverse_iterator.cpp
 *
 *	@brief	reverse_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/iterator/make_reverse_iterator.hpp>
#include <bksge/fnd/iterator/rbegin.hpp>
#include <bksge/fnd/iterator/rend.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/prev.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test_helper.hpp"

namespace bksge_iterator_test
{

namespace reverse_iterator_test
{

class Foo
{
public:
	int get() const { return 42; }
};

GTEST_TEST(IteratorTest, ReverseIteratorTest)
{
	{
		bksge::reverse_iterator<std::string::iterator>      i1;
		bksge::reverse_iterator<std::vector<int>::iterator> i2;
		bksge::reverse_iterator<std::list<float>::iterator> i3;
		bksge::reverse_iterator<int*>                       i4;
		(void)i1;
		(void)i2;
		(void)i3;
		(void)i4;
	}
	{
		std::string s = "abcde";
		bksge::reverse_iterator<std::string::iterator> i = s.rbegin();
		EXPECT_EQ('e', *i);
		++i;
		EXPECT_EQ('d', *i);
		++i;
		EXPECT_EQ('c', *i);
		*i = 'Z';
		++i;
		EXPECT_EQ('b', *i);
		++i;
		EXPECT_EQ('a', *i);
		++i;
		EXPECT_TRUE(i == s.rend());

		EXPECT_EQ("abZde", s);
	}
	{
		std::vector<int> v {1, 2, 3, 4, 5};
		bksge::reverse_iterator<std::vector<int>::iterator> i = v.rbegin();

		EXPECT_FALSE(i == v.rend());
		EXPECT_TRUE (i != v.rend());
		EXPECT_TRUE (i <  v.rend());
		EXPECT_FALSE(i >  v.rend());
		EXPECT_TRUE (i <= v.rend());
		EXPECT_FALSE(i >= v.rend());

		EXPECT_FALSE(v.rend() == i);
		EXPECT_TRUE (v.rend() != i);
		EXPECT_FALSE(v.rend() <  i);
		EXPECT_TRUE (v.rend() >  i);
		EXPECT_FALSE(v.rend() <= i);
		EXPECT_TRUE (v.rend() >= i);

		EXPECT_EQ( 0, i - v.rbegin());
		EXPECT_EQ( 0, v.rbegin() - i);
		EXPECT_EQ(-5, i - v.rend());
		EXPECT_EQ( 5, v.rend() - i);

		EXPECT_EQ(5, *i);
		++i;
		EXPECT_EQ(4, *i);
		i++;
		EXPECT_EQ(3, *i);
		--i;
		EXPECT_EQ(4, *i);
		i--;
		EXPECT_EQ(5, *i);
		i = bksge::next(i);
		EXPECT_EQ(4, *i);
		i += 2;
		EXPECT_EQ(2, *i);
		i = bksge::prev(i);
		EXPECT_EQ(3, *i);
		i -= 2;
		EXPECT_EQ(5, *i);
		i = i + 3;
		EXPECT_EQ(2, *i);
		i = i - 3;
		EXPECT_EQ(5, *i);
		i = 5 + i;
		EXPECT_TRUE(i == v.rend());
	}
	{
		const int a[] {3, 4, 5, 6};
		bksge::reverse_iterator<const int*> first = bksge::rbegin(a);
		bksge::reverse_iterator<const int*> last  = bksge::rend(a);

		EXPECT_EQ(4, bksge::distance(first, last));
		{
			const int expected[] = { 6, 5, 4, 3 };
			random_access_iterator_test(first, (int)bksge::size(expected), expected);
		}

		auto i = first;

		EXPECT_EQ( 0, i - first);
		EXPECT_EQ( 0, first - i);
		EXPECT_EQ(-4, i - last);
		EXPECT_EQ( 4, last - i);

		EXPECT_EQ(6, i[0]);
		EXPECT_EQ(5, i[1]);
		EXPECT_EQ(4, i[2]);
		EXPECT_EQ(3, i[3]);

		++i;
		EXPECT_EQ(5, i[0]);
		EXPECT_EQ(4, i[1]);
		EXPECT_EQ(3, i[2]);

		i++;
		EXPECT_EQ(4, i[0]);
		EXPECT_EQ(3, i[1]);

		i+=1;
		EXPECT_EQ(3, i[0]);

		EXPECT_EQ( 3, i - first);
		EXPECT_EQ(-3, first - i);
		EXPECT_EQ(-1, i - last);
		EXPECT_EQ( 1, last - i);
	}
	{
		std::array<int, 3> a {{1, 2, 3}};
		auto first = bksge::rbegin(a);
		auto last  = bksge::rend(a);

		EXPECT_EQ(3, bksge::distance(first, last));

		auto i1 = first;

		EXPECT_TRUE (i1 == first);
		EXPECT_FALSE(i1 != first);
		EXPECT_FALSE(i1 <  first);
		EXPECT_FALSE(i1 >  first);
		EXPECT_TRUE (i1 <= first);
		EXPECT_TRUE (i1 >= first);

		EXPECT_FALSE(i1 == last);
		EXPECT_TRUE (i1 != last);
		EXPECT_TRUE (i1 <  last);
		EXPECT_FALSE(i1 >  last);
		EXPECT_TRUE (i1 <= last);
		EXPECT_FALSE(i1 >= last);

		EXPECT_EQ( 0, i1 - first);
		EXPECT_EQ( 0, first - i1);
		EXPECT_EQ(-3, i1 - last);
		EXPECT_EQ( 3, last - i1);

		EXPECT_EQ(3, *i1);
		EXPECT_EQ(3, i1[0]);
		EXPECT_EQ(2, i1[1]);
		EXPECT_EQ(1, i1[2]);

		auto i2 = bksge::next(i1);
		EXPECT_EQ(2, *i2);
		EXPECT_EQ(2, i2[0]);
		EXPECT_EQ(1, i2[1]);

		auto i3 = i1 + 2;
		EXPECT_EQ(1, *i3);

		auto i4 = bksge::prev(i3);
		EXPECT_EQ(2, *i4);

		auto i5 = i3 - 2;
		EXPECT_EQ(3, *i5);
	}
	{
		Foo a[3];
		bksge::reverse_iterator<const Foo*> i = bksge::rbegin(a);
		EXPECT_EQ(42, i->get());
	}
	{
		std::vector<int> v{1, 2, 3};
		auto i1 = bksge::make_reverse_iterator(v.begin());
		auto i2 = bksge::make_reverse_iterator(v.end());
		bksge::swap(i1, i2);
		EXPECT_EQ(3, *i1);
		i1 = bksge::next(i1);
		EXPECT_EQ(2, *i1);
		i1 = bksge::prev(i1);
		EXPECT_EQ(3, *i1);
	}
}

}	// namespace bksge_iterator_test

}	// namespace reverse_iterator_test
