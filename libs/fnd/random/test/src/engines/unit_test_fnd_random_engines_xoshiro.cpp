/**
 *	@file	unit_test_fnd_random_engines_xoshiro.cpp
 *
 *	@brief	xoshiro のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/random/engines/xoshiro.hpp>
#include <bksge/fnd/random/seed_seq.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace bksge_random_test
{

namespace xoshiro_test
{

using XoshiroTestTypes = ::testing::Types<
	bksge::xoshiro256starstar,
	bksge::xoshiro256plus,
	bksge::xoshiro128starstar,
	bksge::xoshiro128plus,
	bksge::xoshiro512starstar,
	bksge::xoshiro512plus
>;

template <typename T>
class XoshiroTest : public ::testing::Test {};
TYPED_TEST_SUITE(XoshiroTest, XoshiroTestTypes);

GTEST_TEST(Xoshiro256Test, GenerateTest)
{
	{
		bksge::xoshiro256starstar	e;
		EXPECT_EQ( 9704468759007318649U, e());
		EXPECT_EQ( 6107018170870048781U, e());
		EXPECT_EQ(14265819475815916301U, e());
		EXPECT_EQ(14316270549696789139U, e());
		EXPECT_EQ( 3587917546556971649U, e());
	}
	{
		bksge::xoshiro256plus	e;
		EXPECT_EQ( 6919976103715683355U, e());
		EXPECT_EQ( 5340440007974991913U, e());
		EXPECT_EQ(11281222545134715045U, e());
		EXPECT_EQ( 1646003450124521023U, e());
		EXPECT_EQ( 6030167717500554646U, e());
	}
}

GTEST_TEST(Xoshiro128Test, GenerateTest)
{
	{
		bksge::xoshiro128starstar	e;
		EXPECT_EQ(2055327720U, e());
		EXPECT_EQ(2274403753U, e());
		EXPECT_EQ( 444490680U, e());
		EXPECT_EQ(3373243000U, e());
		EXPECT_EQ(1488122016U, e());
	}
	{
		bksge::xoshiro128plus	e;
		EXPECT_EQ(1277836315U, e());
		EXPECT_EQ(1235278825U, e());
		EXPECT_EQ(4181684155U, e());
		EXPECT_EQ(2584829628U, e());
		EXPECT_EQ(3543839311U, e());
	}
}

GTEST_TEST(Xoshiro512Test, GenerateTest)
{
	{
		bksge::xoshiro512starstar	e;
		EXPECT_EQ( 9704468759007318649U, e());
		EXPECT_EQ( 6107018170870048781U, e());
		EXPECT_EQ( 5054062854043022332U, e());
		EXPECT_EQ(16246517855431934821U, e());
		EXPECT_EQ( 3391123419404408030U, e());
	}
	{
		bksge::xoshiro512plus	e;
		EXPECT_EQ(12743888657125588542U, e());
		EXPECT_EQ( 7902419264184470219U, e());
		EXPECT_EQ(16264352357590435822U, e());
		EXPECT_EQ( 2282615994117961436U, e());
		EXPECT_EQ(16536439120617837224U, e());
	}
}

TYPED_TEST(XoshiroTest, DefaultCtorTest)
{
	using Engine = TypeParam;
	Engine e1;
	Engine e2(Engine::default_seed);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoshiroTest, ResultTypeCtorTest)
{
	using Engine = TypeParam;
	{
		Engine e1(1);
		Engine e2(2);
		EXPECT_TRUE(e1 != e2);
		EXPECT_NE(e1(), e2());
	}
	{
		Engine e1(2);
		Engine e2(2);
		EXPECT_TRUE(e1 == e2);
		EXPECT_EQ(e1(), e2());
	}
}

TYPED_TEST(XoshiroTest, SseqCtorTest)
{
	using Engine = TypeParam;
	{
		unsigned const a[] ={3, 5, 7};
		bksge::seed_seq sseq(a, a+3);
		Engine e1;
		Engine e2(sseq);
		EXPECT_TRUE(e1 != e2);
		EXPECT_NE(e1(), e2());
	}
	{
		unsigned const a[] ={3, 5, 7};
		bksge::seed_seq sseq(a, a+3);
		Engine e1(sseq);
		Engine e2(sseq);
		EXPECT_TRUE(e1 == e2);
		EXPECT_EQ(e1(), e2());
	}
}

TYPED_TEST(XoshiroTest, CopyCtorTest)
{
	using Engine = TypeParam;

	Engine e1;
	(void)e1();
	Engine e2 = e1;
	EXPECT_TRUE(e1 == e2);
	EXPECT_EQ(e1(), e2());
	typename Engine::result_type k = e1();
	EXPECT_TRUE(e1 != e2);
	EXPECT_EQ(e2(), k);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoshiroTest, CopyAssignTest)
{
	using Engine = TypeParam;

	Engine e1(2);
	Engine e2(5);
	EXPECT_TRUE(e1 != e2);
	EXPECT_NE(e1(), e2());

	e2 = e1;
	EXPECT_TRUE(e1 == e2);
	EXPECT_EQ(e1(), e2());
	typename Engine::result_type k = e1();
	EXPECT_TRUE(e1 != e2);
	EXPECT_EQ(e2(), k);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoshiroTest, DiscardTest)
{
	using Engine = TypeParam;

	Engine e1;
	Engine e2 = e1;
	EXPECT_TRUE(e1 == e2);
	e1.discard(3);
	EXPECT_TRUE(e1 != e2);
	(void)e2();
	EXPECT_TRUE(e1 != e2);
	(void)e2();
	EXPECT_TRUE(e1 != e2);
	(void)e2();
	EXPECT_TRUE(e1 == e2);
	(void)e2();
	EXPECT_TRUE(e1 != e2);
}

TYPED_TEST(XoshiroTest, GenerateTest)
{
	using Engine = TypeParam;

	Engine e;
	auto const t1 = e();
	auto const t2 = e();
	auto const t3 = e();
	EXPECT_NE(t1, t2);
	EXPECT_NE(t1, t3);
	EXPECT_NE(t2, t3);
}

TYPED_TEST(XoshiroTest, SeedResultTypeTest)
{
	using Engine = TypeParam;

	Engine e1(42);
	Engine e2;
	EXPECT_TRUE(e1 != e2);
	e2.seed(42);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoshiroTest, SeedSseqTest)
{
	using Engine = TypeParam;

	unsigned a[] ={1, 2, 3, 4, 5};
	bksge::seed_seq sseq(a, a+5);

	Engine e1(sseq);
	Engine e2;
	EXPECT_TRUE(e1 != e2);
	e2.seed(sseq);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoshiroTest, MinTest)
{
	using Engine = TypeParam;
	EXPECT_EQ(Engine::min(), 0u);
}

TYPED_TEST(XoshiroTest, MaxTest)
{
	using Engine = TypeParam;
	EXPECT_EQ(Engine::max(), typename Engine::result_type(~0));
}

TYPED_TEST(XoshiroTest, InputOutputTest)
{
	using Engine = TypeParam;

	Engine e1;
	e1.discard(100);
	std::ostringstream os;
	os << e1;
	std::istringstream is(os.str());
	Engine e2;
	EXPECT_TRUE(e1 != e2);
	is >> e2;
	EXPECT_TRUE(e1 == e2);
}

}	// namespace xoshiro_test

}	// namespace bksge_random_test
