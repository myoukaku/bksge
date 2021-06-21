/**
 *	@file	unit_test_fnd_random_engines_xorshift.cpp
 *
 *	@brief	xorshift のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/random/engines/xorshift.hpp>
#include <bksge/fnd/random/seed_seq.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace bksge_random_test
{

namespace xorshift_test
{

using XorShiftTestTypes = ::testing::Types<
	bksge::xorshift32,
	bksge::xorshift64,
	bksge::xorshift128,
	bksge::xorwow,
	bksge::xorshift64star,
	bksge::xorshift1024star,
	bksge::xorshift128plus
>;

template <typename T>
class XorShiftTest : public ::testing::Test {};
TYPED_TEST_SUITE(XorShiftTest, XorShiftTestTypes);

GTEST_TEST(XorShift32Test, GenerateTest)
{
	{
		bksge::xorshift32	e;
		EXPECT_EQ(1759702352U, e());
		EXPECT_EQ(2622884212U, e());
		EXPECT_EQ(4067188424U, e());
		EXPECT_EQ(1327046738U, e());
		EXPECT_EQ( 158985915U, e());
	}
}

GTEST_TEST(XorShift64Test, GenerateTest)
{
	{
		bksge::xorshift64	e;
		EXPECT_EQ( 9917256526672510451U, e());
		EXPECT_EQ( 5464614852072397640U, e());
		EXPECT_EQ(14840442582314695678U, e());
		EXPECT_EQ( 9703301246473560329U, e());
		EXPECT_EQ( 2529497062930076043U, e());
	}
}

GTEST_TEST(XorShift128Test, GenerateTest)
{
	{
		bksge::xorshift128	e;
		EXPECT_EQ( 479642584U, e());
		EXPECT_EQ(1584067578U, e());
		EXPECT_EQ(3416052809U, e());
		EXPECT_EQ(1853085290U, e());
		EXPECT_EQ(3293663359U, e());
	}
}

GTEST_TEST(XorwowTest, GenerateTest)
{
	{
		bksge::xorwow	e;
		EXPECT_EQ(1059136079U, e());
		EXPECT_EQ(2825730898U, e());
		EXPECT_EQ( 925225704U, e());
		EXPECT_EQ( 191664944U, e());
		EXPECT_EQ(1928611581U, e());
	}
}

GTEST_TEST(XorShift64StarTest, GenerateTest)
{
	{
		bksge::xorshift64star	e;
		EXPECT_EQ(17616574552874421118U, e());
		EXPECT_EQ(13415435684713165503U, e());
		EXPECT_EQ( 8945673505294331433U, e());
		EXPECT_EQ(12786090481707746028U, e());
		EXPECT_EQ(15602385901641712791U, e());
	}
}

GTEST_TEST(XorShift1024StarTest, GenerateTest)
{
	{
		bksge::xorshift1024star	e;
		EXPECT_EQ( 3953794185744210506U, e());
		EXPECT_EQ( 7229817298509174867U, e());
		EXPECT_EQ(17249068839563917123U, e());
		EXPECT_EQ(11571337335857540683U, e());
		EXPECT_EQ( 1365642167102437748U, e());
	}
}

GTEST_TEST(XorShift128PlusTest, GenerateTest)
{
	{
		bksge::xorshift128plus	e;
		EXPECT_EQ(16656247399113149522U, e());
		EXPECT_EQ(  309317887156397309U, e());
		EXPECT_EQ(12864672493441531824U, e());
		EXPECT_EQ( 3215154934207661481U, e());
		EXPECT_EQ( 2849495309549311256U, e());
	}
}

TYPED_TEST(XorShiftTest, DefaultCtorTest)
{
	using Engine = TypeParam;
	Engine e1;
	Engine e2(Engine::default_seed);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XorShiftTest, ResultTypeCtorTest)
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

TYPED_TEST(XorShiftTest, SseqCtorTest)
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

TYPED_TEST(XorShiftTest, CopyCtorTest)
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

TYPED_TEST(XorShiftTest, CopyAssignTest)
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

TYPED_TEST(XorShiftTest, DiscardTest)
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

TYPED_TEST(XorShiftTest, GenerateTest)
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

TYPED_TEST(XorShiftTest, SeedResultTypeTest)
{
	using Engine = TypeParam;

	Engine e1(42);
	Engine e2;
	EXPECT_TRUE(e1 != e2);
	e2.seed(42);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XorShiftTest, SeedSseqTest)
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

TYPED_TEST(XorShiftTest, MinTest)
{
	using Engine = TypeParam;
	EXPECT_EQ(Engine::min(), 0u);
}

TYPED_TEST(XorShiftTest, MaxTest)
{
	using Engine = TypeParam;
	EXPECT_EQ(Engine::max(), typename Engine::result_type(~0));
}

TYPED_TEST(XorShiftTest, InputOutputTest)
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

}	// namespace xorshift_test

}	// namespace bksge_random_test
