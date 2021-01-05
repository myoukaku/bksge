/**
 *	@file	unit_test_fnd_random_engines_xoroshiro.cpp
 *
 *	@brief	xoroshiro のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/random/engines/xoroshiro.hpp>
#include <bksge/fnd/sstream/istringstream.hpp>
#include <bksge/fnd/sstream/ostringstream.hpp>
#include <random>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_random_test
{

namespace xoroshiro_test
{

using XoroshiroTestTypes = ::testing::Types<
	bksge::xoroshiro128starstar,
	bksge::xoroshiro128star,
	bksge::xoroshiro128plus,
	bksge::xoroshiro64starstar,
	bksge::xoroshiro64star,
	bksge::xoroshiro1024starstar,
	bksge::xoroshiro1024star,
	bksge::xoroshiro1024plus
>;

template <typename T>
class XoroshiroTest : public ::testing::Test {};
TYPED_TEST_SUITE(XoroshiroTest, XoroshiroTestTypes);

GTEST_TEST(Xoroshiro128Test, GenerateTest)
{
	{
		bksge::xoroshiro128starstar	e;
		EXPECT_EQ(16968012126571633075U, e());
		EXPECT_EQ( 7141899735468201917U, e());
		EXPECT_EQ(16259179226564127102U, e());
		EXPECT_EQ( 3420123762198687552U, e());
		EXPECT_EQ(11386387936366970547U, e());
	}
	{
		bksge::xoroshiro128star	e;
		EXPECT_EQ( 7503979001914005267U, e());
		EXPECT_EQ( 2831136087953284562U, e());
		EXPECT_EQ(  689029296222643886U, e());
		EXPECT_EQ( 4679223458511799590U, e());
		EXPECT_EQ(10872016672379670585U, e());
	}
	{
		bksge::xoroshiro128plus	e;
		EXPECT_EQ( 5935771268297859122U, e());
		EXPECT_EQ(15473567974492860740U, e());
		EXPECT_EQ( 1550340103376919285U, e());
		EXPECT_EQ(16988662530986123909U, e());
		EXPECT_EQ( 5348152095221562877U, e());
	}
}

GTEST_TEST(Xoroshiro64Test, GenerateTest)
{
	{
		bksge::xoroshiro64starstar	e;
		EXPECT_EQ(1873671452U, e());
		EXPECT_EQ(3277519382U, e());
		EXPECT_EQ(2809264179U, e());
		EXPECT_EQ( 598995401U, e());
		EXPECT_EQ(2818767005U, e());
	}
	{
		bksge::xoroshiro64star	e;
		EXPECT_EQ(1702853819U, e());
		EXPECT_EQ(4127546972U, e());
		EXPECT_EQ(3131409190U, e());
		EXPECT_EQ(2929690191U, e());
		EXPECT_EQ(3373060493U, e());
	}
}

GTEST_TEST(Xoroshiro1024Test, GenerateTest)
{
	{
		bksge::xoroshiro1024starstar	e;
		EXPECT_EQ( 9704468759007318649U, e());
		EXPECT_EQ( 6682727700222042062U, e());
		EXPECT_EQ(15573890136842553780U, e());
		EXPECT_EQ(10738970727608375964U, e());
		EXPECT_EQ( 4936835683531367474U, e());
	}
	{
		bksge::xoroshiro1024star	e;
		EXPECT_EQ(16466527217768367267U, e());
		EXPECT_EQ( 1564470160224948103U, e());
		EXPECT_EQ( 7324709781044359918U, e());
		EXPECT_EQ( 1458544928678517903U, e());
		EXPECT_EQ( 8293522010231248698U, e());
	}
	{
		bksge::xoroshiro1024plus	e;
		EXPECT_EQ( 5935771268297859122U, e());
		EXPECT_EQ(11990323554558717260U, e());
		EXPECT_EQ( 1111384398776950444U, e());
		EXPECT_EQ(15092056878560721025U, e());
		EXPECT_EQ(16818156358068173675U, e());
	}
}

TYPED_TEST(XoroshiroTest, DefaultCtorTest)
{
	using Engine = TypeParam;
	Engine e1;
	Engine e2(Engine::default_seed);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoroshiroTest, ResultTypeCtorTest)
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

TYPED_TEST(XoroshiroTest, SseqCtorTest)
{
	using Engine = TypeParam;
	{
		unsigned const a[] ={3, 5, 7};
		std::seed_seq sseq(a, a+3);
		Engine e1;
		Engine e2(sseq);
		EXPECT_TRUE(e1 != e2);
		EXPECT_NE(e1(), e2());
	}
	{
		unsigned const a[] ={3, 5, 7};
		std::seed_seq sseq(a, a+3);
		Engine e1(sseq);
		Engine e2(sseq);
		EXPECT_TRUE(e1 == e2);
		EXPECT_EQ(e1(), e2());
	}
}

TYPED_TEST(XoroshiroTest, CopyCtorTest)
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

TYPED_TEST(XoroshiroTest, CopyAssignTest)
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

TYPED_TEST(XoroshiroTest, DiscardTest)
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

TYPED_TEST(XoroshiroTest, GenerateTest)
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

TYPED_TEST(XoroshiroTest, SeedResultTypeTest)
{
	using Engine = TypeParam;

	Engine e1(42);
	Engine e2;
	EXPECT_TRUE(e1 != e2);
	e2.seed(42);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoroshiroTest, SeedSseqTest)
{
	using Engine = TypeParam;

	unsigned a[] ={1, 2, 3, 4, 5};
	std::seed_seq sseq(a, a+5);

	Engine e1(sseq);
	Engine e2;
	EXPECT_TRUE(e1 != e2);
	e2.seed(sseq);
	EXPECT_TRUE(e1 == e2);
}

TYPED_TEST(XoroshiroTest, MinTest)
{
	using Engine = TypeParam;
	EXPECT_EQ(Engine::min(), 0u);
}

TYPED_TEST(XoroshiroTest, MaxTest)
{
	using Engine = TypeParam;
	EXPECT_EQ(Engine::max(), typename Engine::result_type(~0));
}

TYPED_TEST(XoroshiroTest, InputOutputTest)
{
	using Engine = TypeParam;

	Engine e1;
	e1.discard(100);
	bksge::ostringstream os;
	os << e1;
	bksge::istringstream is(os.str());
	Engine e2;
	EXPECT_TRUE(e1 != e2);
	is >> e2;
	EXPECT_TRUE(e1 == e2);
}

}	// namespace xoroshiro_test

}	// namespace bksge_random_test
