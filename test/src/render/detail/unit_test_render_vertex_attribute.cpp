/**
 *	@file	unit_test_render_vertex_attribute.cpp
 *
 *	@brief	VertexAttributeのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/detail/vertex_attribute.hpp>
#include <bksge/render/vertex_element.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_VertexAttribute, BasicTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		const VertexAttribute a(Semantic::kPosition, TypeEnum::kSInt8, 3, 0);
		EXPECT_EQ(Semantic::kPosition,	a.semantic());
		EXPECT_EQ(TypeEnum::kSInt8,		a.type());
		EXPECT_EQ(3u,					a.element_num());
		EXPECT_EQ(0u,					a.offset());
		EXPECT_EQ(3u,					a.bytes());
	}
	{
		const VertexAttribute a(Semantic::kColor, TypeEnum::kUInt16, 4, 2);
		EXPECT_EQ(Semantic::kColor,			a.semantic());
		EXPECT_EQ(TypeEnum::kUInt16,		a.type());
		EXPECT_EQ(4u,						a.element_num());
		EXPECT_EQ(2u,						a.offset());
		EXPECT_EQ(8u,						a.bytes());
	}
}

GTEST_TEST(Render_VertexAttribute, CompareTest)
{
	using namespace bksge;
	using namespace bksge::render;

	const VertexAttribute a1(Semantic::kPosition, TypeEnum::kSInt8,  3, 0);
	const VertexAttribute a2(Semantic::kPosition, TypeEnum::kSInt8,  3, 0);
	const VertexAttribute a3(Semantic::kNormal,   TypeEnum::kSInt8,  3, 0);
	const VertexAttribute a4(Semantic::kPosition, TypeEnum::kSInt32, 3, 0);
	const VertexAttribute a5(Semantic::kPosition, TypeEnum::kSInt8,  4, 0);
	const VertexAttribute a6(Semantic::kPosition, TypeEnum::kSInt8,  3, 1);

	EXPECT_TRUE (a1 == a1);
	EXPECT_TRUE (a1 == a2);
	EXPECT_FALSE(a1 == a3);
	EXPECT_FALSE(a1 == a4);
	EXPECT_FALSE(a1 == a5);
	EXPECT_FALSE(a1 == a6);

	EXPECT_FALSE(a1 != a1);
	EXPECT_FALSE(a1 != a2);
	EXPECT_TRUE (a1 != a3);
	EXPECT_TRUE (a1 != a4);
	EXPECT_TRUE (a1 != a5);
	EXPECT_TRUE (a1 != a6);
}

GTEST_TEST(Render_VertexAttribute, MakeVertexAttributeTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		auto const a = MakeVertexAttribute<VPosition>(0);
		EXPECT_EQ(Semantic::kPosition,	a.semantic());
		EXPECT_EQ(TypeEnum::kFloat,		a.type());
		EXPECT_EQ( 3u,					a.element_num());
		EXPECT_EQ( 0u,					a.offset());
		EXPECT_EQ(12u,					a.bytes());
	}
	{
		auto const a = MakeVertexAttribute<VNormal>(1);
		EXPECT_EQ(Semantic::kNormal,	a.semantic());
		EXPECT_EQ(TypeEnum::kFloat,		a.type());
		EXPECT_EQ( 3u,					a.element_num());
		EXPECT_EQ( 1u,					a.offset());
		EXPECT_EQ(12u,					a.bytes());
	}
	{
		auto const a = MakeVertexAttribute<VColor>(2);
		EXPECT_EQ(Semantic::kColor,		a.semantic());
		EXPECT_EQ(TypeEnum::kFloat,		a.type());
		EXPECT_EQ( 4u,					a.element_num());
		EXPECT_EQ( 2u,					a.offset());
		EXPECT_EQ(16u,					a.bytes());
	}
	{
		auto const a = MakeVertexAttribute<VTexCoord>(3);
		EXPECT_EQ(Semantic::kTexCoord,	a.semantic());
		EXPECT_EQ(TypeEnum::kFloat,		a.type());
		EXPECT_EQ( 2u,					a.element_num());
		EXPECT_EQ( 3u,					a.offset());
		EXPECT_EQ( 8u,					a.bytes());
	}
}
