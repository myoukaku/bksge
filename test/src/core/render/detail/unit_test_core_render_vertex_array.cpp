/**
 *	@file	unit_test_core_render_vertex_array.cpp
 *
 *	@brief	VertexArrayのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/detail/vertex_array.hpp>
#include <bksge/core/render/vertex.hpp>
#include <bksge/core/render/vertex_element.hpp>
//#include <bksge/fnd/serialization/shared_ptr.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <gtest/gtest.h>
#include <sstream>
//#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace vertex_array_test
{

GTEST_TEST(Render_VertexArray, DefaultConstructTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		using VertexType = Vertex<VPosition>;
		VertexArray<VertexType> a;
		EXPECT_EQ(VertexType::vertex_layout(), a.vertex_layout());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
	}
	{
		using VertexType = Vertex<VColor>;
		VertexArray<VertexType> a;
		EXPECT_EQ(VertexType::vertex_layout(), a.vertex_layout());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
	}
	{
		using VertexType = Vertex<VPosition, VColor, VNormal>;
		VertexArray<VertexType> a;
		EXPECT_EQ(VertexType::vertex_layout(), a.vertex_layout());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
	}
}

GTEST_TEST(Render_VertexArray, ConstructTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		using VertexType = Vertex<VPosition>;
		const VertexType t[] =
		{
			{{{10, 11, 12}}},
			{{{20, 21, 22}}},
			{{{30, 31, 32}}},
		};
		VertexArray<VertexType> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(VertexType::vertex_layout(), a.vertex_layout());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(36u, a.bytes());

		auto const* p = static_cast<const float*>(a.data());
		EXPECT_EQ(10, p[0]);
		EXPECT_EQ(11, p[1]);
		EXPECT_EQ(12, p[2]);
		EXPECT_EQ(20, p[3]);
		EXPECT_EQ(21, p[4]);
		EXPECT_EQ(22, p[5]);
		EXPECT_EQ(30, p[6]);
		EXPECT_EQ(31, p[7]);
		EXPECT_EQ(32, p[8]);
	}
	{
		using VertexType = Vertex<VPosition, VColor, VNormal>;
		const VertexType t[] = {{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}}};
		VertexArray<VertexType> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(VertexType::vertex_layout(), a.vertex_layout());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(40u, a.bytes());

		auto const* p = static_cast<const float*>(a.data());
		EXPECT_EQ(10, p[0]);
		EXPECT_EQ(11, p[1]);
		EXPECT_EQ(12, p[2]);
		EXPECT_EQ(13, p[3]);
		EXPECT_EQ(14, p[4]);
		EXPECT_EQ(15, p[5]);
		EXPECT_EQ(16, p[6]);
		EXPECT_EQ(17, p[7]);
		EXPECT_EQ(18, p[8]);
		EXPECT_EQ(19, p[9]);
	}
	{
		using VertexType = Vertex<VPosition, VColor, VNormal>;
		const VertexType t[] =
		{
			{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}},
			{{{20, 21, 22}}, {{23, 24, 25, 26}}, {{27, 28, 29}}},
			{{{30, 31, 32}}, {{33, 34, 35, 36}}, {{37, 38, 39}}},
		};
		VertexArray<VertexType> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(VertexType::vertex_layout(), a.vertex_layout());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(120u, a.bytes());

		auto const* p = static_cast<const float*>(a.data());
		EXPECT_EQ(10, p[ 0]);
		EXPECT_EQ(11, p[ 1]);
		EXPECT_EQ(12, p[ 2]);
		EXPECT_EQ(13, p[ 3]);
		EXPECT_EQ(14, p[ 4]);
		EXPECT_EQ(15, p[ 5]);
		EXPECT_EQ(16, p[ 6]);
		EXPECT_EQ(17, p[ 7]);
		EXPECT_EQ(18, p[ 8]);
		EXPECT_EQ(19, p[ 9]);

		EXPECT_EQ(20, p[10]);
		EXPECT_EQ(21, p[11]);
		EXPECT_EQ(22, p[12]);
		EXPECT_EQ(23, p[13]);
		EXPECT_EQ(24, p[14]);
		EXPECT_EQ(25, p[15]);
		EXPECT_EQ(26, p[16]);
		EXPECT_EQ(27, p[17]);
		EXPECT_EQ(28, p[18]);
		EXPECT_EQ(29, p[19]);

		EXPECT_EQ(30, p[20]);
		EXPECT_EQ(31, p[21]);
		EXPECT_EQ(32, p[22]);
		EXPECT_EQ(33, p[23]);
		EXPECT_EQ(34, p[24]);
		EXPECT_EQ(35, p[25]);
		EXPECT_EQ(36, p[26]);
		EXPECT_EQ(37, p[27]);
		EXPECT_EQ(38, p[28]);
		EXPECT_EQ(39, p[29]);
	}
}

GTEST_TEST(Render_VertexArray, CompareTest)
{
	using namespace bksge;
	using namespace bksge::render;

	using VertexType1 = Vertex<VPosition, VColor, VNormal>;
	using VertexType2 = Vertex<VNormal, VColor, VPosition>;
	using VertexType3 = Vertex<VPosition, VColor, VNormal, VBinormal>;

	const VertexType1 t1[] = {{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}}};
	const VertexType1 t2[] = {{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}}};
	const VertexType1 t3[] = {{{{ 0, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}}};
	const VertexType1 t4[] = {{{{10, 11, 12}}, {{10, 14, 15, 16}}, {{17, 18, 19}}}};
	const VertexType1 t5[] = {{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 20}}}};
	const VertexType2 t6[] = {{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}}};
	const VertexType3 t7[] = {{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}, {{20,21,22}}}};
	const VertexType1 t8[] =
	{
		{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}},
		{{{20, 21, 22}}, {{23, 24, 25, 26}}, {{27, 28, 29}}},
	};

	VertexArray<VertexType1> a1(bksge::begin(t1), bksge::end(t1));
	VertexArray<VertexType1> a2(bksge::begin(t2), bksge::end(t2));
	VertexArray<VertexType1> a3(bksge::begin(t3), bksge::end(t3));
	VertexArray<VertexType1> a4(bksge::begin(t4), bksge::end(t4));
	VertexArray<VertexType1> a5(bksge::begin(t5), bksge::end(t5));
	VertexArray<VertexType2> a6(bksge::begin(t6), bksge::end(t6));
	VertexArray<VertexType3> a7(bksge::begin(t7), bksge::end(t7));
	VertexArray<VertexType1> a8(bksge::begin(t8), bksge::end(t8));

	EXPECT_TRUE(a1 == a1);
	EXPECT_TRUE(a1 == a2);
	EXPECT_FALSE(a1 == a3);
	EXPECT_FALSE(a1 == a4);
	EXPECT_FALSE(a1 == a5);
	EXPECT_FALSE(a1 == a6);
	EXPECT_FALSE(a1 == a7);
	EXPECT_FALSE(a1 == a8);

	EXPECT_FALSE(a1 != a1);
	EXPECT_FALSE(a1 != a2);
	EXPECT_TRUE(a1 != a3);
	EXPECT_TRUE(a1 != a4);
	EXPECT_TRUE(a1 != a5);
	EXPECT_TRUE(a1 != a6);
	EXPECT_TRUE(a1 != a7);
	EXPECT_TRUE(a1 != a8);
}

GTEST_TEST(Render_VertexArray, SerializeTest)
{
#if 0
	using namespace bksge;
	using namespace bksge::render;
	using namespace bksge::archive;

	using VertexType = Vertex<VPosition, VColor, VNormal>;
	const VertexType t[] =
	{
		{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}},
		{{{20, 21, 22}}, {{23, 24, 25, 26}}, {{27, 28, 29}}},
		{{{30, 31, 32}}, {{33, 34, 35, 36}}, {{37, 38, 39}}},
	};

	VertexArray<VertexType> a(bksge::begin(t), bksge::end(t));

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (a);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (a);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (a);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(a);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(a);
#endif
#endif
}

#if 0
template <typename OArchive, typename IArchive, typename Stream>
void SerializeBasePtrTest(void)
{
	using namespace bksge;
	using namespace bksge::render;

	using VertexType1 = Vertex<VPosition, VColor, VNormal>;
	using VertexType2 = Vertex<VNormal, VColor, VPosition>;
	using VertexType3 = Vertex<VPosition, VColor, VNormal, VBinormal>;

	Stream s;
	{
		const VertexType1 t1[] = {{{{ 0,  1,  2}}, {{ 3,  4,  5,  6}}, {{ 7,  8,  9}}}};
		const VertexType2 t2[] =
		{
			{{{ 0,  1,  2}}, {{ 3,  4,  5,  6}}, {{ 7,  8,  9}}},
			{{{10, 11, 12}}, {{13, 14, 15, 16}}, {{17, 18, 19}}},
		};
		const VertexType3 t3[] = {{{{20, 21, 22}}, {{23, 24, 25, 26}}, {{27, 28, 29}}, {{30, 31, 32}}}};

		bksge::shared_ptr<VertexArrayBase> a1 = bksge::make_shared<VertexArray<VertexType1>>(bksge::begin(t1), bksge::end(t1));
		bksge::shared_ptr<VertexArrayBase> a2 = bksge::make_shared<VertexArray<VertexType2>>(bksge::begin(t2), bksge::end(t2));
		bksge::shared_ptr<VertexArrayBase> a3 = bksge::make_shared<VertexArray<VertexType3>>(bksge::begin(t3), bksge::end(t3));

		OArchive oa(s);
		oa << BKSGE_SERIALIZATION_NVP(a1);
		oa << BKSGE_SERIALIZATION_NVP(a2);
		oa << BKSGE_SERIALIZATION_NVP(a3);
	}
	{
		bksge::shared_ptr<VertexArrayBase> a1;
		bksge::shared_ptr<VertexArrayBase> a2;
		bksge::shared_ptr<VertexArrayBase> a3;

		IArchive ia(s);
		ia >> BKSGE_SERIALIZATION_NVP(a1);
		ia >> BKSGE_SERIALIZATION_NVP(a2);
		ia >> BKSGE_SERIALIZATION_NVP(a3);

		EXPECT_EQ(VertexType1::vertex_layout(), a1->vertex_layout());
		EXPECT_EQ(VertexType2::vertex_layout(), a2->vertex_layout());
		EXPECT_EQ(VertexType3::vertex_layout(), a3->vertex_layout());
		
		{
			auto const* p = static_cast<const float*>(a1->data());
			EXPECT_EQ(0, p[0]);
			EXPECT_EQ(1, p[1]);
			EXPECT_EQ(2, p[2]);
			EXPECT_EQ(3, p[3]);
			EXPECT_EQ(4, p[4]);
			EXPECT_EQ(5, p[5]);
			EXPECT_EQ(6, p[6]);
			EXPECT_EQ(7, p[7]);
			EXPECT_EQ(8, p[8]);
			EXPECT_EQ(9, p[9]);
		}
		{
			auto const* p = static_cast<const float*>(a2->data());
			EXPECT_EQ( 0, p[ 0]);
			EXPECT_EQ( 1, p[ 1]);
			EXPECT_EQ( 2, p[ 2]);
			EXPECT_EQ( 3, p[ 3]);
			EXPECT_EQ( 4, p[ 4]);
			EXPECT_EQ( 5, p[ 5]);
			EXPECT_EQ( 6, p[ 6]);
			EXPECT_EQ( 7, p[ 7]);
			EXPECT_EQ( 8, p[ 8]);
			EXPECT_EQ( 9, p[ 9]);
			EXPECT_EQ(10, p[10]);
			EXPECT_EQ(11, p[11]);
			EXPECT_EQ(12, p[12]);
			EXPECT_EQ(13, p[13]);
			EXPECT_EQ(14, p[14]);
			EXPECT_EQ(15, p[15]);
			EXPECT_EQ(16, p[16]);
			EXPECT_EQ(17, p[17]);
			EXPECT_EQ(18, p[18]);
			EXPECT_EQ(19, p[19]);
		}
		{
			auto const* p = static_cast<const float*>(a3->data());
			EXPECT_EQ(20, p[ 0]);
			EXPECT_EQ(21, p[ 1]);
			EXPECT_EQ(22, p[ 2]);
			EXPECT_EQ(23, p[ 3]);
			EXPECT_EQ(24, p[ 4]);
			EXPECT_EQ(25, p[ 5]);
			EXPECT_EQ(26, p[ 6]);
			EXPECT_EQ(27, p[ 7]);
			EXPECT_EQ(28, p[ 8]);
			EXPECT_EQ(29, p[ 9]);
			EXPECT_EQ(30, p[10]);
			EXPECT_EQ(31, p[11]);
			EXPECT_EQ(32, p[12]);
		}

		EXPECT_EQ(40u, a1->bytes());
		EXPECT_EQ(80u, a2->bytes());
		EXPECT_EQ(52u, a3->bytes());
	}
}
#endif

GTEST_TEST(Render_VertexArray, SerializeBasePtrTest)
{
#if 0
	using namespace bksge::archive;

	SerializeBasePtrTest<text_oarchive,   text_iarchive,   std::stringstream> ();
	SerializeBasePtrTest<xml_oarchive,    xml_iarchive,    std::stringstream> ();
	SerializeBasePtrTest<binary_oarchive, binary_iarchive, std::stringstream> ();

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeBasePtrTest<text_woarchive,  text_wiarchive,  std::wstringstream>();
	SerializeBasePtrTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>();
#endif
#endif
}

}	// namespace vertex_array_test

}	// namespace bksge_core_render_test
