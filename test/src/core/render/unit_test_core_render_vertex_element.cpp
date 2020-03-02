/**
 *	@file	unit_test_core_render_vertex_element.cpp
 *
 *	@brief	VertexElement のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/vertex_element.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

GTEST_TEST(Render_VertexElement, BasicTest)
{
	using namespace bksge;

	const VPosition v {{1,2,3}};
	static_assert(bksge::is_same<float, VPosition::value_type>::value, "");
	static_assert(VPosition::element_num == 3, "");
	static_assert(VPosition::semantic    == Semantic::kPosition, "");
	static_assert(VPosition::type_enum   == TypeEnum::kFloat, "");
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(2, v[1]);
	EXPECT_EQ(3, v[2]);

	const VNormal n {{4,5,6}};
	static_assert(bksge::is_same<float, VNormal::value_type>::value, "");
	static_assert(VNormal::element_num == 3, "");
	static_assert(VNormal::semantic    == Semantic::kNormal, "");
	static_assert(VNormal::type_enum   == TypeEnum::kFloat, "");
	EXPECT_EQ(4, n[0]);
	EXPECT_EQ(5, n[1]);
	EXPECT_EQ(6, n[2]);

	const VColor c {{2,3,4,5}};
	static_assert(bksge::is_same<float, VColor::value_type>::value, "");
	static_assert(VColor::element_num == 4, "");
	static_assert(VColor::semantic    == Semantic::kColor, "");
	static_assert(VColor::type_enum   == TypeEnum::kFloat, "");
	EXPECT_EQ(2, c[0]);
	EXPECT_EQ(3, c[1]);
	EXPECT_EQ(4, c[2]);
	EXPECT_EQ(5, c[3]);

	const VTexCoord t {{0, 1}};
	static_assert(bksge::is_same<float, VTexCoord::value_type>::value, "");
	static_assert(VTexCoord::element_num == 2, "");
	static_assert(VTexCoord::semantic    == Semantic::kTexCoord, "");
	static_assert(VTexCoord::type_enum   == TypeEnum::kFloat, "");
	EXPECT_EQ(0, t[0]);
	EXPECT_EQ(1, t[1]);
}

GTEST_TEST(Render_VertexElement, SerializeTest)
{
	using namespace bksge::serialization;

	const bksge::VPosition v {{1,2,3}};
	const bksge::VNormal n {{4,5,6}};

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(n);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(n);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(n);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(n);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(n);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(n);
#endif
}
