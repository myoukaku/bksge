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

}	// namespace primitive_test

}	// namespace bksge_core_render_test
