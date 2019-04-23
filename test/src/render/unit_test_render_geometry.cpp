/**
 *	@file	unit_test_render_geometry.cpp
 *
 *	@brief	Geometry のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/geometry.hpp>
#include <bksge/render/vertex.hpp>
#include <bksge/render/vertex_element.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
//#include "serialize_test.hpp"

GTEST_TEST(Render_Geometry, BasicTest)
{
	using namespace bksge::render;

	{
		Geometry geometry;
		auto const& layout = geometry.vertex_layout();

		EXPECT_EQ(Primitive::kTriangles, geometry.primitive());
		EXPECT_EQ(nullptr, geometry.vertex_array_data());
		EXPECT_EQ(0u, geometry.vertex_array_bytes());
		EXPECT_EQ(nullptr, geometry.index_array_data());
		EXPECT_EQ(0u, geometry.index_array_bytes());
		EXPECT_EQ(0u, geometry.index_array_count());
		EXPECT_EQ(TypeEnum::kUnsignedShort, geometry.index_array_type());
		EXPECT_EQ(0u, layout.total_bytes());
	}

	{
		using VertexType = Vertex<VPosition, VColor, VNormal>;
		const VertexType vertex_array[] =
		{
			{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}},
			{{{20, 21, 22}}, {{23, 24, 25, 26}}, {{27, 28, 29}}},
		};

		const std::uint16_t index_array[] =
		{
			0, 1,
		};

		Geometry geometry(Primitive::kLines, vertex_array, index_array);
		auto const& layout = geometry.vertex_layout();

		EXPECT_EQ(Primitive::kLines, geometry.primitive());
		EXPECT_NE(nullptr, geometry.vertex_array_data());
		EXPECT_EQ(sizeof(vertex_array), geometry.vertex_array_bytes());
		EXPECT_NE(nullptr, geometry.index_array_data());
		EXPECT_EQ(sizeof(index_array), geometry.index_array_bytes());
		EXPECT_EQ(2u, geometry.index_array_count());
		EXPECT_EQ(TypeEnum::kUnsignedShort, geometry.index_array_type());
		EXPECT_EQ(sizeof(VertexType), layout.total_bytes());
	}

	{
		using VertexType = Vertex<VPosition, VNormal, VColor, VTexCoord>;
		const VertexType vertex_array[] =
		{
			{{{10, 11, 12}}, {{13, 14, 15}}, {{16, 17, 18, 19}}, {{20, 21}}},
			{{{20, 21, 22}}, {{23, 24, 25}}, {{26, 27, 28, 29}}, {{30, 31}}},
			{{{30, 31, 32}}, {{33, 34, 35}}, {{36, 37, 38, 39}}, {{40, 41}}},
		};

		const std::uint32_t index_array[] =
		{
			0, 1, 2,
		};

		Geometry geometry(Primitive::kTriangles, vertex_array, index_array);
		auto const& layout = geometry.vertex_layout();

		EXPECT_EQ(Primitive::kTriangles, geometry.primitive());
		EXPECT_NE(nullptr, geometry.vertex_array_data());
		EXPECT_EQ(sizeof(vertex_array), geometry.vertex_array_bytes());
		EXPECT_NE(nullptr, geometry.index_array_data());
		EXPECT_EQ(sizeof(index_array), geometry.index_array_bytes());
		EXPECT_EQ(3u, geometry.index_array_count());
		EXPECT_EQ(TypeEnum::kUnsignedInt, geometry.index_array_type());
		EXPECT_EQ(sizeof(VertexType), layout.total_bytes());
	}
}

GTEST_TEST(Render_Geometry, CopyTest)
{
	using namespace bksge::render;

	{
		using VertexType = Vertex<VPosition, VColor, VNormal>;
		const VertexType vertex_array[] =
		{
			{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}},
			{{{20, 21, 22}}, {{23, 24, 25, 26}}, {{27, 28, 29}}},
		};

		const std::uint16_t index_array[] =
		{
			0, 1,
		};

		Geometry geometry_tmp(Primitive::kLines, vertex_array, index_array);

		Geometry geometry(geometry_tmp);

		auto const& layout = geometry.vertex_layout();

		EXPECT_EQ(Primitive::kLines, geometry.primitive());
		EXPECT_NE(nullptr, geometry.vertex_array_data());
		EXPECT_EQ(sizeof(vertex_array), geometry.vertex_array_bytes());
		EXPECT_NE(nullptr, geometry.index_array_data());
		EXPECT_EQ(sizeof(index_array), geometry.index_array_bytes());
		EXPECT_EQ(2u, geometry.index_array_count());
		EXPECT_EQ(TypeEnum::kUnsignedShort, geometry.index_array_type());
		EXPECT_EQ(sizeof(VertexType), layout.total_bytes());
	}
	{
		Geometry geometry;

		using VertexType = Vertex<VPosition, VNormal, VColor, VTexCoord>;
		const VertexType vertex_array[] =
		{
			{{{10, 11, 12}}, {{13, 14, 15}}, {{16, 17, 18, 19}}, {{20, 21}}},
			{{{20, 21, 22}}, {{23, 24, 25}}, {{26, 27, 28, 29}}, {{30, 31}}},
			{{{30, 31, 32}}, {{33, 34, 35}}, {{36, 37, 38, 39}}, {{40, 41}}},
		};

		const std::uint32_t index_array[] =
		{
			0, 1, 2,
		};

		Geometry geometry_tmp(Primitive::kTriangles, vertex_array, index_array);

		geometry = geometry_tmp;

		auto const& layout = geometry.vertex_layout();

		EXPECT_EQ(Primitive::kTriangles, geometry.primitive());
		EXPECT_NE(nullptr, geometry.vertex_array_data());
		EXPECT_EQ(sizeof(vertex_array), geometry.vertex_array_bytes());
		EXPECT_NE(nullptr, geometry.index_array_data());
		EXPECT_EQ(sizeof(index_array), geometry.index_array_bytes());
		EXPECT_EQ(3u, geometry.index_array_count());
		EXPECT_EQ(TypeEnum::kUnsignedInt, geometry.index_array_type());
		EXPECT_EQ(sizeof(VertexType), layout.total_bytes());
	}
}

GTEST_TEST(Render_Geometry, CompareTest)
{
	using namespace bksge::render;

	using VertexType1 = Vertex<VPosition>;
	using VertexType2 = Vertex<VNormal>;
	using VertexType3 = Vertex<VPosition, VNormal>;

	const VertexType1 vertex_array_1[] =
	{
		{{{10, 11, 12}}},
	};
	const VertexType1 vertex_array_2[] =
	{
		{{{10, 11, 12}}},
	};
	const VertexType1 vertex_array_3[] =
	{
		{{{20, 21, 22}}},
	};
	const VertexType2 vertex_array_4[] =
	{
		{{{10, 11, 12}}},
	};
	const VertexType2 vertex_array_5[] =
	{
		{{{20, 21, 22}}},
	};
	const VertexType3 vertex_array_6[] =
	{
		{{{10, 11, 12}},{{10, 11, 12}}},
	};

	const std::uint16_t index_array_1[] =
	{
		0, 1, 2,
	};
	const std::uint16_t index_array_2[] =
	{
		0, 1, 2,
	};
	const std::uint16_t index_array_3[] =
	{
		2, 1, 0,
	};
	const std::uint32_t index_array_4[] =
	{
		0, 1, 2,
	};
	const std::uint32_t index_array_5[] =
	{
		2, 1, 0,
	};

	const Geometry geometry_1(Primitive::kLines, vertex_array_1, index_array_1);
	const Geometry geometry_2(Primitive::kLines, vertex_array_1, index_array_2);
	const Geometry geometry_3(Primitive::kLines, vertex_array_1, index_array_3);
	const Geometry geometry_4(Primitive::kLines, vertex_array_1, index_array_4);
	const Geometry geometry_5(Primitive::kLines, vertex_array_1, index_array_5);
	const Geometry geometry_6(Primitive::kLines, vertex_array_1, index_array_1);
	const Geometry geometry_7(Primitive::kLines, vertex_array_2, index_array_1);
	const Geometry geometry_8(Primitive::kLines, vertex_array_3, index_array_1);
	const Geometry geometry_9(Primitive::kLines, vertex_array_4, index_array_1);
	const Geometry geometry_10(Primitive::kLines, vertex_array_5, index_array_1);
	const Geometry geometry_11(Primitive::kLines, vertex_array_6, index_array_1);
	const Geometry geometry_12(Primitive::kPoints, vertex_array_1, index_array_1);
	const Geometry geometry_13(Primitive::kTriangles, vertex_array_1, index_array_1);
	const Geometry geometry_14;

	EXPECT_TRUE (geometry_1 == geometry_1);
	EXPECT_TRUE (geometry_1 == geometry_2);
	EXPECT_FALSE(geometry_1 == geometry_3);
	EXPECT_FALSE(geometry_1 == geometry_4);
	EXPECT_FALSE(geometry_1 == geometry_5);
	EXPECT_TRUE (geometry_1 == geometry_6);
	EXPECT_TRUE (geometry_1 == geometry_7);
	EXPECT_FALSE(geometry_1 == geometry_8);
	EXPECT_FALSE(geometry_1 == geometry_9);
	EXPECT_FALSE(geometry_1 == geometry_10);
	EXPECT_FALSE(geometry_1 == geometry_11);
	EXPECT_FALSE(geometry_1 == geometry_12);
	EXPECT_FALSE(geometry_1 == geometry_13);
	EXPECT_FALSE(geometry_1 == geometry_14);

	EXPECT_FALSE(geometry_1 != geometry_1);
	EXPECT_FALSE(geometry_1 != geometry_2);
	EXPECT_TRUE (geometry_1 != geometry_3);
	EXPECT_TRUE (geometry_1 != geometry_4);
	EXPECT_TRUE (geometry_1 != geometry_5);
	EXPECT_FALSE(geometry_1 != geometry_6);
	EXPECT_FALSE(geometry_1 != geometry_7);
	EXPECT_TRUE (geometry_1 != geometry_8);
	EXPECT_TRUE (geometry_1 != geometry_9);
	EXPECT_TRUE (geometry_1 != geometry_10);
	EXPECT_TRUE (geometry_1 != geometry_11);
	EXPECT_TRUE (geometry_1 != geometry_12);
	EXPECT_TRUE (geometry_1 != geometry_13);
	EXPECT_TRUE (geometry_1 != geometry_14);
}

#if 0
GTEST_TEST(Render_Geometry, SerializeTest)
{
	using namespace bksge::archive;

	using VertexType = Vertex<VPosition, VColor, VNormal>;
	const VertexType vertex_array[] =
	{
		{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}},
		{{{20, 21, 22}}, {{23, 24, 25, 26}}, {{27, 28, 29}}},
	};

	const std::uint16_t index_array[] =
	{
		0, 1,
	};

	Geometry geometry(Primitive::kLines, vertex_array, index_array);

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (geometry);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (geometry);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (geometry);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(geometry);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(geometry);
#endif
}
#endif
