/**
 *	@file	unit_test_core_render_vertex.cpp
 *
 *	@brief	Vertex のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/vertex.hpp>
#include <bksge/core/render/vertex_element.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <sstream>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace render_vertex_test
{

inline void AttrTest(
	bksge::VertexLayout const& layout,
	bksge::Semantic semantic,
	bksge::size_t element_num,
	bksge::size_t offset,
	bksge::TypeEnum type)
{
	auto const* attr = layout.FindVertexAttributeBySemantic(semantic);
	ASSERT_TRUE(attr != nullptr);
	EXPECT_EQ(element_num, attr->element_num());
	EXPECT_EQ(offset, attr->offset());
	EXPECT_EQ(semantic, attr->semantic());
	EXPECT_EQ(type, attr->type());
}

inline void AttrNullTest(
	bksge::VertexLayout const& layout,
	bksge::Semantic semantic)
{
	auto const* attr = layout.FindVertexAttributeBySemantic(semantic);
	EXPECT_TRUE(attr == nullptr);
}

GTEST_TEST(Render_Vertex, BasicTest)
{
	using namespace bksge::render;
	using VP = Vertex<VPosition>;
	using VC = Vertex<VColor>;
	using VN = Vertex<VNormal>;
	using VPC = Vertex<VPosition, VColor>;
	using VPN = Vertex<VPosition, VNormal>;
	using VCP = Vertex<VColor, VPosition>;

	{
		auto const& layout = VP::vertex_layout();
		EXPECT_EQ(sizeof(float) * 3, layout.total_bytes());
		EXPECT_EQ(sizeof(float) * 3, sizeof(VP));
		AttrTest(layout, Semantic::kPosition, 3, 0, TypeEnum::kFloat);
		AttrNullTest(layout, Semantic::kColor);
		AttrNullTest(layout, Semantic::kNormal);
	}
	{
		auto const& layout = VC::vertex_layout();
		EXPECT_EQ(sizeof(float) * 4, layout.total_bytes());
		EXPECT_EQ(sizeof(float) * 4, sizeof(VC));
		AttrNullTest(layout, Semantic::kPosition);
		AttrTest(layout, Semantic::kColor, 4, 0, TypeEnum::kFloat);
		AttrNullTest(layout, Semantic::kNormal);
	}
	{
		auto const& layout = VN::vertex_layout();
		EXPECT_EQ(sizeof(float) * 3, layout.total_bytes());
		EXPECT_EQ(sizeof(float) * 3, sizeof(VN));
		AttrNullTest(layout, Semantic::kPosition);
		AttrNullTest(layout, Semantic::kColor);
		AttrTest(layout, Semantic::kNormal, 3, 0, TypeEnum::kFloat);
	}
	{
		auto const& layout = VPC::vertex_layout();
		EXPECT_EQ(sizeof(float) * 7, layout.total_bytes());
		EXPECT_EQ(sizeof(float) * 7, sizeof(VPC));
		AttrTest(layout, Semantic::kPosition, 3, 0, TypeEnum::kFloat);
		AttrTest(layout, Semantic::kColor, 4, 12, TypeEnum::kFloat);
		AttrNullTest(layout, Semantic::kNormal);

		const VPC vertices[] =
		{
			{{{1, 2, 3}}, {{4, 5, 6, 7}}},
			{{{8, 9, 10}}, {{11, 12, 13, 14}}},
		};

		EXPECT_EQ(sizeof(float) * 14, sizeof(vertices));

		const float* p = reinterpret_cast<const float*>(vertices);
		EXPECT_EQ(1, p[0]);
		EXPECT_EQ(2, p[1]);
		EXPECT_EQ(3, p[2]);
		EXPECT_EQ(4, p[3]);
		EXPECT_EQ(5, p[4]);
		EXPECT_EQ(6, p[5]);
		EXPECT_EQ(7, p[6]);
		EXPECT_EQ(8, p[7]);
		EXPECT_EQ(9, p[8]);
		EXPECT_EQ(10, p[9]);
		EXPECT_EQ(11, p[10]);
		EXPECT_EQ(12, p[11]);
		EXPECT_EQ(13, p[12]);
		EXPECT_EQ(14, p[13]);
	}
	{
		auto const& layout = VPN::vertex_layout();
		EXPECT_EQ(sizeof(float) * 6, layout.total_bytes());
		EXPECT_EQ(sizeof(float) * 6, sizeof(VPN));
		AttrTest(layout, Semantic::kPosition, 3, 0, TypeEnum::kFloat);
		AttrNullTest(layout, Semantic::kColor);
		AttrTest(layout, Semantic::kNormal, 3, 12, TypeEnum::kFloat);

		const VPN vertices[] =
		{
			{{{11, 12, 13}}, {{14, 15, 16}}},
			{{{21, 22, 23}}, {{24, 25, 26}}},
		};

		EXPECT_EQ(sizeof(float) * 12, sizeof(vertices));

		const float* p = reinterpret_cast<const float*>(vertices);
		EXPECT_EQ(11, p[0]);
		EXPECT_EQ(12, p[1]);
		EXPECT_EQ(13, p[2]);
		EXPECT_EQ(14, p[3]);
		EXPECT_EQ(15, p[4]);
		EXPECT_EQ(16, p[5]);
		EXPECT_EQ(21, p[6]);
		EXPECT_EQ(22, p[7]);
		EXPECT_EQ(23, p[8]);
		EXPECT_EQ(24, p[9]);
		EXPECT_EQ(25, p[10]);
		EXPECT_EQ(26, p[11]);
	}
	{
		auto const& layout = VCP::vertex_layout();
		EXPECT_EQ(sizeof(float) * 7, layout.total_bytes());
		EXPECT_EQ(sizeof(float) * 7, sizeof(VCP));
		AttrTest(layout, Semantic::kPosition, 3, 16, TypeEnum::kFloat);
		AttrTest(layout, Semantic::kColor, 4, 0, TypeEnum::kFloat);
		AttrNullTest(layout, Semantic::kNormal);

		const VCP vertices[] =
		{
			{{{11, 12, 13, 14}}, {{15, 16, 17}}},
			{{{21, 22, 23, 24}}, {{25, 26, 27}}},
		};

		EXPECT_EQ(sizeof(float) * 14, sizeof(vertices));

		const float* p = reinterpret_cast<const float*>(vertices);
		EXPECT_EQ(11, p[0]);
		EXPECT_EQ(12, p[1]);
		EXPECT_EQ(13, p[2]);
		EXPECT_EQ(14, p[3]);
		EXPECT_EQ(15, p[4]);
		EXPECT_EQ(16, p[5]);
		EXPECT_EQ(17, p[6]);
		EXPECT_EQ(21, p[7]);
		EXPECT_EQ(22, p[8]);
		EXPECT_EQ(23, p[9]);
		EXPECT_EQ(24, p[10]);
		EXPECT_EQ(25, p[11]);
		EXPECT_EQ(26, p[12]);
		EXPECT_EQ(27, p[13]);
	}

	{
		using VertexType = Vertex<VTexCoord, VColor, VFogCoord, VPosition, VBinormal>;
		auto const& layout = VertexType::vertex_layout();
		EXPECT_EQ(sizeof(float) * (2+4+1+3+3), layout.total_bytes());
		EXPECT_EQ(sizeof(float) * (2+4+1+3+3), sizeof(VertexType));

		AttrTest(layout, Semantic::kTexCoord, 2, 0,                TypeEnum::kFloat);
		AttrTest(layout, Semantic::kColor,    4, sizeof(float)* 2, TypeEnum::kFloat);
		AttrTest(layout, Semantic::kFogCoord, 1, sizeof(float)* 6, TypeEnum::kFloat);
		AttrTest(layout, Semantic::kPosition, 3, sizeof(float)* 7, TypeEnum::kFloat);
		AttrTest(layout, Semantic::kBinormal, 3, sizeof(float)*10, TypeEnum::kFloat);

		AttrNullTest(layout, Semantic::kNormal);
		AttrNullTest(layout, Semantic::kPointSize);
		AttrNullTest(layout, Semantic::kBlendIndices);

		const VertexType vertices[] =
		{
			{{{ 0,  1}},{{ 2,  3,  4,  5}},{{ 6}},{{ 7, 8, 9}},{{10,11,12}}},
			{{{13, 14}},{{15, 16, 17, 18}},{{19}},{{20,21,22}},{{23,24,25}}},
			{{{26, 27}},{{28, 29, 30, 31}},{{32}},{{33,34,35}},{{36,37,38}}},
		};

		EXPECT_EQ(sizeof(float) * 39, sizeof(vertices));

		const float* p = reinterpret_cast<const float*>(vertices);

		for (bksge::size_t i = 0; i < 39; ++i)
		{
			EXPECT_EQ(static_cast<float>(i), p[i]);
		}
	}
}

GTEST_TEST(Render_Vertex, CompareTest)
{
	using namespace bksge::render;
	using VertexType = Vertex<VPosition, VColor, VNormal>;

	const VertexType v1 = {{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}};
	const VertexType v2 = {{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}};
	const VertexType v3 = {{{ 0, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}};
	const VertexType v4 = {{{10, 10, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}};
	const VertexType v5 = {{{10, 11, 13}}, {{13, 14, 15, 16}}, {{17, 18, 19}}};
	const VertexType v6 = {{{10, 11, 12}}, {{ 1, 14, 15, 16}}, {{17, 18, 19}}};
	const VertexType v7 = {{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 20}}};

	EXPECT_TRUE (v1 == v1);
	EXPECT_TRUE (v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);
	EXPECT_FALSE(v1 == v5);
	EXPECT_FALSE(v1 == v6);
	EXPECT_FALSE(v1 == v7);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE (v1 != v3);
	EXPECT_TRUE (v1 != v4);
	EXPECT_TRUE (v1 != v5);
	EXPECT_TRUE (v1 != v6);
	EXPECT_TRUE (v1 != v7);
}

GTEST_TEST(Render_Vertex, SerializeTest)
{
	using namespace bksge::render;
	using namespace bksge::serialization;

	using VertexType1 = Vertex<VPosition, VColor, VNormal>;
	using VertexType2 = Vertex<VTexCoord, VColor, VFogCoord, VPosition, VBinormal>;

	VertexType1 v1 = {{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}};
	VertexType2 v2 = {{{ 0,  1}},{{ 2,  3,  4,  5}},{{ 6}},{{ 7, 8, 9}},{{10,11,12}}};

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v1);
	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v2);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v1);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v2);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v1);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v2);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v1);
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v2);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v1);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v2);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v1);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v2);
#endif
}

}	// namespace render_vertex_test

}	// namespace bksge_core_render_test
