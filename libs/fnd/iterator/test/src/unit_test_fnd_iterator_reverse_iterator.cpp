/**
 *	@file	unit_test_fnd_iterator_reverse_iterator.cpp
 *
 *	@brief	reverse_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace reverse_iterator_test
{

struct Base {};
struct Derived : Base {};

struct X
{
public:
	BKSGE_CXX14_CONSTEXPR X(int v) : m_v(v){}

	BKSGE_CXX14_CONSTEXPR int get() const { return m_v; }

private:
	int	m_v;
};

GTEST_TEST(ReverseIteratorTest, DefaultCtorTest)
{
	{
		BKSGE_CXX14_CONSTEXPR bksge::reverse_iterator<int*> it;
		(void)it;
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::reverse_iterator<char const*> it;
		(void)it;
	}
}

inline BKSGE_CXX14_CONSTEXPR bool iter_ctor_test()
{
	char s[] = "123";
	bksge::reverse_iterator<char*> it(s);
	return it.base() == s;
}

GTEST_TEST(ReverseIteratorTest, IterCtorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(iter_ctor_test());
}

inline BKSGE_CXX14_CONSTEXPR bool convert_ctor_test()
{
	Derived d{};
	bksge::reverse_iterator<Derived*> const it1(&d);
	bksge::reverse_iterator<Base*> it2(it1);
	return it2.base() == &d;
}

GTEST_TEST(ReverseIteratorTest, ConvertCtorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(convert_ctor_test());
}

inline BKSGE_CXX14_CONSTEXPR bool assign_test()
{
	Derived d{};
	bksge::reverse_iterator<Derived*> const it1(&d);
	bksge::reverse_iterator<Base*> it2;
	bksge::reverse_iterator<Base*>& r = it2 = it1;
	return
		it2.base() == &d &&
		&r == &it2;
}

GTEST_TEST(ReverseIteratorTest, AssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(assign_test());
}

inline BKSGE_CXX14_CONSTEXPR bool op_star_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it1(p+1);
	bksge::reverse_iterator<char const*> it2(p+2);
	return
		*it1 == p[0] &&
		*it2 == p[1];
}

GTEST_TEST(ReverseIteratorTest, OpStarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(op_star_test());
}

inline BKSGE_CXX14_CONSTEXPR bool op_arrow_test()
{
	X const a[] = {1,2,3,4,5,6,7,8,9};
	bksge::reverse_iterator<X const*> it1(a+1);
	bksge::reverse_iterator<X const*> it2(a+2);
	return
		it1->get() == a[0].get() &&
		it2->get() == a[1].get();
}

GTEST_TEST(ReverseIteratorTest, OpArrowTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(op_arrow_test());
}

inline BKSGE_CXX14_CONSTEXPR bool op_index_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it1(p+5);
	return
		it1[0] == p[4] &&
		it1[1] == p[3] &&
		it1[2] == p[2] &&
		it1[3] == p[1] &&
		it1[4] == p[0];
}

GTEST_TEST(ReverseIteratorTest, OpIndexTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(op_index_test());
}

inline BKSGE_CXX14_CONSTEXPR bool increment_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = it++;
	auto it3 = it;
	auto it4 = ++it;
	return
		*it1 == p[4] &&
		*it2 == p[4] &&
		*it3 == p[3] &&
		*it4 == p[2] &&
		*it  == p[2];
}

GTEST_TEST(ReverseIteratorTest, IncrementTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(increment_test());
}

inline BKSGE_CXX14_CONSTEXPR bool decrement_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = it--;
	auto it3 = it;
	auto it4 = --it;
	return
		*it1 == p[4] &&
		*it2 == p[4] &&
		*it3 == p[5] &&
		*it4 == p[6] &&
		*it  == p[6];
}

GTEST_TEST(ReverseIteratorTest, DecrementTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(decrement_test());
}

inline BKSGE_CXX14_CONSTEXPR bool add_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = (it += 1);
	auto it3 = it;
	auto it4 = (it += 2);
	return
		*it1 == p[4] &&
		*it2 == p[3] &&
		*it3 == p[3] &&
		*it4 == p[1] &&
		*it  == p[1];
}

GTEST_TEST(ReverseIteratorTest, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(add_test());
}

inline BKSGE_CXX14_CONSTEXPR bool sub_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = (it -= 1);
	auto it3 = it;
	auto it4 = (it -= 2);
	return
		*it1 == p[4] &&
		*it2 == p[5] &&
		*it3 == p[5] &&
		*it4 == p[7] &&
		*it  == p[7];
}

GTEST_TEST(ReverseIteratorTest, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(sub_test());
}

inline BKSGE_CXX14_CONSTEXPR bool plus_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = (it + 1);
	auto it3 = (2 + it);
	return
		*it1 == p[4] &&
		*it2 == p[3] &&
		*it3 == p[2] &&
		*it  == p[4];
}

GTEST_TEST(ReverseIteratorTest, PlusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(plus_test());
}

inline BKSGE_CXX14_CONSTEXPR bool minus_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it(p+5);
	auto it1 = it;
	auto it2 = (it - 1);
	auto it3 = (it - 2);
	return
		*it1 == p[4] &&
		*it2 == p[5] &&
		*it3 == p[6] &&
		*it  == p[4];
}

GTEST_TEST(ReverseIteratorTest, MinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(minus_test());
}

inline BKSGE_CXX14_CONSTEXPR bool distance_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it1(p+1);
	bksge::reverse_iterator<char const*> it2(p+2);
	bksge::reverse_iterator<char const*> it3(p+3);
	return
		((it1 - it1) ==  0) &&
		((it1 - it2) ==  1) &&
		((it1 - it3) ==  2) &&
		((it2 - it1) == -1) &&
		((it2 - it2) ==  0) &&
		((it2 - it3) ==  1) &&
		((it3 - it1) == -2) &&
		((it3 - it2) == -1) &&
		((it3 - it3) ==  0);
}

GTEST_TEST(ReverseIteratorTest, DistanceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(distance_test());
}

inline BKSGE_CXX14_CONSTEXPR bool compare_test()
{
	char const* p = "123456789";
	bksge::reverse_iterator<char const*> it1(p+1);
	bksge::reverse_iterator<char const*> it2(p+2);
	bksge::reverse_iterator<char const*> it3(p+3);
	return
		((it2 == it1) == false) &&
		((it2 == it2) == true)  &&
		((it2 == it3) == false) &&
		((it2 != it1) == true)  &&
		((it2 != it2) == false) &&
		((it2 != it3) == true)  &&
		((it2 <  it1) == true)  &&
		((it2 <  it2) == false) &&
		((it2 <  it3) == false) &&
		((it2 >  it1) == false) &&
		((it2 >  it2) == false) &&
		((it2 >  it3) == true)  &&
		((it2 <= it1) == true)  &&
		((it2 <= it2) == true)  &&
		((it2 <= it3) == false) &&
		((it2 >= it1) == false) &&
		((it2 >= it2) == true)  &&
		((it2 >= it3) == true);
}

GTEST_TEST(ReverseIteratorTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(compare_test());
}

}	// namespace reverse_iterator_test

}	// namespace bksge_iterator_test
