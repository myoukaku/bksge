/**
 *	@file	unit_test_fnd_utility_pair_piecewise_construct.cpp
 *
 *	@brief	piecewise_construct のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace piecewise_construct_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct type_zero
{
	BKSGE_CONSTEXPR type_zero()
		: m_n(757) {}

	type_zero(const type_zero&) = delete;

	BKSGE_CONSTEXPR type_zero(type_zero&& other)
		: m_n(other.m_n) {}

	BKSGE_CONSTEXPR int get() const { return m_n; }

private:
	int m_n;
};

struct type_one
{
	BKSGE_CONSTEXPR type_one(int n)
		: m_n(n) {}

	type_one(const type_one&) = delete;

	BKSGE_CONSTEXPR type_one(type_one&& other)
		: m_n(other.m_n) {}

	BKSGE_CONSTEXPR int get() const { return m_n; }

private:
	int m_n;
};

struct type_two
{
	BKSGE_CONSTEXPR type_two(int n1, int n2)
		: m_n1(n1), m_n2(n2) {}

	type_two(const type_two&) = delete;

	BKSGE_CONSTEXPR type_two(type_two&& other)
		: m_n1(other.m_n1), m_n2(other.m_n2) {}

	BKSGE_CONSTEXPR int get1() const { return m_n1; }
	BKSGE_CONSTEXPR int get2() const { return m_n2; }

private:
	int m_n1, m_n2;
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	bksge::pair<type_one, type_zero> pp0(bksge::piecewise_construct,
		std::forward_as_tuple(-3),
		std::forward_as_tuple());
	VERIFY(pp0.first.get() == -3);
	VERIFY(pp0.second.get() == 757);

	bksge::pair<type_one, type_two> pp1(bksge::piecewise_construct,
		std::forward_as_tuple(6),
		std::forward_as_tuple(5, 4));
	VERIFY(pp1.first.get() == 6);
	VERIFY(pp1.second.get1() == 5);
	VERIFY(pp1.second.get2() == 4);

	bksge::pair<type_two, type_two> pp2(bksge::piecewise_construct,
		std::forward_as_tuple(2, 1),
		std::forward_as_tuple(-1, -3));
	VERIFY(pp2.first.get1() == 2);
	VERIFY(pp2.first.get2() == 1);
	VERIFY(pp2.second.get1() == -1);
	VERIFY(pp2.second.get2() == -3);

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, PiecewiseConstructTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test01()));
}

}	// namespace piecewise_construct_test

}	// namespace bksge_pair_test
