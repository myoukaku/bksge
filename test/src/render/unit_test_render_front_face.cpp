/**
 *	@file	unit_test_render_front_face.cpp
 *
 *	@brief	FrontFace のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/front_face.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace front_face_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::FrontFace front_face, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << front_face;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_FrontFace, OutputStreamTest)
{
	using bksge::FrontFace;

	OutputStreamTestSub(FrontFace::kClockwise,		  "FrontFace::kClockwise");
	OutputStreamTestSub(FrontFace::kCounterClockwise, "FrontFace::kCounterClockwise");

	OutputStreamTestSub(FrontFace::kClockwise,		  L"FrontFace::kClockwise");
	OutputStreamTestSub(FrontFace::kCounterClockwise, L"FrontFace::kCounterClockwise");
}

}	// namespace front_face_test

}	// namespace bksge_render_test
