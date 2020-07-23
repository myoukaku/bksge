/**
 *	@file	unit_test_fnd_memory_to_address.cpp
 *
 *	@brief	to_address のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/to_address.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace to_address_test
{

class P1
{
public:
	using element_type = int;

	explicit BKSGE_CONSTEXPR P1(int* p)
		: p_(p) { }

	BKSGE_CONSTEXPR int* operator->() const noexcept
	{
		return p_;
	}

private:
	int* p_;
};

class P2
{
public:
	using element_type = int;

	explicit BKSGE_CONSTEXPR P2(int* p)
		: p_(p) { }

	BKSGE_CONSTEXPR P1 operator->() const noexcept
	{
		return p_;
	}

private:
	P1 p_;
};

class P3
{
public:
	explicit BKSGE_CONSTEXPR P3(int* p)
		: p_(p) { }

	BKSGE_CONSTEXPR int* get() const noexcept
	{
		return p_;
	}

private:
	int* p_;
};

class P4
{
public:
	explicit BKSGE_CONSTEXPR P4(int* p)
		: p_(p) { }

	BKSGE_CONSTEXPR int* operator->() const noexcept
	{
		return nullptr;
	}

	BKSGE_CONSTEXPR int* get() const noexcept
	{
		return p_;
	}

private:
	int* p_;
};

}	// namespace to_address_test

}	// namespace bksge_memory_test

namespace std
{

template<>
struct pointer_traits<bksge_memory_test::to_address_test::P3>
{
	static BKSGE_CONSTEXPR int*
	to_address(const bksge_memory_test::to_address_test::P3& p) noexcept
	{
		return p.get();
	}
};

template<>
struct pointer_traits<bksge_memory_test::to_address_test::P4>
{
	static BKSGE_CONSTEXPR int*
	to_address(const bksge_memory_test::to_address_test::P4& p) noexcept
	{
		return p.get();
	}
};

}	// namespace std

namespace bksge_memory_test
{

namespace to_address_test
{

BKSGE_CXX14_CONSTEXPR bool test1()
{
	int i = 0;
	int* p = &i;
	return (bksge::to_address(p) == &i);
}
BKSGE_CXX14_CONSTEXPR bool test2()
{
	int i = 0;
	P1 p(&i);
	return (bksge::to_address(p) == &i);
}
BKSGE_CXX14_CONSTEXPR bool test3()
{
	int i = 0;
	P2 p(&i);
	return (bksge::to_address(p) == &i);
}
BKSGE_CXX14_CONSTEXPR bool test4()
{
	int i = 0;
	P3 p(&i);
	return (bksge::to_address(p) == &i);
}
BKSGE_CXX14_CONSTEXPR bool test5()
{
	int i = 0;
	P4 p(&i);
	return (bksge::to_address(p) == &i);
}

GTEST_TEST(MemoryTest, ToAddressTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test2());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test3());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test4());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test5());
}

}	// namespace to_address_test

}	// namespace bksge_memory_test
