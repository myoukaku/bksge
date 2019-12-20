/**
 *	@file	unit_test_core_render_primitive.cpp
 *
 *	@brief	Primitive のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/primitive.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace primitive_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::Primitive p, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << p;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_Primitive, OutputStreamTest)
{
	using bksge::Primitive;

	OutputStreamTestSub(Primitive::kPoints,		"Primitive::kPoints");
	OutputStreamTestSub(Primitive::kLines,		"Primitive::kLines");
	OutputStreamTestSub(Primitive::kTriangles,	"Primitive::kTriangles");

	OutputStreamTestSub(Primitive::kPoints,		L"Primitive::kPoints");
	OutputStreamTestSub(Primitive::kLines,		L"Primitive::kLines");
	OutputStreamTestSub(Primitive::kTriangles,	L"Primitive::kTriangles");
}

GTEST_TEST(Render_Primitive, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::Primitive::kTriangles;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace primitive_test

}	// namespace bksge_core_render_test
