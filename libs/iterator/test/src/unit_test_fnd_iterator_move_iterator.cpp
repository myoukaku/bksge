/**
 *	@file	unit_test_fnd_iterator_move_iterator.cpp
 *
 *	@brief	move_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/move_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace move_iterator_test
{

struct Base {};
struct Derived : Base {};

struct Movable
{
public:
	BKSGE_CXX14_CONSTEXPR Movable(int v) : m_value(v){}
	BKSGE_CXX14_CONSTEXPR Movable(Movable&& other) : m_value(other.m_value) { other.m_value = 0; }
	BKSGE_CXX14_CONSTEXPR Movable& operator=(Movable&& other) { m_value = other.m_value; other.m_value = 0; return *this; }
	BKSGE_CXX14_CONSTEXPR int value() const { return m_value; }
private:
	Movable(Movable const&) = delete;
	Movable& operator=(Movable const&) = delete;
	int	m_value;
};

GTEST_TEST(MoveIteratorTest, DefaultCtorTest)
{
	{
		bksge::move_iterator<char*> it;
		(void)it;
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::move_iterator<char*> it;
		(void)it;
	}
}

inline BKSGE_CXX14_CONSTEXPR bool iter_ctor_test()
{
	char s[] = "123";
	bksge::move_iterator<char*> it(s);
	return it.base() == s;
}

GTEST_TEST(MoveIteratorTest, IterCtorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(iter_ctor_test());
}

inline BKSGE_CXX14_CONSTEXPR bool convert_ctor_test()
{
	Derived d{};
	bksge::move_iterator<Derived*> const it1(&d);
	bksge::move_iterator<Base*> it2(it1);
	return it2.base() == &d;
}

GTEST_TEST(MoveIteratorTest, ConvertCtorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(convert_ctor_test());
}

inline BKSGE_CXX14_CONSTEXPR bool assign_test()
{
	Derived d{};
	bksge::move_iterator<Derived*> const it1(&d);
	bksge::move_iterator<Base*> it2;
	bksge::move_iterator<Base*>& r = it2 = it1;
	return
		it2.base() == &d &&
		&r == &it2;
}

GTEST_TEST(MoveIteratorTest, AssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(assign_test());
}

template <int n>
inline BKSGE_CXX14_CONSTEXPR bool op_star_test()
{
	Movable x(n);
	bksge::move_iterator<Movable*> p(&x);
	Movable y(*p);
	return
		0 == x.value() &&
		n == y.value();
}

GTEST_TEST(MoveIteratorTest, OpStarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(op_star_test<43>());
}

inline BKSGE_CXX14_CONSTEXPR bool op_index_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> p(&a[1]);
	Movable y(*p);
	return
		1 == a[0].value() &&
		0 == a[1].value() &&
		3 == a[2].value() &&
		2 == y.value();
}

GTEST_TEST(MoveIteratorTest, OpIndexTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(op_index_test());
}

inline BKSGE_CXX14_CONSTEXPR bool increment_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> p(&a[0]);
	Movable y(*(p++));
	Movable z(*(++p));
	return
		0 == a[0].value() &&
		2 == a[1].value() &&
		0 == a[2].value() &&
		1 == y.value() &&
		3 == z.value() &&
		p.base() == &a[2];
}

GTEST_TEST(MoveIteratorTest, IncrementTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(increment_test());
}

inline BKSGE_CXX14_CONSTEXPR bool decrement_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> p(&a[2]);
	Movable y(*(p--));
	Movable z(*(--p));
	return
		0 == a[0].value() &&
		2 == a[1].value() &&
		0 == a[2].value() &&
		3 == y.value() &&
		1 == z.value() &&
		p.base() == &a[0];
}

GTEST_TEST(MoveIteratorTest, DecrementTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(decrement_test());
}

inline BKSGE_CXX14_CONSTEXPR bool add_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> p(&a[0]);
	Movable y(*(p += 2));
	return
		1 == a[0].value() &&
		2 == a[1].value() &&
		0 == a[2].value() &&
		3 == y.value() &&
		p.base() == &a[2];
}

GTEST_TEST(MoveIteratorTest, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(add_test());
}

inline BKSGE_CXX14_CONSTEXPR bool sub_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> p(&a[2]);
	Movable y(*(p -= 2));
	return
		0 == a[0].value() &&
		2 == a[1].value() &&
		3 == a[2].value() &&
		1 == y.value() &&
		p.base() == &a[0];
}

GTEST_TEST(MoveIteratorTest, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(sub_test());
}

inline BKSGE_CXX14_CONSTEXPR bool plus_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> p(&a[0]);
	Movable y(*(p + 1));
	Movable z(*(2 + p));
	return
		1 == a[0].value() &&
		0 == a[1].value() &&
		0 == a[2].value() &&
		2 == y.value() &&
		3 == z.value() &&
		p.base() == &a[0];
}

GTEST_TEST(MoveIteratorTest, PlusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(plus_test());
}

inline BKSGE_CXX14_CONSTEXPR bool minus_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> p(&a[2]);
	Movable y(*(p - 1));
	Movable z(*(p - 2));
	return
		0 == a[0].value() &&
		0 == a[1].value() &&
		3 == a[2].value() &&
		2 == y.value() &&
		1 == z.value() &&
		p.base() == &a[2];
}

GTEST_TEST(MoveIteratorTest, MinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(minus_test());
}

inline BKSGE_CXX14_CONSTEXPR bool distance_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> it1(&a[0]);
	bksge::move_iterator<Movable*> it2(&a[1]);
	bksge::move_iterator<Movable*> it3(&a[2]);
	return
		((it1 - it1) ==  0) &&
		((it1 - it2) == -1) &&
		((it1 - it3) == -2) &&
		((it2 - it1) ==  1) &&
		((it2 - it2) ==  0) &&
		((it2 - it3) == -1) &&
		((it3 - it1) ==  2) &&
		((it3 - it2) ==  1) &&
		((it3 - it3) ==  0);
}

GTEST_TEST(MoveIteratorTest, DistanceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(distance_test());
}

inline BKSGE_CXX14_CONSTEXPR bool compare_test()
{
	Movable a[] = {Movable(1), Movable(2), Movable(3)};
	bksge::move_iterator<Movable*> it1(&a[0]);
	bksge::move_iterator<Movable*> it2(&a[1]);
	bksge::move_iterator<Movable*> it3(&a[2]);
	return
		((it2 == it1) == false) &&
		((it2 == it2) == true)  &&
		((it2 == it3) == false) &&
		((it2 != it1) == true)  &&
		((it2 != it2) == false) &&
		((it2 != it3) == true)  &&
		((it2 <  it1) == false) &&
		((it2 <  it2) == false) &&
		((it2 <  it3) == true)  &&
		((it2 >  it1) == true)  &&
		((it2 >  it2) == false) &&
		((it2 >  it3) == false) &&
		((it2 <= it1) == false) &&
		((it2 <= it2) == true)  &&
		((it2 <= it3) == true)  &&
		((it2 >= it1) == true)  &&
		((it2 >= it2) == true)  &&
		((it2 >= it3) == false);
}

GTEST_TEST(MoveIteratorTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(compare_test());
}

}	// namespace move_iterator_test

}	// namespace bksge_iterator_test
