/**
 *	@file	unit_test_core_render_vertex_layout.cpp
 *
 *	@brief	VertexLayoutのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/vertex_layout.hpp>
#include <bksge/core/render/vertex_element.hpp>
#include <utility>
#include <gtest/gtest.h>

GTEST_TEST(Render_VertexLayout, BasicTest)
{
	using namespace bksge;
	using namespace bksge::render;

	VertexLayout l;

	EXPECT_EQ(0u, l.total_bytes());
	EXPECT_EQ(nullptr, l.FindVertexAttributeBySemantic(Semantic::kPosition));
	EXPECT_EQ(nullptr, l.FindVertexAttributeBySemantic(Semantic::kColor));
	EXPECT_EQ(nullptr, l.FindVertexAttributeBySemantic(Semantic::kNormal));

	l.AddAttribute(MakeVertexAttribute<VPosition>(0));

	EXPECT_EQ(12u, l.total_bytes());
	EXPECT_NE(nullptr, l.FindVertexAttributeBySemantic(Semantic::kPosition));
	EXPECT_EQ(nullptr, l.FindVertexAttributeBySemantic(Semantic::kColor));
	EXPECT_EQ(nullptr, l.FindVertexAttributeBySemantic(Semantic::kNormal));

	{
		auto const a = l.FindVertexAttributeBySemantic(Semantic::kPosition);
		EXPECT_EQ(Semantic::kPosition, a->semantic());
		EXPECT_EQ(TypeEnum::kFloat, a->type());
		EXPECT_EQ( 3u, a->element_num());
		EXPECT_EQ( 0u, a->offset());
		EXPECT_EQ(12u, a->bytes());
	}

	{
		const VertexAttribute a(Semantic::kColor, TypeEnum::kSInt8, 4, 12);
		l.AddAttribute(a);
	}

	EXPECT_EQ(16u, l.total_bytes());
	EXPECT_NE(nullptr, l.FindVertexAttributeBySemantic(Semantic::kPosition));
	EXPECT_NE(nullptr, l.FindVertexAttributeBySemantic(Semantic::kColor));
	EXPECT_EQ(nullptr, l.FindVertexAttributeBySemantic(Semantic::kNormal));

	{
		auto const a = l.FindVertexAttributeBySemantic(Semantic::kColor);
		EXPECT_EQ(Semantic::kColor, a->semantic());
		EXPECT_EQ(TypeEnum::kSInt8, a->type());
		EXPECT_EQ( 4u, a->element_num());
		EXPECT_EQ(12u, a->offset());
		EXPECT_EQ( 4u, a->bytes());
	}
}

GTEST_TEST(Render_VertexLayout, MoveCtorTest)
{
	using namespace bksge;
	using namespace bksge::render;

	VertexLayout l;
	l.AddAttribute(MakeVertexAttribute<VPosition>(l.total_bytes()));
	l.AddAttribute(MakeVertexAttribute<VNormal>  (l.total_bytes()));
	l.AddAttribute(MakeVertexAttribute<VTexCoord>(l.total_bytes()));

//	VertexLayout const l2(l);	// コピー禁止
	VertexLayout const l2(std::move(l));

	EXPECT_EQ(32u, l2.total_bytes());
	EXPECT_NE(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kPosition));
	EXPECT_EQ(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kColor));
	EXPECT_NE(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kNormal));
	EXPECT_NE(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kTexCoord));
}

GTEST_TEST(Render_VertexLayout, MoveAssignTest)
{
	using namespace bksge;
	using namespace bksge::render;

	VertexLayout l;
	l.AddAttribute(MakeVertexAttribute<VPosition>(l.total_bytes()));
	l.AddAttribute(MakeVertexAttribute<VNormal>  (l.total_bytes()));
	l.AddAttribute(MakeVertexAttribute<VTexCoord>(l.total_bytes()));

	VertexLayout l2;
//	l2 = l;	// コピー禁止
	l2 = std::move(l);
	EXPECT_EQ(32u, l2.total_bytes());
	EXPECT_NE(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kPosition));
	EXPECT_EQ(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kColor));
	EXPECT_NE(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kNormal));
	EXPECT_NE(nullptr, l2.FindVertexAttributeBySemantic(Semantic::kTexCoord));
}

GTEST_TEST(Render_VertexLayout, VertexAttributeArrayTest)
{
	using namespace bksge;

	VertexLayout l;
	l.AddAttribute(render::MakeVertexAttribute<VPosition>(l.total_bytes()));
	l.AddAttribute(render::MakeVertexAttribute<VNormal>  (l.total_bytes()));
	l.AddAttribute(render::MakeVertexAttribute<VTexCoord>(l.total_bytes()));

	auto const& vaa = l.vertex_attribute_array();
	EXPECT_EQ(3u, vaa.size());
	EXPECT_EQ(Semantic::kPosition, vaa[0].semantic());
	EXPECT_EQ(Semantic::kNormal,   vaa[1].semantic());
	EXPECT_EQ(Semantic::kTexCoord, vaa[2].semantic());
}

GTEST_TEST(Render_VertexLayout, CompareTest)
{
	using namespace bksge;
	using namespace bksge::render;

	VertexLayout l1;
	l1.AddAttribute(MakeVertexAttribute<VPosition>(l1.total_bytes()));
	l1.AddAttribute(MakeVertexAttribute<VNormal>  (l1.total_bytes()));
	l1.AddAttribute(MakeVertexAttribute<VTexCoord>(l1.total_bytes()));

	VertexLayout l2;
	l2.AddAttribute(MakeVertexAttribute<VPosition>(l2.total_bytes()));
	l2.AddAttribute(MakeVertexAttribute<VNormal>  (l2.total_bytes()));
	l2.AddAttribute(MakeVertexAttribute<VTexCoord>(l2.total_bytes()));

	VertexLayout l3;
	l3.AddAttribute(MakeVertexAttribute<VNormal>  (l3.total_bytes()));
	l3.AddAttribute(MakeVertexAttribute<VPosition>(l3.total_bytes()));
	l3.AddAttribute(MakeVertexAttribute<VTexCoord>(l3.total_bytes()));

	VertexLayout l4;
	l4.AddAttribute(MakeVertexAttribute<VPosition>(l4.total_bytes()));
	l4.AddAttribute(MakeVertexAttribute<VNormal>  (l4.total_bytes()));
	l4.AddAttribute(MakeVertexAttribute<VColor>  (l4.total_bytes()));

	VertexLayout l5;
	l5.AddAttribute(MakeVertexAttribute<VPosition>(l5.total_bytes()));
	l5.AddAttribute(MakeVertexAttribute<VNormal>  (l5.total_bytes()));

	VertexLayout l6;
	l6.AddAttribute(MakeVertexAttribute<VPosition>(l6.total_bytes()));
	l6.AddAttribute(MakeVertexAttribute<VNormal>  (l6.total_bytes()));
	l6.AddAttribute(MakeVertexAttribute<VTexCoord>(l6.total_bytes()));
	l6.AddAttribute(MakeVertexAttribute<VColor>   (l6.total_bytes()));

	EXPECT_TRUE (l1 == l1);
	EXPECT_TRUE (l1 == l2);
	EXPECT_FALSE(l1 == l3);
	EXPECT_FALSE(l1 == l4);
	EXPECT_FALSE(l1 == l5);
	EXPECT_FALSE(l1 == l6);

	EXPECT_FALSE(l1 != l1);
	EXPECT_FALSE(l1 != l2);
	EXPECT_TRUE (l1 != l3);
	EXPECT_TRUE (l1 != l4);
	EXPECT_TRUE (l1 != l5);
	EXPECT_TRUE (l1 != l6);
}
